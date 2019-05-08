//
// Created by rafael on 08/04/19.
//
//libs do sistema


//lib importadas

#include <model.pb.h>
#include "Seed.h"
#include "util.h"
#include <ostream>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>


namespace io = google::protobuf::io;

Seed::~Seed() {
    close(socket_fd);
}

Seed::Seed(int porta) {
    srand((unsigned int) time(NULL));
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        error("socket()");
    }
    FD_ZERO(&readfds);
    numfd = socket_fd + 1;
    address_length = sizeof(struct sockaddr);
    rastreador_address.sin_family = AF_INET;
    rastreador_address.sin_port = htons(rastreadorPorta);
    rastreador_address.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_address.sin_zero), 8);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(porta);
    server_address.sin_addr.s_addr = INADDR_ANY;
    bzero(&(rastreador_address.sin_zero), 8);
    if (bind(socket_fd,
             (struct sockaddr *) &server_address, sizeof(struct sockaddr)) == -1) {
        error("bind()");
    }
    Run();

}


void Seed::Run() {

//    AtualizarRastreador("cc72fc24056ced9ce13a287ca1243d48", "/home/rafael/Downloads/t.mp3");
    AtualizarRastreador("cc72fc24056ced9ce13a287ca1243d48", "/home/rafael/Downloads/rafael.txt");

    for (;;) {
        FD_SET(socket_fd, &readfds);
        int recieve = select(numfd, &readfds, NULL, NULL, NULL);
        if (recieve == -1) {
            perror("Erro select"); // erro no select()
        }
        if (recieve == 0) {
            perror("0 select"); // erro no select()
        }

        if (FD_ISSET(socket_fd, &readfds)) {
            FD_CLR(socket_fd, &readfds);
            std::cout << "Comunicação Cliente" << std::endl;
            bytes_read = recvfrom(socket_fd, recieve_data, MAX_LENGTH, 0, (struct sockaddr *) &client_address,
                                  &address_length); //block call, will wait till client enters something, before proceeding
            rathed::Datagrama buf;
            buf.ParseFromArray(recieve_data, bytes_read);
            TratarMensagem(buf);
        }
    }
}

void Seed::IsTypeEnviar(rathed::Datagrama &data, int opcao) {
    if (opcao == 1) {
        int valor = rand() % (10 + 1);
        if (valor > R) {
            std::cout << "Bloco Dispinivel: " << std::endl;
            std::cout << "Enviar Bloco Dispinivel!" << std::endl;
            EnviarSequencial(data);
        } else {
            std::cout << "Bloco Não Dispinivel!: " << std::endl;
            mySleep(20);
            std::cout << "Consultar Bloco....." << std::endl;
            IsTypeEnviar(data, 1);
        }
    } else if (opcao==2) {
        EnviarAleatorio(data);
    }
}

void Seed::TratarMensagem(rathed::Datagrama &data) {


    switch (data.type()) {
        case 1:
            Desconectar();
            break;
        case 2:
            IsTypeEnviar(data,1);
            break;
        case 3:
            ConsultaFileSize(data);
            break;
        case 4:
            AtualizacaoRealizada(data);
            break;
    }


}

void Seed::ConsultaFileSize(rathed::Datagrama &data) {
    auto it = std::find_if(file.begin(), file.end(), CompareHash(data.data()));
    if (it.base() != nullptr && data.packnumber() >= 0) {
        bytes_total = fileSize(it.base()->second.c_str());
        std::cout << "ConsultaFile Enviado Tamanho File: " << bytes_total
                  << std::endl;
        rathed::Datagrama _data = DataGrama(3, bytes_total, data.data());
        if (sendto(socket_fd, DataGramaSerial(_data), _data.ByteSizeLong(), 0,
                   (struct sockaddr *) &client_address, sizeof(struct sockaddr)) <= 0)
            error("Erro ao enviar");
    } else {
        std::cout << "Erro Enviado Tamanho File: " << std::endl;
    }

}

rathed::Datagrama Seed::check_list_enviados(int x) {
    rathed::Datagrama datagrama;
    datagrama.set_type(static_cast<rathed::DatagramaType>(1));
    int valor = 0, temp = 0;
    temp = (int) total_de_pacotes + 1 - x;
    valor = rand() % temp;
    std::cout << "X: " << x << " Aleatorio Sorteador: " << valor << " MAXIMO " << total_de_pacotes << std::endl;
    auto it = buffer.begin() + (x - 1);
    while (it != buffer.end()) {
        if ((*it).packnumber() >= (valor)) {
            datagrama.set_packnumber(it.base()->packnumber());
            datagrama.set_data(it.base()->data().c_str(), it.base()->data().size());
//            it = buffer.erase(it);
            return datagrama;
        } else {
            ++it;
        }

    }
    datagrama.set_packnumber(-1);
    return datagrama;
}


void Seed::EnviarAleatorio(rathed::Datagrama &data) {


    auto it = std::find_if(file.begin(), file.end(), CompareHash(data.data()));
    rathed::Datagrama datagrama;

    if (it.base() != nullptr && data.packnumber() >= 0) {
        datagrama = check_list_enviados(data.packnumber());
        if (sendto(socket_fd, DataGramaSerial(datagrama), datagrama.ByteSizeLong(), 0,
                   (struct sockaddr *) &client_address, sizeof(struct sockaddr)) <= 0)
            error("Erro ao enviar 1");

        std::cout << "Bytes Datagrama: " << datagrama.ByteSizeLong() << std::endl;
        std::cout << "Packnumber: " << datagrama.packnumber() << std::endl;


    } else {
        if (
                sendto(socket_fd,
                       "ERRO", sizeof("ERRO"), 0,
                       (struct sockaddr *) &client_address, sizeof(struct sockaddr)) <= 0)
            error("Erro ao enviar 2");
    }
}

void Seed::EnviarSequencial(rathed::Datagrama &data) {
    auto it_find = std::find_if(file.begin(), file.end(), CompareHash(data.data()));
    rathed::Datagrama datagrama;
    if (it_find.base() != nullptr && data.packnumber() > 0) {

        auto it = buffer.begin() + (data.packnumber() - 1);

        datagrama.set_type(static_cast<rathed::DatagramaType>(1));
        datagrama.set_packnumber(it.base()->packnumber());
        datagrama.set_data(it.base()->data().c_str(),it.base()->data().size());

        if (sendto(socket_fd, DataGramaSerial(datagrama), datagrama.ByteSizeLong(), 0,
                   (struct sockaddr *) &client_address, sizeof(struct sockaddr)) <= 0)
            error("Erro ao enviar 1");


        std::cout << "Total de Bytes File Enviados: " << data.packnumber() << " DE " << total_de_pacotes
                  << std::endl;
        std::cout << "Bytes File: " << it.base()->data().size() << std::endl;
        std::cout << "Bytes Datagrama: " << datagrama.ByteSizeLong() << std::endl;
        std::cout << "Packnumber: " << datagrama.packnumber() << std::endl;


    } else {
        if (
                sendto(socket_fd,
                       "ERRO", sizeof("ERRO"), 0,
                       (struct sockaddr *) &client_address, sizeof(struct sockaddr)) <= 0)
            error("Erro ao enviar 2");
    }
}


void Seed::AtualizarRastreador(const std::string &hash, const std::string &path) {


    std::cout << "atualizarRastreador Seed: " << std::endl;
    std::pair<std::string, std::string> arquivo = std::make_pair(hash,
                                                                 path);
    file.push_back(arquivo);

    long fileSize_total = fileSize(path.c_str());

    if ((fileSize_total % 310 == 0)) {
        total_de_pacotes = (fileSize_total / 310);

    } else {
        total_de_pacotes = (fileSize_total / 310) + 1;
    }


    int fd_arq = open(path.c_str(), O_RDONLY, 0666);
    io::ZeroCopyInputStream *raw_input = new io::FileInputStream(fd_arq);
    auto *coded_input = new io::CodedInputStream(raw_input);

    for (long j = 1; j <= total_de_pacotes; ++j) {
        int inicial = coded_input->CurrentPosition();
        coded_input->ReadRaw(recieve_data, MAX_LENGTH - 10);
        int fim = coded_input->CurrentPosition();
        rathed::Datagrama data;
        data.set_packnumber(j);
        data.set_data(recieve_data, (fim - inicial));
        buffer.push_back(data);

    }

    rathed::Datagrama _data = DataGrama(4, arquivo.second.size(), arquivo.first);
    if (sendto(socket_fd, DataGramaSerial(_data), _data.ByteSizeLong(), 0,
               (struct sockaddr *) &rastreador_address, sizeof(struct sockaddr)) <= 0)
        error("Erro ao enviar");

    delete (raw_input);
    delete (coded_input);
    close(fd_arq);

}

void Seed::AtualizacaoRealizada(rathed::Datagrama &data) {
    std::cout << "TIPO: " << data.type() << "| OK |" << std::endl;
}

void Seed::Desconectar() {
    std::cout << "User desconectado" << std::endl;

}
