
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


Leecher::~Leecher() {
    free(threads);
    free(total_bytes_file);
    free(seed_address);
    delete camadaDeRede;
    close(socket_fd);
    ofs->close();
}

void Leecher::ConfigFileDownload(const char *hash_, const char *path_, const char *log, const char *log_player_) {
    path = (char *) malloc(strlen(path_));
    hash = (char *) malloc(strlen(hash_));
    log_player = (char *) malloc(strlen(log_player_));

    ofs = new std::ofstream(log, std::ofstream::out);

    strcpy((char *) path, path_);
    strcpy((char *) hash, hash_);
    strcpy((char *) log_player, log_player_);

}


Leecher::Leecher(int peers, int tipo_download, int rastreador_porta, int rtt, int e, int falha) : tipo_download(
        tipo_download),
                                                                                                  rastreador_porta(
                                                                                                          rastreador_porta),
                                                                                                  numthreads(peers),
                                                                                                  rtt(rtt) {

    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        error("socket()");
    }
    bzero(&(rastreador_address.sin_zero), 8);
    rastreador_address.sin_family = AF_INET;
    rastreador_address.sin_port = htons(rastreador_porta);
    rastreador_address.sin_addr.s_addr = INADDR_ANY;
    camadaDeRede = new CamadaDeRede(socket_fd, rastreador_address, rtt, e, falha);
    threads = (std::thread *) malloc(sizeof(std::thread) * peers);
    total_bytes_file = (int *) malloc(sizeof(int) * peers);
}


void Leecher::run() {
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
    int fileSize_total = total_bytes_file[0];

    if (fileSize_total % (MAX_LENGTH_FILE) == 0) {
        total_de_pacotes = (fileSize_total / (MAX_LENGTH_FILE));

    } else {
        total_de_pacotes = (fileSize_total / (MAX_LENGTH_FILE)) + 1;
    }

    if (tipo_download == 1) {
        IniciarDownloadP2PSequencial();
    } else if (tipo_download == 2) {
        IniciarDownloadP2PAleatorio();
    }


}

void StarPlay(const char *path, const char *log, int total_bytes_file) {
    Player player(path, log, total_bytes_file);
    player.run();

}

void Leecher::IniciarDownloadP2PSequencial() {
    double tempInicioFile = 0, tempFimFile, tempInicio = 0, tempFim = 0, tempResult = 0, tempResulTotal = 0, jitter = 0, jitterImp = 0, jitterPar = 0;
    int fd_arq = open(path, O_CREAT | O_WRONLY,
                      0666), num_pacote = 1, round = 0;
    int cont_packs = 0;
    io::ZeroCopyOutputStream *raw_output = new io::FileOutputStream(fd_arq, 305);
    auto *coded_output = new io::CodedOutputStream(raw_output);
    std::pair<double, int> tempInicioPack[numthreads];
    bool flag, flag_2;
    flag = flag_2 = true;
    tempInicioFile = MyTempMiS_();
    long byts_anterior = 0;
    std::thread thread_player;
    while (flag) {
        round += 1;
        int threads_round = 0;
        camadaDeRede->InterfaceGetFilaBuffer().clear();
//        tempInicio = MyTempMiS_();
        while (threads_round < numthreads && flag_2) {
            if (total_de_pacotes + 1 > num_pacote) {
                threads[threads_round] = std::thread(&Leecher::RequisicaoP2P, this, 1, hash, num_pacote, seed_address[threads_round]);
                tempInicioPack[threads_round] = std::make_pair(MyTempMiS_(), num_pacote);
                num_pacote += 1;
                threads_round++;
            } else {
                flag = flag_2 = false;
            }

        }
        for (int i = 0; i < threads_round; ++i) {
            threads[i].join();
        }
        byts_anterior = coded_output->ByteCount();

        while (!filaBuffer.empty()) {
            rathed::Datagrama data;
            filaBuffer.next(data);
            double temp_print_log = 0;
            for (int i = 0; i < numthreads; ++i) {
                if (tempInicioPack[i].second == data.packnumber()) {
                    temp_print_log = tempInicioPack[i].first;
                }
            }

            coded_output->WriteRaw(data.data().c_str(), data.data().size());

            if (flag_2) {
                tempFim = MyTempMiS_();
                tempResult = tempFim - temp_print_log;
                tempResulTotal += tempResult;

                total_bytes_baixados = coded_output->ByteCount();

                velocidade_media = ((total_bytes_baixados / ((double) ((tempFim - tempInicioFile) * pow(10, -6)))) *
                                    pow(10, -3));
                int bytes_resut = (total_bytes_baixados - byts_anterior);
                velocidade = (((bytes_resut) / ((double) (tempResult * pow(10, -6)))) * pow(10, -3));

                *ofs << data.packnumber() << ";" << velocidade_media << ";" << (long) temp_print_log << ";"
                     << (long) tempFim << ";" << std::endl;
                if ((round % 2) == 1) {
                    jitterPar = tempResult;
                    jitter += jitterPar - jitterImp;
                    std::cout << "VELOCIDADE: " << velocidade << " KBps VELOCIDADE [M]: " << velocidade_media
                              << " KBps  "
                              << "- PING: " << (tempResult / 1000) << " ms - JITTER: " << (jitterPar - jitterImp) / 1000
                              <<
                              " ms - PING [M]: " << ((tempResulTotal / 1000) / round) << " ms - JITTER [M]: "
                              << jitter / 1000 << std::endl;

                } else {
                    jitterImp = tempResult;
                    jitter += jitterImp - jitterPar;
                    std::cout << "VELOCIDADE: " << velocidade << " KBps VELOCIDADE [M]: " << velocidade_media
                              << " KBps  "
                              << "- PING: " << (tempResult / 1000) << " ms - JITTER: " << (jitterImp - jitterPar) / 1000
                              <<
                              " ms - PING [M]: " << ((tempResulTotal / 1000) / round) << " ms - JITTER [M]: "
                              << jitter / 1000 << " ms"
                              << std::endl;

                }
                cont_packs++;


            }

        }
        if (round == 2) {
            thread_player = std::thread(StarPlay, path, log_player, total_bytes_file[0]);
        }

    }

    tempFimFile = MyTempMiS_();
    std::cout << "TAMANHO FINAL DO AUDIO: " << coded_output->ByteCount() << " Bytes Gravados" << " em: "
              << ((tempFimFile - tempInicioFile) / 1000000) << " segundos" << std::endl;
    std::cout << "TAXA DE GRAVACAO: "
              << ((coded_output->ByteCount()) / ((tempFimFile - tempInicioFile) / 1000000)) / 1000 << " KBytes/s"
              << std::endl;

    *ofs << "TAMANHO FINAL DO AUDIO: " << coded_output->ByteCount() << " Bytes Gravados" << " em: "
         << ((tempFimFile - tempInicioFile) / 1000000) << " segundos" << std::endl;
    *ofs << "TAXA DE GRAVACAO: " << ((coded_output->ByteCount()) / ((tempFimFile - tempInicioFile) / 1000000)) / 1000
         << " KBytes/s" << std::endl;

    delete coded_output;
    delete raw_output;
    close(fd_arq);
    thread_player.join();
}


void Leecher::IniciarDownloadP2PAleatorio() {
    double tempInicioFile, tempFimFile, tempInicio = 0, tempFim = 0, tempResult = 0, tempResulTotal = 0, jitter = 0, jitterImp = 0, jitterPar = 0;
    int fd_arq = open(path, O_CREAT | O_WRONLY,
                      0666), num_pacote = 1, round = 0;
    io::ZeroCopyOutputStream *raw_output = new io::FileOutputStream(fd_arq, 305);
    auto *coded_output = new io::CodedOutputStream(raw_output);
    bool flag = true, flag_confirma;
    int byts_anterior = 0, num_pacote_ultimo = 0;
    round = 1;

    std::thread thread_player;
    tempInicioFile = MyTempMiS_();
    rathed::Datagrama data;

    while (flag) {
        int threads_round = 0;
        camadaDeRede->InterfaceGetFilaBuffer().clear();
        if (num_pacote > num_pacote_ultimo) {
            tempInicio = MyTempMiS_();
            num_pacote_ultimo = num_pacote;
        }
        std::string tmp="#";
        while (!filaConfirma.empty()) {
            tmp += std::to_string((*filaConfirma.begin()));
            tmp += ";";
            filaConfirma.erase((*filaConfirma.begin()));
        }
        std::string new_hash =hash;
        new_hash+=tmp;
        while (threads_round < numthreads && flag) {

            if (total_de_pacotes + 1 > num_pacote) {

                threads[threads_round] = std::thread(&Leecher::RequisicaoP2P, this, 2, new_hash.c_str(), num_pacote,
                                                     seed_address[threads_round]);
                threads_round++;
            } else {
                flag = false;
            }
        }

        for (int i = 0; i < threads_round; ++i) {
            threads[i].join();
        }

        while (!filaBuffer.empty()) {
            filaBuffer.next(data);

//            filaConfirma.emplace(data);
            filaConfirma.emplace(data.packnumber());
            if (data.packnumber() >= num_pacote) {
                setBuffer.emplace(data);
            }
        }

        if ((*setBuffer.begin()).data.packnumber() == -1) {
            flag = false;
        } else {

            bool flag_entrou_gravacao = false;
            while (setBuffer.begin() != setBuffer.end() && num_pacote == (*setBuffer.begin()).data.packnumber() &&
                   flag) {

                if (flag_entrou_gravacao) {
                    tempInicio = MyTempMiS_();
                }

                flag_entrou_gravacao = true;
                byts_anterior = coded_output->ByteCount();
                coded_output->WriteRawMaybeAliased((*setBuffer.begin()).data.data().c_str(),
                                                   (*setBuffer.begin()).data.data().size());

                setBuffer.erase(setBuffer.begin());
                num_pacote += 1;
                tempFim = MyTempMiS_();
                tempResult = (tempFim - tempInicio);
                tempResulTotal += tempResult;
                total_bytes_baixados = coded_output->ByteCount();
                velocidade_media = ((total_bytes_baixados / ((double) ((tempFim - tempInicioFile) * pow(10, -6)))) *
                                    pow(10, -3));
                int bytes_resut = (total_bytes_baixados - byts_anterior);
                velocidade = ((double) ((double) (bytes_resut) / ((double) (tempResult * pow(10, -6)))) * pow(10, -3));
                if ((round % 2) == 1) {
                    jitterPar = tempResult;
                    jitter += jitterPar - jitterImp;
                    std::cout << "VELOCIDADE: " << velocidade << " KBps VELOCIDADE [M]: " << velocidade_media
                              << " KBps  "
                              << "- PING: " << (tempResult / 1000) << " ms - JITTER: " << (jitterPar - jitterImp) / 1000
                              <<
                              " ms - PING [M]: " << ((tempResulTotal / 1000) / round) << " ms - JITTER [M]: "
                              << (jitter / 1000) << std::endl;
                } else {
                    jitterImp = tempResult;
                    jitter += jitterImp - jitterPar;
                    std::cout << "VELOCIDADE: " << velocidade << " KBps VELOCIDADE [M]: " << velocidade_media
                              << " KBps  "
                              << "- PING: " << (tempResult / 1000) << " ms - JITTER: " << (jitterImp - jitterPar) / 1000
                              <<
                              " ms - PING [M]: " << ((tempResulTotal / 1000) / round) << " ms - JITTER [M]: "
                              << jitter / 1000 << " ms"
                              << std::endl;


                }
                *ofs << velocidade_media << std::endl;
                if (round == 1) {
                    thread_player = std::thread(StarPlay, path, log_player, total_bytes_file[0]);
                }
                round += 1;
            }
        }
    }
    tempFimFile = MyTempMiS_();
    std::cout << "TAMANHO FINAL DO AUDIO: " << coded_output->ByteCount() << " Bytes Gravados" << " em: "
              << ((tempFimFile - tempInicioFile) * pow(10, -6)) << " segundos" << std::endl;
    std::cout << "TAXA DE GRAVACAO: "
              << ((coded_output->ByteCount() / ((tempFim - tempInicioFile) * pow(10, -6))) * pow(10, -3)) << " KBytes/s"
              << std::endl;
//
    *ofs << "TAMANHO FINAL DO AUDIO: " << coded_output->ByteCount() << " Bytes Gravados" << " em: "
         << ((tempFimFile - tempInicioFile) / 1000000) << " segundos" << std::endl;
    *ofs << "TAXA DE GRAVACAO: "
         << ((coded_output->ByteCount()) / ((tempFimFile - tempInicioFile) / 1000000)) / 1000
         << " KBytes/s" << std::endl;

    delete coded_output;
    delete raw_output;
    close(fd_arq);
    thread_player.join();

}


rathed::Datagrama
Leecher::EnviarDataGramaParaRede(int type_dow, const rathed::Datagrama &data_,
                                 struct sockaddr_in &pointer_address) {
    std::pair<long, rathed::Datagrama> data;
    using namespace std::chrono_literals;
    int round = rtt;
    while (true) {
        if (round == rtt) {
            camadaDeRede->InterfaceRede(data_, pointer_address);
        }
        if (camadaDeRede->InterfaceGetFilaBuffer().myPack(data_.type(), data_.packnumber(), data, type_dow,
                                                          round)) {
            long t1 = MyTempMS();
            int tempoEspera = (t1 - data.first) * -1000;
            tempoEspera > 0 ?: tempoEspera = 0;
            usleep(tempoEspera);
            return data.second;
        } else {
            usleep(1000);
            round -= 1;
            if (round < 0) {
                round = rtt;
            }
        }
    }
}


std::vector<std::string> Leecher::ConsultarRastreador(const char *hash) {
    rathed::Datagrama data;
    data.set_type(static_cast<rathed::DatagramaType>(2));
    data.set_packnumber(0);
    data.set_data(hash, strlen(hash));
    data = EnviarDataGramaParaRede(1, data, rastreador_address);
    std::vector<std::string> Peers_Com_File{my_split(data.data(), ';')};
    for (int i = 0; i < Peers_Com_File.size(); ++i) {
        std::cout << "SEED: " << i << ":" << Peers_Com_File[i] << std::endl;
    }
    return Peers_Com_File;

}

void
Leecher::RequisicaoP2P(int type_down, const char *hash, int pack_number, struct sockaddr_in seed) {
    rathed::Datagrama data = DataGrama(2, pack_number, hash);
    filaBuffer.push(EnviarDataGramaParaRede(type_down, data, seed));
}


long Leecher::ConsultarFileSize(const char *hash, sockaddr_in &seed) {
    rathed::Datagrama data = DataGrama(3, 0, hash);
    return EnviarDataGramaParaRede(1, data, seed).packnumber();
}




