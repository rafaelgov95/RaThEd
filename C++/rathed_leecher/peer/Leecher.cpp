#include <utility>

#include <utility>

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
    camadaDeRede = new CamadaDeRede(socket_fd, rastreador_address);
}


void Leecher::run(const std::string& hash, std::string path) {
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
    total_bytes_file = file_size_peers[0];
    iniciaDownloadP2P(path,hash,seed_address);

}
void Leecher::iniciaDownloadP2P(const std::string& hash, const std::string& path, struct sockaddr_in seed_address[]){

    int fd_arq = open(path.c_str(), O_CREAT | O_WRONLY, 0666);
    io::ZeroCopyOutputStream *raw_output = new io::FileOutputStream(fd_arq);
    auto *coded_output = new io::CodedOutputStream(raw_output,(4*310));
    int buff_count = 0, round = 0;
    bool flag = true;
    while (flag) {
        round += 1;
        int threads_round = 0;
        camadaDeRede->get_FilaBuffer();
        for (int i = 0; i < 4; ++i) {
            if (total_bytes_file > buff_count) {
                threads[i] = std::thread(&Leecher::downloandP2P, this, seed_address[i], hash, buff_count);
                std::cout <<"TOTAL: "<<total_bytes_file<<" Thread " << i << "PACK: " << buff_count << std::endl;
                buff_count += 310;
                threads_round++;

            } else {
                i = 5;
                flag = false;
            }

        }
        for (int j = 0; j < threads_round; ++j) {
            threads[j].join();
        }


        while (!filaBuffer.empty()) {
            rathed::Datagrama data;
            filaBuffer.next(data);
            std::cout << "Gravando PACOTE: " << data.packnumber() << std::endl;
            coded_output->WriteRaw(data.data().c_str(), data.data().size());
        }
    }
    std::cout << "FIM " << std::endl;

    delete coded_output;
    delete raw_output;
    close(fd_arq);
}


long Leecher::MyTempMS() {
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );
    return ms.count();
}

std::vector<std::string> Leecher::consultarRastreador(const std::string& hash) {
    camadaDeRede->InterfaceConsultarRastreador(hash);
    while (true) {
        bool fila = camadaDeRede->get_FilaBuffer().empty();
        if (!fila) {
            std::pair<long, rathed::Datagrama> pair = camadaDeRede->get_FilaBuffer().top();
            camadaDeRede->get_FilaBuffer().pop();
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

void Leecher::downloandP2P(sockaddr_in seed_address, const std::string& hash, long number_pack) {

    bool flag_1 = true, flag_2;
    while (flag_1) {
        flag_2 = true;
        std::pair<long, rathed::Datagrama> pair;
        if (camadaDeRede->get_FilaBuffer().myPack(number_pack, pair)) {
            while (flag_2) {
                long t1 = pair.first;
                long t2 = MyTempMS();
                if (t1 <= t2) {
                    filaBuffer.push(pair.second);
                    std::cout << "Pacote: " << pair.second.packnumber() << " Copiado" << std::endl;
                    flag_1 = flag_2 = false;
                } else {
                }
            }
        } else {
            std::cout << "AQUI: " <<std::endl;
            camadaDeRede->InterfaceDownloandP2P(hash, number_pack, seed_address);
        }

    }
}


long Leecher::consultarFileSize(const std::string& hash, sockaddr_in seed) {
    camadaDeRede->InterfaceConsultarFileSize(hash, 0, seed);
    while (true) {
        bool fila = camadaDeRede->get_FilaBuffer().empty();
        if (!fila) {
            std::pair<long, rathed::Datagrama> pair = camadaDeRede->get_FilaBuffer().top();
            camadaDeRede->get_FilaBuffer().pop();
            for (;;) {
                long t1 = pair.first;
                long t2 = MyTempMS();
                if (t1 <= t2) {
                    return pair.second.packnumber();
                }
            }
        } else {
            camadaDeRede->InterfaceConsultarFileSize(hash, 0, seed);
        }
    }
}




