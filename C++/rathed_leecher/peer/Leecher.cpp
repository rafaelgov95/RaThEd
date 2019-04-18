//
// Created by rafael on 08/04/19.
//

#include <sstream>
#include "Leecher.h"


#include <QApplication>
#include <QMainWindow>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <google/protobuf/io/zero_copy_stream_impl.h>

namespace io = google::protobuf::io;

Leecher::~Leecher() {
    close(socket_fd);
}

Leecher::Leecher() {
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        error("socket()");
    }
    bzero(&(rastreador_address.sin_zero), 8);
    rastreador_address.sin_family = AF_INET;
    rastreador_address.sin_port = htons(rastreadorPorta);
    rastreador_address.sin_addr.s_addr = INADDR_ANY;
    address_length = sizeof(struct sockaddr); //tamanh do endereco ipv4
}


void Leecher::run(std::string hash, std::string path) {
    std::vector <std::string> total_peers = consultarRastreador(hash);
    struct sockaddr_in seed_address[total_peers.size()];
    int file_size_peers[total_peers.size()];

    for (int i = 0; i < total_peers.size(); ++i) {
        std::vector <std::string> primeiro_peer{my_split(total_peers[i], ':')};
        std::cout << "IP: " << primeiro_peer[0] << std::endl;
        std::cout << "PORTA: " << primeiro_peer[1] << std::endl;

        bzero(&(seed_address[i].sin_zero), 8);
        seed_address[i].sin_family = AF_INET;
//        inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
        seed_address[i].sin_port = htons(std::stoi(primeiro_peer[1]));
        inet_aton(primeiro_peer[0].c_str(), &seed_address[i].sin_addr);
        file_size_peers[i] = consultarFileSize(hash, seed_address[i]);
    }


    downloandP2P(seed_address[0], path, hash);
}

std::vector <std::string> Leecher::consultarRastreador(std::string hash) {
    rathed::Datagrama _data = DataGrama(2, 0, hash.c_str());
    if (sendto(socket_fd, DataGramaSerial(_data), _data.ByteSizeLong(), 0, (struct sockaddr *) &rastreador_address,
               sizeof(struct sockaddr)) <= 0)
        error("Erro ao enviar");

    usleep(200);

    bytes_read = recvfrom(socket_fd, recieve_data, MAX_LENGTH, 0, (struct sockaddr *) &rastreador_address,
                          &address_length); //block call, will wait till client enters something, before proceeding
    usleep(200);

    rathed::Datagrama datagrama;
    datagrama.ParseFromArray(recieve_data, bytes_read);
    std::cout << "DataGrama consultar Rastreador: " << datagrama.data() << std::endl;

    std::vector <std::string> Peers_Com_File{my_split(datagrama.data(), ';')};
    for (int i = 0; i < Peers_Com_File.size(); ++i) {
        std::cout << "SEED: " << Peers_Com_File[i] << std::endl;

    }
    return Peers_Com_File;
}

void Leecher::downloandP2P(sockaddr_in seed_address, std::string caminho, std::string hash) {

    int fd_arq;
    rathed::Datagrama datagrama_buff;
    fd_arq = open(caminho.c_str(), O_CREAT | O_WRONLY);
    io::ZeroCopyOutputStream *raw_output = new io::FileOutputStream(fd_arq);
    auto *coded_output = new io::CodedOutputStream(raw_output);
    int buff_int = 0, buff_data = 0, cont_ack = 0;
    bool flag = true;
    datagrama_buff = DataGrama(2, 0, hash);
    std::cout << "Pedindo Arquivo para Peer" << std::endl;
    if (sendto(socket_fd, DataGramaSerial(datagrama_buff), datagrama_buff.ByteSizeLong(), 0,
               (struct sockaddr *) &seed_address, sizeof(struct sockaddr)) <= 0)
        error("Erro ao enviar");

    while (flag) {

        bytes_read = recvfrom(socket_fd, recieve_data, MAX_LENGTH, 0, (struct sockaddr *) &seed_address,
                              &address_length);
        datagrama_buff.ParseFromArray(recieve_data, bytes_read);
        if (datagrama_buff.packnumber() >= total_bytes_file) {
            std::cout << "Foi Recebido COMANDO DE FIM!!" << std::endl;
            flag = false;
        } else {
            coded_output->WriteRaw(datagrama_buff.data().c_str(), datagrama_buff.data().size());
            buff_int += datagrama_buff.data().size();
            buff_data += bytes_read;
            cont_ack++;
            std::cout << "Total Bytes Recebido File: " << buff_int << " DE " << total_bytes_file << std::endl;
            std::cout << "Total Bytes Recebido Datagrama: " << buff_data << std::endl;

            usleep(3000);
            datagrama_buff.set_type(static_cast<rathed::DatagramaType>(2));
            datagrama_buff.set_packnumber(buff_int);
            datagrama_buff.set_data(hash);
            sendto(socket_fd, DataGramaSerial(datagrama_buff), datagrama_buff.ByteSizeLong(), 0,
                   (struct sockaddr *) &seed_address,
                   sizeof(struct sockaddr));
            usleep(3000);

        }

    }
    datagrama_buff.set_type(static_cast<rathed::DatagramaType>(1));
    datagrama_buff.set_packnumber(buff_int);
    datagrama_buff.set_data("");

    sendto(socket_fd, DataGramaSerial(datagrama_buff), datagrama_buff.ByteSizeLong(), 0,
           (struct sockaddr *) &seed_address,
           sizeof(struct sockaddr));
    std::cout << "Foi Recebido Tudo!!" << std::endl;
    delete coded_output;
    delete raw_output;
}


bool Leecher::consultarFileSize(std::string hash, sockaddr_in seed) {
    rathed::Datagrama datagrama_buff;
    datagrama_buff.set_type(static_cast<rathed::DatagramaType>(3));
    datagrama_buff.set_packnumber(0);
    datagrama_buff.set_data(hash);
    if (sendto(socket_fd, DataGramaSerial(datagrama_buff), datagrama_buff.ByteSizeLong(), 0,
               (struct sockaddr *) &seed,
               sizeof(struct sockaddr)) > 0) {
        usleep(200);
        datagrama_buff.clear_data();
        bytes_read = recvfrom(socket_fd, recieve_data, MAX_LENGTH, 0,
                              (struct sockaddr *) &seed,
                              &address_length); //block call, will wait till client enters something, before proceeding
        datagrama_buff.ParseFromArray(recieve_data, bytes_read);
        if (datagrama_buff.packnumber() >= 0) {
            return total_bytes_file = datagrama_buff.packnumber();
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}


