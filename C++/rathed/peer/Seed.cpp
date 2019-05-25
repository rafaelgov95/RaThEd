//
// Created by rafael on 08/04/19.
//
//libs do sistema


//lib importadas

#include <model.pb.h>
#include "Seed.h"
#include "util.h"
#include <ostream>
#include "random"

Seed::~Seed() {

    delete (raw_input);
    delete (coded_input);
    close(fd_arq);
    close(socket_fd);
}

Seed::Seed(int tipo_download, int porta, int rastreadorPorta, int disponibilidade) {

    opcao = tipo_download;
    R = disponibilidade;

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
    my_port = ntohs(server_address.sin_port);


}


void Seed::Run() {


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
            bytes_read = recvfrom(socket_fd, recieve_data, MAX_LENGTH_FILE, 0, (struct sockaddr *) &client_address,
                                  &address_length); //block call, will wait till client enters something, before proceeding
            rathed::Datagrama buf;
            buf.ParseFromArray(recieve_data, bytes_read);
            TratarMensagem(buf);
        }
    }
}

void Seed::IsTypeEnviar(rathed::Datagrama &data) {
    if (opcao == 1) {
        int valor = rand() % (100 + 1);
        if (R >= valor) {
            std::cout << "Bloco Dispinivel: " << std::endl;
            std::cout << "Enviar Bloco Dispinivel!" << std::endl;
            EnviarSequencial(data);
        } else {
            std::cout << "Bloco Não Dispinivel!: " << std::endl;
            mySleep(20);
            std::cout << "Consultar Bloco....." << std::endl;
            IsTypeEnviar(data);
        }
    } else if (opcao == 2) {
        EnviarAleatorio(data);
    }
}

void Seed::TratarMensagem(rathed::Datagrama &data) {

    switch (data.type()) {
        case 1:
            ConfirmarPacote(data);
            break;
        case 2:
            IsTypeEnviar(data);
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
        rathed::Datagrama _data = DataGrama(3, bytes_total, data.data().c_str());

        if (sendto(socket_fd, DataGramaSerial(_data), _data.ByteSizeLong(), 0,
                   (struct sockaddr *) &client_address, sizeof(struct sockaddr)) <= 0)
            error("Erro ao enviar");
    } else {
        std::cout << "Erro Enviado Tamanho File: " << std::endl;
    }

}

rathed::Datagrama Seed::SelecionarBloco(rathed::Datagrama &data) {
    rathed::Datagrama datagrama;
    datagrama.set_type(static_cast<rathed::DatagramaType>(1));

    auto i = buffer.begin();
    while (i != buffer.end()) {
        int valor = 0;
        int range = total_de_pacotes;
        if (range > 1) {
            valor = rand() % range;
        }
        i = buffer.begin() + valor;
        if (i.base()->packnumber() >= data.packnumber()) {
            datagrama.set_packnumber(i.base()->packnumber());
            datagrama.set_data(i.base()->data().c_str(), i.base()->data().size());
            std::cout << "X: " << data.packnumber() << " Tamanho PACK: " << datagrama.data().size()
                      << " VALOR SORTEADO: " << valor
                      << " TOTAL PACKs: " << total_de_pacotes << " SEED: " << my_port
                      << std::endl;
            return datagrama;
        } else {
            i = buffer.erase(i);
            total_de_pacotes = buffer.size();
        }
    }
    datagrama.set_packnumber(0);
    datagrama.set_data("", 1);
    return datagrama;
}

void Seed::EnviarAleatorio(rathed::Datagrama &data) {
    auto it = std::find_if(file.begin(), file.end(), CompareHash(data.data()));
    if (it.base() != nullptr && data.packnumber() > 0) {


        ConfirmarPacote(data);
        rathed::Datagrama datagrama;
        datagrama = SelecionarBloco(data);
        if (sendto(socket_fd, DataGramaSerial(datagrama), datagrama.ByteSizeLong(), 0,
                   (struct sockaddr *) &client_address, sizeof(struct sockaddr)) <= 0)
            error("Erro ao enviar 1");

        std::cout << "Bytes data: " << datagrama.data().size() << std::endl;
        std::cout << "Bytes Datagrama: " << datagrama.ByteSizeLong() << std::endl;
        std::cout << "Packnumber: " << datagrama.packnumber() << std::endl;


    }
}

void Seed::EnviarSequencial(rathed::Datagrama &data) {
    auto it_find = std::find_if(file.begin(), file.end(), CompareHash(data.data()));

    if (it_find.base() != nullptr && data.packnumber() > 0) {
        auto it = buffer.begin() + (data.packnumber() - 1);

        rathed::Datagrama datagrama;
        datagrama.set_type(static_cast<rathed::DatagramaType>(1));
        datagrama.set_packnumber(it.base()->packnumber());
        datagrama.set_data(it.base()->data().c_str(), it.base()->data().size());

        if (sendto(socket_fd, DataGramaSerial(datagrama), datagrama.ByteSizeLong(), 0,
                   (struct sockaddr *) &client_address, sizeof(struct sockaddr)) <= 0)
            error("Erro ao enviar 1");


        std::cout << "Total de Bytes File Enviados: " << data.packnumber() << " DE " << total_de_pacotes
                  << std::endl;
        std::cout << "Bytes File: " << datagrama.data().size() << std::endl;
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


void Seed::AtualizarRastreador(const char *&hash, const char *&path) {

    std::cout << "atualizarRastreador Seed: " << std::endl;
    std::pair<std::string, std::string> arquivo = std::make_pair(hash,
                                                                 path);
    file.push_back(arquivo);


    long fileSize_total = fileSize(path);
    std::cout << "fileSize_total: " << fileSize_total << std::endl;

    if (fileSize_total % (MAX_LENGTH_FILE) == 0) {
        total_de_pacotes = (fileSize_total / MAX_LENGTH_FILE);

    } else {
        total_de_pacotes = (fileSize_total / MAX_LENGTH_FILE) + 1;
    }
    std::cout << "total_de_pacotes: " << total_de_pacotes << std::endl;

    fd_arq = open(path, O_RDONLY, 0666);
    raw_input = new io::FileInputStream(fd_arq);
    coded_input = new io::CodedInputStream(raw_input);
    for (long j = 1; j <= total_de_pacotes; ++j) {
        int inicial = coded_input->CurrentPosition();
        coded_input->ReadRaw(recieve_data, MAX_LENGTH_FILE);
        int fim = coded_input->CurrentPosition();
        rathed::Datagrama data;
        data.set_type(static_cast<rathed::DatagramaType>(1));
        data.set_packnumber(j);
        data.set_data(recieve_data, (fim - inicial));
        buffer.push_back(data);
    }


    rathed::Datagrama _data = DataGrama(4,  arquivo.second.size(), arquivo.first.c_str());
    if (sendto(socket_fd, DataGramaSerial(_data), _data.ByteSizeLong(), 0,
               (struct sockaddr *) &rastreador_address, sizeof(struct sockaddr)) <= 0)
        error("Erro ao enviar");

}

void Seed::AtualizacaoRealizada(rathed::Datagrama &data) {
    std::cout << "TIPO: " << data.type() << "| OK |" << std::endl;
}


void Seed::ConfirmarPacote(rathed::Datagrama &data) {
    std::vector<std::string> Peers_Com_File{my_split(data.data(), '#')};
    if (Peers_Com_File.size()>1) {
        std::vector<std::string> list_apagar{my_split(Peers_Com_File[1], ';')};
        for (int j = 0; j < list_apagar.size(); ++j) {
            bool flag = true;
            auto i = buffer.begin();
            while (i != buffer.end() && i.base()->packnumber() <= std::atoi(list_apagar[j].c_str()) && flag) {
                if (i.base()->packnumber() == std::atoi(list_apagar[j].c_str()) ) {
                    buffer.erase(i);
                    total_de_pacotes = buffer.size();
                    flag = false;
                } else {
                    ++i;
                }
            }
        std::cout << "TOTAL PACKS: " << total_de_pacotes << " APAGANDO PACK: " << list_apagar[j].c_str() << " SEED: "
                  << my_port << std::endl;
        }
    }
}
