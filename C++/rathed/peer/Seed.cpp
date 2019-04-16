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

}

Seed::Seed(int porta) {
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        error("socket()");
    }
    FD_ZERO(&socketoriginal);
    FD_ZERO(&readfds);
    FD_SET(socket_fd, &socketoriginal);
    FD_SET(socket_fd, &readfds);
    numfd = socket_fd + 1;
    tv.tv_sec = 0;
    rastreador_address.sin_family = AF_INET;
    rastreador_address.sin_port = htons(rastreadorPorta);
    rastreador_address.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_address.sin_zero), 8);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(porta);
    server_address.sin_addr.s_addr = INADDR_ANY;
    bzero(&(rastreador_address.sin_zero), 8);

    run();

}


void Seed::run() {
    if (bind(socket_fd,
             (struct sockaddr *) &server_address, sizeof(struct sockaddr)) == -1) // atribui ip
    {
        error("bind()"); // erro se der merd@
    }

    address_length = sizeof(struct sockaddr); //tamanh do endereco ipv4

    atualizarRastreador("cc72fc24056ced9ce13a287ca1243d48","/home/rafael/Música/AlanWalker.mp3");

    while (1) {
        readfds = socketoriginal;
        int recieve = select(numfd + 1, &readfds, NULL, NULL, &tv);
        if (recieve == -1) {
            perror("Erro select"); // erro no select()
        }

        if (FD_ISSET(socket_fd, &readfds)) {
            FD_CLR(socket_fd, &readfds);
            std::cout << "Comunicação Cliente" << std::endl;
            bytes_read = recvfrom(socket_fd, recieve_data, MAX_LENGTH_DATAG, 0, (struct sockaddr *) &client_address,
                                  &address_length); //block call, will wait till client enters something, before proceeding
            rathed::Datagrama buf;
            buf.ParseFromArray(recieve_data, bytes_read);
            tratarMensagem(buf);

        }
    }
}

void Seed::tratarMensagem(rathed::Datagrama data) {
    if (data.type() == 1) {
        Desconectar();
    } else if (data.type() == 2) {
        EnviarArquivo(data);
    } else if (data.type() == 3) {
        consultaFileSize(data);
    } else if (data.type() == 4) {
        atualizacaoRealizada(data);

    }

}

void Seed::consultaFileSize(rathed::Datagrama data) {
    auto it = std::find_if(file.begin(), file.end(), CompareHash(data.data()));
    if (it.base() != nullptr && data.packnumber() >= 0) {
        bytes_total = fileSize(it.base()->second.c_str());
        std::cout << "ConsultaFile Enviado Tamanho File: " << bytes_total
                  << std::endl;
        rathed::Datagrama _data = DataGrama(1, bytes_total, data.data());
        if (sendto(socket_fd, DataGramaSerial(_data), _data.ByteSizeLong(), 0,
                   (struct sockaddr *) &client_address, sizeof(struct sockaddr)) <= 0)
            error("Erro ao enviar");
    } else {
        std::cout << "Erro Enviado Tamanho File: " << std::endl;
    }

}

void Seed::EnviarArquivo(rathed::Datagrama data) {
    auto it = std::find_if(file.begin(), file.end(), CompareHash(data.data()));
    rathed::Datagrama datagrama;

    if (it.base() != nullptr && data.packnumber() >= 0) {
        int fd_arq = open(it.base()->second.c_str(), O_RDONLY);
        int total_bytes_read = 0;
        io::ZeroCopyInputStream *raw_input = new io::FileInputStream(fd_arq);
        io::CodedInputStream *coded_input = new io::CodedInputStream(raw_input);
        total_bytes_read = data.packnumber();
        coded_input->Skip(data.packnumber());
        int antes = coded_input->CurrentPosition();
        bytes_read = coded_input->ReadRaw(send_data, MAX_LENGTH_FILE);
        int depois = coded_input->CurrentPosition();
        int size_bytes = depois - antes;
        datagrama.set_type(static_cast<rathed::DatagramaType>(1));
        datagrama.set_packnumber(data.packnumber());
        datagrama.set_data(send_data, size_bytes);
        usleep(3000);

        if (sendto(socket_fd, DataGramaSerial(datagrama), datagrama.ByteSizeLong(), 0,
                   (struct sockaddr *) &client_address, sizeof(struct sockaddr)) <= 0)
            error("Erro ao enviar 1");

        total_bytes_read += bytes_read;
        std::cout << "Total de Bytes File Enviados: " << total_bytes_read << " DE " << bytes_total << std::endl;

        std::cout << "Bytes File: " << size_bytes << std::endl;
        std::cout << "Bytes Datagrama: " << datagrama.ByteSizeLong() << std::endl;


        usleep(3000);
    } else {
        if (
                sendto(socket_fd,
                       "ERRO", sizeof("ERRO"), 0,
                       (struct sockaddr *) &client_address, sizeof(struct sockaddr)) <= 0)
            error("Erro ao enviar 2");
    }
}



void Seed::atualizarRastreador(std::string hash,std::string path) {
    std::cout << "atualizarRastreador Seed: " << std::endl;
    std::pair<std::string, std::string> arquivo = std::make_pair(hash,
                                                                 path);
    file.push_back(arquivo);

    rathed::Datagrama _data = DataGrama(4, arquivo.second.size(), arquivo.first);


    if (sendto(socket_fd, DataGramaSerial(_data), _data.ByteSizeLong(), 0,
               (struct sockaddr *) &rastreador_address, sizeof(struct sockaddr)) <= 0)
        error("Erro ao enviar");

}

void Seed::atualizacaoRealizada(rathed::Datagrama data) {
    std::cout << "TIPO: " << data.type() << "| OK |" << std::endl;

}

void Seed::Desconectar() {
    std::cout << "User desconectado" << std::endl;

}
