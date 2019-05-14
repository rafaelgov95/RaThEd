
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


void Leecher::Run(const char *hash, const char *path, int type_download) {
    std::vector<std::string> total_peers = ConsultarRastreador(hash);
    seed_address = (struct sockaddr_in *) malloc(total_peers.size() * sizeof(struct sockaddr_in));
    for (int i = 0; i < total_peers.size(); ++i) {
        std::vector<std::string> primeiro_peer{my_split(total_peers[i], ':')};
        bzero(&(seed_address[i].sin_zero), 8);
        seed_address[i].sin_family = AF_INET;
        seed_address[i].sin_port = htons(std::stoi(primeiro_peer[1]));
        inet_aton(primeiro_peer[0].c_str(), &seed_address[i].sin_addr);
        total_bytes_file[i] = ConsultarFileSize(hash, seed_address[i]);
        std::cout << "Teste total_bytes_file : " << total_bytes_file[i] << std::endl;

    }
    long fileSize_total = total_bytes_file[0];

    if ( fileSize_total %  (MAX_LENGTH_FILE) == 0) {
        total_de_pacotes = (fileSize_total /  (MAX_LENGTH_FILE));

    } else {
        total_de_pacotes = (fileSize_total /   (MAX_LENGTH_FILE)) + 1;
    }

//    std::cout << "Total de pacotes : " << total_de_pacotes << std::endl;

    if (type_download == 1) {
        IniciarDownloadP2PSequencial(hash, path, seed_address);
    } else if (type_download == 2) {
        IniciarDownloadP2PAleatorio(hash, path, seed_address);
    }


}

void Leecher::IniciarDownloadP2PSequencial(const char *hash, const char *path, struct sockaddr_in *pointer_address) {
    long tempInicio = 0, tempFim = 0, tempResult = 0, tempResulTotal = 0;
    int fd_arq = open(path, O_CREAT | O_WRONLY,
                      0666), num_pacote = 1, round = 0, jitter = 0, jitterImp = 0, jitterPar = 0;
    io::ZeroCopyOutputStream *raw_output = new io::FileOutputStream(fd_arq);
    auto *coded_output = new io::CodedOutputStream(raw_output);
    bool flag, flag_2;
    flag = flag_2 = true;

    while (flag) {
        round += 1;
        int threads_round = 0;
        camadaDeRede->InterfaceGetFilaBuffer().clear();
        tempInicio = MyTempMS();
        while (threads_round < numthreads && flag_2) {
            if (total_de_pacotes + 1 > num_pacote) {
                threads[threads_round] = std::thread(&Leecher::RequisicaoP2P, this, 1, hash, num_pacote,pointer_address[threads_round]);
                num_pacote += 1;
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
//            std::cout << "BYTES PACK: " << data.ByteSize() <<std::endl;
//            std::cout << "BYTES data() PACK: " << data.data().size() <<std::endl;
//            std::cout << "BYTES data() APACKNUMBER: " << sizeof(data.packnumber()) <<std::endl;
//            std::cout << "GRAVANDO BYTES: " << data.data().size() <<std::endl;

            coded_output->WriteRaw(data.data().c_str(), data.data().size());
        }
        if (flag_2) {
            tempFim = MyTempMS();
            tempResult = tempFim - tempInicio;
            tempResulTotal += tempResult;
            total_bytes_baixados = coded_output->ByteCount();
            velocidade += ((((numthreads * 320)) / (tempResult * pow(10, -3))) * pow(10, -2));
            if ((round % 2) == 1) {
                jitterPar = tempResult;
                jitter += jitterPar - jitterImp;
                std::cout << "VELOCIDADE: " << velocidade/round << " KBps  "
                          << "- PING: " << tempResult << " ms - JITTER: " << jitterPar - jitterImp <<
                          " ms - PING [M]: " << (tempResulTotal / round) << " ms - JITTER [M]: " << jitter << std::endl;
            } else {
                jitterImp = tempResult;
                jitter += jitterImp - jitterPar;
                std::cout << "VELOCIDADE: " << velocidade/round << " KBps  "
                          << "- PING: " << tempResult << " ms - JITTER: " << jitterImp - jitterPar <<
                          " ms - PING [M]: " << (tempResulTotal / round) << " ms - JITTER [M]: " << jitter << " ms"
                          << std::endl;
            }

        }
    }


    std::cout << "FIM TOTAL DE: " << coded_output->ByteCount() << " Bytes Gravados" << std::endl;
    delete coded_output;
    delete raw_output;
    close(fd_arq);
}


void Leecher::IniciarDownloadP2PAleatorio(const char *hash, const char *path, struct sockaddr_in *pointer_address) {
    long tempInicio = 0, tempFim = 0, tempResult = 0, tempResulTotal = 0;
    int fd_arq = open(path, O_CREAT | O_WRONLY,
                      0666), num_pacote = 1, round = 0, jitter = 0, jitterImp = 0, jitterPar = 0;
    io::ZeroCopyOutputStream *raw_output = new io::FileOutputStream(fd_arq);
    auto *coded_output = new io::CodedOutputStream(raw_output);
    bool flag = true;

    round = 1;
    while (flag) {
        int threads_round = 0;
        camadaDeRede->InterfaceGetFilaBuffer().clear();
        tempInicio = MyTempMS();
        while (threads_round < numthreads && flag) {
            if (total_de_pacotes + 1 > num_pacote) {
                threads[threads_round] = std::thread(&Leecher::RequisicaoP2P, this, 2, hash, num_pacote, pointer_address[threads_round]);
                threads_round++;
            } else {
                flag = false;
            }
        }
        for (int i = 0; i < threads_round; ++i) {
            threads[i].join();
        }

        while (!filaBuffer.empty()) {
            rathed::Datagrama data;
            rathed::Datagrama data_;
            filaBuffer.next(data);
            filaConfirma.push(data);
            if (data.packnumber() >= num_pacote) {
                setBuffer.emplace(data);

            }

        }
        camadaDeRede->InterfaceGetFilaBuffer().clear();
        ConfirmarPacotes(hash, num_pacote);
        camadaDeRede->InterfaceGetFilaBuffer().clear();

        if ((*setBuffer.begin()).data.packnumber() == -1) {
            flag = false;
        } else {

            bool flag_entrou_gravacao = false;
            while (num_pacote == (*setBuffer.begin()).data.packnumber() && !setBuffer.empty() && flag ) {
                if (flag_entrou_gravacao) {
                    tempInicio = MyTempMS();
//                    std::cout << "T2 Inicio " << tempInicio << std::endl;
                }

                flag_entrou_gravacao = true;
                rathed::Datagrama data = (*setBuffer.begin()).data;
                coded_output->WriteRaw(data.data().c_str(), data.data().size());
                num_pacote += 1;
//                std::cout << "2 Numer Pack: " << " Gravados ate Agora no Buffer: " << coded_output->ByteCount()
//                          << " Gravando Bytes: " << data.data().size() << " Packnumber: "
//                          << data.packnumber() << " inicioDownload: " << num_pacote << std::endl;
                setBuffer.erase(setBuffer.begin());
                tempFim = MyTempMS();


                tempResult = tempFim - tempInicio;
                tempResulTotal += tempResult;

//                std::cout << "T1 FIM " << tempFim << std::endl;
//                std::cout << "T1 RESULT " << tempResult << std::endl;

//                std::cout <<"PACKNUMER: "<<data.packnumber() <<"Tamanho Data Size: "<<data.data().size() << "total_bytes_baixados: " << total_bytes_baixados <<std::endl;

                total_bytes_baixados = coded_output->ByteCount();
                velocidade = ((((double) (numthreads * 310) ) / (tempResult * pow(10, -3))) * pow(10, -2));
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
                round += 1;
            }
        }
    }


    std::cout << "FIM TOTAL DE: " << coded_output->ByteCount() << " Bytes Gravados" << std::endl;
    delete coded_output;
    delete raw_output;
    close(fd_arq);
}

void Leecher::ConfirmarPacotes(const char *hash, int num_send) {
    int threads_round = 0;
    while (!filaConfirma.empty()) {
        int porta = 0;
        rathed::Datagrama data = filaConfirma.front();
        for (int j = 0; j < numthreads; ++j) {
            if (ntohs(seed_address[j].sin_port) == data.seqnumber()) {
                porta = j;
            }
        }
        threads[threads_round] = std::thread(&Leecher::ConfirmaRequisicaoP2P, this, 2, data, seed_address[porta]);
        filaConfirma.pop();
        threads_round++;
    }

    for (int i = 0; i < threads_round; ++i) {
        threads[i].join();
    }
    filaBuffer.clear();
}

rathed::Datagrama
Leecher::EnviarDataGramaParaRede(int type_dow, const rathed::Datagrama& data_, struct sockaddr_in &pointer_address) {
    std::pair<long, rathed::Datagrama> data;
    using namespace std::chrono_literals;
    int round = 4;
    while (true) {
        if (round == 4) {
            camadaDeRede->InterfaceRede(data_, pointer_address);
//           if(type==1){
//               std::cout<<"Enviando Confirmacao PACKS: "<<numpacote<<std::endl;
//           }else if(type==2){
//               std::cout<<"Enviando PACKS: "<<numpacote<<std::endl;
//           }


        }
        if (camadaDeRede->InterfaceGetFilaBuffer().myPack(data_.type(), data_.packnumber(), data, type_dow, round)) {
            long t1 = MyTempMS();
            int tempoEspera = (t1 - data.first) * -1000;
            tempoEspera > 0 ?: tempoEspera = 0;
            usleep(tempoEspera);
            return data.second;
        } else {
            usleep(10 * round);
            round -= 1;
            if (round < 0) {
                round = 4;
            }
        }
    }
}


std::vector<std::string> Leecher::ConsultarRastreador(const char *hash) {
    rathed::Datagrama data;
    data.set_type(static_cast<rathed::DatagramaType>(2));
    data.set_packnumber(0);
    data.set_data(hash);
    data = EnviarDataGramaParaRede(1, data, rastreador_address);
    std::vector<std::string> Peers_Com_File{my_split(data.data(), ';')};
    for (int i = 0; i < Peers_Com_File.size(); ++i) {
        std::cout << "SEED: " << i << ":" << Peers_Com_File[i] << std::endl;
    }
    return Peers_Com_File;

}

void Leecher::RequisicaoP2P(int type_down, const char *hash, long num_pacote, struct sockaddr_in seed) {
    rathed::Datagrama data;
    data.set_type(static_cast<rathed::DatagramaType>(2));
    data.set_packnumber(num_pacote);
    data.set_data(hash);
    filaBuffer.push(EnviarDataGramaParaRede(type_down,data,seed));
}

void Leecher::ConfirmaRequisicaoP2P(int type_down, const rathed::Datagrama& data, struct sockaddr_in seed) {
    filaBuffer.push(EnviarDataGramaParaRede(type_down,data,seed));
}

long Leecher::ConsultarFileSize(const char *hash, sockaddr_in &seed) {
    rathed::Datagrama data;
    data.set_type(static_cast<rathed::DatagramaType>(3));
    data.set_packnumber(0);
    data.set_data(hash);
    return EnviarDataGramaParaRede(1, data, seed).packnumber();
}




