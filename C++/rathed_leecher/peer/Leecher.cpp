
//
// Created by rafael on 08/04/19.
//

#include "Leecher.h"

#include <utility>
#include <sstream>
#include <QApplication>
#include <QMainWindow>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <util/Temporizador.h>


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


void Leecher::Run(std::string hash, std::string path, int type_download) {
    std::vector<std::string> total_peers = ConsultarRastreador(hash.c_str());
    struct sockaddr_in seed_address[total_peers.size()];
    for (int i = 0; i < total_peers.size(); ++i) {
        std::vector<std::string> primeiro_peer{my_split(total_peers[i], ':')};
        bzero(&(seed_address[i].sin_zero), 8);
        seed_address[i].sin_family = AF_INET;
        seed_address[i].sin_port = htons(std::stoi(primeiro_peer[1]));
        inet_aton(primeiro_peer[0].c_str(), &seed_address[i].sin_addr);
        total_bytes_file[i] = ConsultarFileSize(hash.c_str(), &seed_address[i]);
        std::cout << "Teste total_bytes_file : " << total_bytes_file[i] << std::endl;

    }
    if ((total_bytes_file[0] % 310 == 0)) {
        total_de_pacotes = (total_bytes_file[0] / 310);

    } else {
        total_de_pacotes = (total_bytes_file[0] / 310) + 1;
    }


    if (type_download == 1) {
        IniciarDownloadP2PSequencial(hash.c_str(), path.c_str(), seed_address);
    } else if (type_download == 2) {
        IniciarDownloadP2PAleatorio(hash.c_str(), path.c_str(), seed_address);
    }


}

void Leecher::IniciarDownloadP2PSequencial(const char *hash, const char *path, struct sockaddr_in seed_address[]) {
    long tempInicio = 0, tempFim = 0, tempResult = 0, tempResulTotal = 0;
    int fd_arq = open(path, O_CREAT | O_WRONLY,
                      0666), bytes_file = 1, round = 0, jitter = 0, jitterImp = 0, jitterPar = 0;
    io::ZeroCopyOutputStream *raw_output = new io::FileOutputStream(fd_arq);
    auto *coded_output = new io::CodedOutputStream(raw_output);
    bool flag = true;

    while (flag) {
        round += 1;
        int threads_round = 0;
        camadaDeRede->InterfaceGetFilaBuffer().clear();
        tempInicio = MyTempMS();
        bool flag_2 = true;
        while (threads_round < numthreads && flag_2) {
            if (total_de_pacotes + 1 > bytes_file) {
                threads[threads_round] = std::thread(&Leecher::DownloandP2P, this, hash, bytes_file,
                                                     &seed_address[threads_round]);
                bytes_file += 1;
                threads_round++;
            } else {
                flag = flag_2 = false;
            }
        }
        for (int i = 0; i < threads_round; ++i) {
            threads[i].join();
        }

        while (!filaBuffer.empty()) {
            rathed::Datagrama data;
            filaBuffer.next(data);
            coded_output->WriteRaw(data.data().c_str(), data.data().size());
        }
        if (!flag_2) {
            tempFim = MyTempMS();
            tempResult = tempFim - tempInicio;
            tempResulTotal += tempResult;
            total_bytes_baixados = coded_output->ByteCount();
            velocidade = ((((numthreads * 310) / 8) / (tempResult * pow(10, -3))) * pow(10, -2));
            if ((round % 2) == 1) {
                jitterPar = tempResult;
                jitter += jitterPar - jitterImp;
                std::cout << "VELOCIDADE: " << velocidade << " KBps  "
                          << "- PING: " << tempResult << " ms - JITTER: " << jitterPar - jitterImp <<
                          " ms - PING [M]: " << (tempResulTotal / round) << " ms - JITTER [M]: " << jitter << std::endl;
            } else {
                jitterImp = tempResult;
                jitter += jitterImp - jitterPar;
                std::cout << "VELOCIDADE: " << velocidade << " KBps  "
                          << "- PING: " << tempResult << " ms - JITTER: " << jitterImp - jitterPar <<
                          " ms - PING [M]: " << (tempResulTotal / round) << " ms - JITTER [M]: " << jitter << " ms"
                          << std::endl;
            }

        }
    }


    std::cout << "FIM TOTAL DE: " << coded_output->ByteCount()<< " Bytes Gravados"<<std::endl;
    delete coded_output;
    delete raw_output;
    close(fd_arq);
}

void Leecher::IniciarDownloadP2PAleatorio(const char *hash, const char *path, sockaddr_in *seed_address) {
    long tempInicio = 0, tempFim = 0, tempResult = 0, tempResulTotal = 0;
    int fd_arq = open(path, O_CREAT | O_WRONLY,
                      0666), bytes_file = 0, round = 0, jitter = 0, jitterImp = 0, jitterPar = 0;
    io::ZeroCopyOutputStream *raw_output = new io::FileOutputStream(fd_arq);
    auto *coded_output = new io::CodedOutputStream(raw_output);
    bool flag = true;
    long inicioDownload = 1;

    std::cout << "tTtal_de_pacotes: " << total_de_pacotes << std::endl;

    while (flag) {
        round += 1;
        int threads_round = 0;
        camadaDeRede->InterfaceGetFilaBuffer().clear();
        tempInicio = MyTempMS();
        while (threads_round < numthreads && flag) {
            if (total_de_pacotes + 1 > inicioDownload) {
                threads[threads_round] = std::thread(&Leecher::DownloandP2P, this, hash, inicioDownload,
                                                     &seed_address[threads_round]);
                threads_round++;
            } else {
                std::cout << "FIM" << std::endl;
                flag = false;
            }
        }
        for (int i = 0; i < threads_round; ++i) {
            threads[i].join();
        }

        while (!filaBuffer.empty()) {
            rathed::Datagrama data;
            filaBuffer.next(data);
            tempBuffer.emplace(data);
        }
        if ((*tempBuffer.begin()).data.packnumber() == -1) {
            flag = false;
        } else {

            bool flag_entrou_gravacao = false;
            while (inicioDownload == (*tempBuffer.begin()).data.packnumber()) {
                if (flag_entrou_gravacao) {
                    tempInicio = MyTempMS();
                }
                flag_entrou_gravacao = true;
                rathed::Datagrama data = (*tempBuffer.begin()).data;
                coded_output->WriteRaw(data.data().c_str(), data.data().size());
                inicioDownload += 1;
//                std::cout << "2 Numer Pack: " << " Gravados ate Agora no Buffer: " << coded_output->ByteCount()
//                          << " Gravando Bytes: " << data.data().size() << " Packnumber: "
//                          << data.packnumber() << " inicioDownload: " << inicioDownload << std::endl;
                tempBuffer.erase(tempBuffer.begin());
                tempFim = MyTempMS();
                tempResult = tempFim - tempInicio;
                tempResulTotal += tempResult;
                total_bytes_baixados = coded_output->ByteCount();
                velocidade = (int) ((((numthreads * 310) / 8) / (tempResult * pow(10, -3))) * pow(10, -2));
                if ((round % 2) == 1) {
                    jitterPar = tempResult;
                    jitter += jitterPar - jitterImp;
                    std::cout << "VELOCIDADE: " << velocidade << " KBps  "
                              << "- PING: " << tempResult << " ms - JITTER: " << jitterPar - jitterImp <<
                              " ms - PING [M]: " << (tempResulTotal / round) << " ms - JITTER [M]: " << jitter
                              << std::endl;
                } else {
                    jitterImp = tempResult;
                    jitter += jitterImp - jitterPar;
                    std::cout << "VELOCIDADE: " << velocidade << " KBps  "
                              << "- PING: " << tempResult << " ms - JITTER: " << jitterImp - jitterPar <<
                              " ms - PING [M]: " << (tempResulTotal / round) << " ms - JITTER [M]: " << jitter << " ms"
                              << std::endl;
                }
            }
        }
    }


    std::cout << "FIM " << std::endl;
    delete coded_output;
    delete raw_output;
    close(fd_arq);
}


rathed::Datagrama
Leecher::EnviarDataGramaParaRede(long temp, short type, const char *hash, long bytes,
                                 struct sockaddr_in *pointer_address) {
    std::pair<long, rathed::Datagrama> data;
    using namespace std::chrono_literals;
    std::promise<void> done;
    std::shared_future<void> done_future(done.get_future());
    int round = 0;
    bool isTemporizador = false;
    while (true) {
        camadaDeRede->InterfaceRede(type, hash, bytes, pointer_address);
        long isTimeOutput = MyTempMS();
//        if (((isTimeOutput-temp)>10) || camadaDeRede->InterfaceGetFilaBuffer().myPack(type, bytes, data, round)) {
        if (camadaDeRede->InterfaceGetFilaBuffer().myPack(type, bytes, data, round)) {

//            if(isTemporizador) {
//                done.set_value();
//                isTemporizador=false;
//            }
            while (true) {
                long t1 = data.first;
                long t2 = MyTempMS();
                if (t1 <= t2) {
                    return data.second;
                }
//                else if((isTimeOutput-temp)>10 && type==2){
//                    return data.second;
//                }
            }
        } else {
//            isTemporizador=true;
//            Temporizador t1(done_future,10ms,camadaDeRede, type, hash,  bytes, pointer_address);
//            auto x = t1.run();
        }
    }
}


std::vector<std::string> Leecher::ConsultarRastreador(const char *hash) {
    long time = MyTempMS();
    rathed::Datagrama data = EnviarDataGramaParaRede(time, 2, hash, 0, &rastreador_address);
    std::vector<std::string> Peers_Com_File{my_split(data.data(), ';')};
    for (int i = 0; i < Peers_Com_File.size(); ++i) {
        std::cout << "SEED: " << i << ":" << Peers_Com_File[i] << std::endl;
    }
    return Peers_Com_File;

}

void Leecher::DownloandP2P(const char *hash, long bytes, sockaddr_in *seed_address) {
    long time = MyTempMS();
    filaBuffer.push(EnviarDataGramaParaRede(time, 2, hash, bytes, seed_address));
}


long Leecher::ConsultarFileSize(const char *hash, sockaddr_in *seed) {
    long time = MyTempMS();
    return EnviarDataGramaParaRede(time, 3, hash, 0, seed).packnumber();
}




