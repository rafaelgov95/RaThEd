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
    camadaDeRede = new CamadaDeRede(socket_fd, rastreador_address);
}


void Leecher::run(std::string hash, std::string path) {
    std::cout << "HASH: " << hash << std::endl;

    std::vector<std::string> total_peers = consultarRastreador(hash);
    struct sockaddr_in seed_address[total_peers.size()];
    int file_size_peers[total_peers.size()];

    for (int i = 0; i < total_peers.size(); ++i) {
        std::vector<std::string> primeiro_peer{my_split(total_peers[i], ':')};
        std::cout << "IP: " << primeiro_peer[0] << std::endl;
        std::cout << "PORTA: " << primeiro_peer[1] << std::endl;

        bzero(&(seed_address[i].sin_zero), 8);
        seed_address[i].sin_family = AF_INET;
        seed_address[i].sin_port = htons(std::stoi(primeiro_peer[1]));
        inet_aton(primeiro_peer[0].c_str(), &seed_address[i].sin_addr);
        file_size_peers[i] = consultarFileSize(hash, seed_address[i]);
    }

    std::cout << " 0" << std::endl;

    downloandP2P(seed_address[0], path, hash);
}

long Leecher::MyTempMS() {
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );
    return ms.count();
}


void Leecher::startTemporizador(std::string hash) {
    usleep(20000);
    camadaDeRede->InterfaceConsultarRastreador(hash);
}

std::vector<std::string> Leecher::consultarRastreador(std::string hash) {
    rathed::Datagrama datagrama_buff;
    camadaDeRede->InterfaceConsultarRastreador(hash);
    while (true) {
        sem_wait(&camadaDeRede->mutex);
        bool fila = camadaDeRede->filaDataGramas.empty();
        if (!fila) {

            std::pair<long, rathed::Datagrama> pair = camadaDeRede->filaDataGramas.top();
            camadaDeRede->filaDataGramas.pop();
            for (;;) {
                long t1 = pair.first;
                long t2 = MyTempMS();
                if (t1 <= t2) {
                    std::vector<std::string> Peers_Com_File{
                            my_split(pair.second.data(), ';')};
                    for (int i = 0; i < Peers_Com_File.size(); ++i) {

                        std::cout << "SEED: " << Peers_Com_File[i] << std::endl;
                    }

                    return Peers_Com_File;
                }
            }
        } else {
            camadaDeRede->InterfaceConsultarRastreador(hash);
        }
    }
}

void Leecher::downloandP2P(sockaddr_in seed_address, std::string caminho, std::string hash) {
    int fd_arq, buff_int = 0, buff_data = 0, cont_ack = 0;
    fd_arq = open(caminho.c_str(), O_CREAT | O_WRONLY,0666);
    io::ZeroCopyOutputStream *raw_output = new io::FileOutputStream(fd_arq);
    auto *coded_output = new io::CodedOutputStream(raw_output);
    bool flag_1 = true, flag_2;
    (*camadaDeRede).InterfaceDownloandP2P(hash, buff_int, seed_address);
    while (flag_1) {
        flag_2 = true;
        sem_wait(&camadaDeRede->mutex);
        bool fila = camadaDeRede->filaDataGramas.empty();
        if (!fila) {
            std::pair<long, rathed::Datagrama> pair = camadaDeRede->filaDataGramas.top();
            camadaDeRede->filaDataGramas.pop();
            while (flag_2) {
                usleep(1000);
                long t1 = pair.first;
                long t2 = MyTempMS();
                if (t1 <= t2) {
                    if (pair.second.packnumber() >= total_bytes_file) {
                        std::cout << "Foi Recebido COMANDO DE FIM!!" << std::endl;
                        flag_1 = flag_2 = false;
                    } else {
                        coded_output->WriteRaw(pair.second.data().c_str(), pair.second.data().size());
                        buff_int += pair.second.data().size();
                        buff_data += pair.second.ByteSizeLong();
                        cont_ack++;
                        std::cout << "Total Bytes Recebido File: " << buff_int << " DE " << total_bytes_file
                                  << std::endl;
                        std::cout << "Total Bytes Recebido Datagrama: " << buff_data << std::endl;
                        (*camadaDeRede).InterfaceDownloandP2P(hash, buff_int, seed_address);
                        flag_2 = false;
                    }
                }
            }
        } else {
            (*camadaDeRede).InterfaceDownloandP2P(hash, buff_int, seed_address);
        }
    }
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
                              &address_length);
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


