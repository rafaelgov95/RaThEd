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
    free(camadaDeRede);
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


void Leecher::Run(const std::string& hash, const std::string& path) {
    std::vector<std::string> total_peers = ConsultarRastreador(hash);
    struct sockaddr_in seed_address[total_peers.size()];

    for (int i = 0; i < total_peers.size(); ++i) {
        std::vector<std::string> primeiro_peer{my_split(total_peers[i], ':')};
        std::cout << "IP: " << primeiro_peer[0] << std::endl;
        std::cout << "PORTA: " << primeiro_peer[1] << std::endl;
        bzero(&(seed_address[i].sin_zero), 8);
        seed_address[i].sin_family = AF_INET;
        seed_address[i].sin_port = htons(std::stoi(primeiro_peer[1]));
        inet_aton(primeiro_peer[0].c_str(), &seed_address[i].sin_addr);
        total_bytes_file[i] = ConsultarFileSize(hash, seed_address[i]);
    }

    IniciarDownloadP2P(hash,path,seed_address);

}
void Leecher::IniciarDownloadP2P(const std::string& hash, const std::string& path, struct sockaddr_in seed_address[]){

    int fd_arq = open(path.c_str(), O_CREAT | O_WRONLY, 0666);
    io::ZeroCopyOutputStream *raw_output = new io::FileOutputStream(fd_arq);
    auto *coded_output = new io::CodedOutputStream(raw_output);
    int buff_count = 0, round = 0;
    bool flag = true;
    long tempInicio,tempFim,tempResult;
    while (flag) {
        round += 1;
        int threads_round = 0;
        camadaDeRede->get_FilaBuffer().clear();
        while (threads_round < 4) {
             tempInicio=MyTempMS();
            if (total_bytes_file[0] > buff_count) {
                threads[threads_round] = std::thread(&Leecher::DownloandP2P, this, seed_address[threads_round], hash, buff_count);
                std::cout <<"TOTAL: "<<total_bytes_file<<" Thread " << threads_round << "PACK: " << buff_count << std::endl;
                buff_count += 310;
                threads_round++;
            } else {
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
        tempFim=MyTempMS();
        tempResult=tempFim-tempInicio;
        std::cout << "Gravado em : " <<tempResult << std::endl;

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

std::vector<std::string> Leecher::ConsultarRastreador(const std::string& hash) {
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

                        std::cout << "SEED: "<< i << ":" << Peers_Com_File[i] << std::endl;
                    }

                    return Peers_Com_File;
                }
            }
        } else {
            camadaDeRede->InterfaceConsultarRastreador(hash);
        }
    }
}

void Leecher::DownloandP2P(const std::string& hash, long bytes, sockaddr_in seed_address,) {

    bool flag_1 = true, flag_2;
    while (flag_1) {
        flag_2 = true;
        std::pair<long, rathed::Datagrama> data;
        if (camadaDeRede->get_FilaBuffer().myPack(bytes, data)) {
            while (flag_2) {
                long t1 = data.first;
                long t2 = MyTempMS();
                if (t1 <= t2) {
                    filaBuffer.push(data.second);
                    std::cout << "Pacote: " << data.second.packnumber() << " Copiado" << std::endl;
                    flag_1 = flag_2 = false;
                } else {
                }
            }
        } else {
            camadaDeRede->InterfaceDownloandP2P(hash, bytes, seed_address);
        }

    }
}


long Leecher::ConsultarFileSize(const std::string& hash, sockaddr_in seed) {
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




