#include <utility>

//
// Created by rafael on 08/04/19.
//

#ifndef UNTITLED_LEECHERS_H
#define UNTITLED_LEECHERS_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/fcntl.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <math.h>
#include <semaphore.h>
#include "thread"
#include "pthread.h"
#include "vector"
#include "iostream"
#include "util.h"
#include "model.pb.h"
#include "PrioritDataGramaFIFO.h"

#include "CamadaDeRede.h"
#include <assert.h>
#include <chrono>
#include <future>
#include <QtCore/QString>
#include <set>

#define MAX_LENGTH (320*8)
#define MAX_LENGTH_FILE ((320*8)-10)

#include <stack>

namespace io = google::protobuf::io;


class Leecher {

private:
    int socket_fd, total_bytes_file[4], total_de_pacotes, rastreadorPorta = 8080, numthreads = 4;
    std::thread threads[4];
    PrioritDataGramaFIFO filaBuffer;
    std::queue<rathed::Datagrama> filaConfirma;
    std::set<ComparableBuffer> setBuffer;
    struct sockaddr_in rastreador_address, *seed_address;
    CamadaDeRede *camadaDeRede;


    rathed::Datagrama
    EnviarDataGramaParaRede(int type_down, const rathed::Datagrama &data_, struct sockaddr_in &memory_seed_address);

    std::vector<std::string> ConsultarRastreador(const char *hash);

    long ConsultarFileSize(const char *hash, struct sockaddr_in &pointer_address);

    void IniciarDownloadP2PSequencial(const char *hash, const char *path, struct sockaddr_in *pointers_address);

    void IniciarDownloadP2PAleatorio(const char *hash, const char *path, struct sockaddr_in *pointer_address);

    void RequisicaoP2P(int type_down, const char *hash, long num_pacote, struct sockaddr_in seed_address);

//    overload RequisicaoP2P; // This is optional

    void ConfirmaRequisicaoP2P(int type_down, const rathed::Datagrama& data_, struct sockaddr_in seed_address);

    void ConfirmarPacotes(const char *hash, int num_pack);

public:
    Leecher();

    ~Leecher();


    double total_bytes_baixados = 0, velocidade = 100;
    void Run(const char *hash, const char *path, int type_download);


};


#endif //UNTITLED_LEECHERS_H
