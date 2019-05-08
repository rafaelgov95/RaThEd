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
#define MAX_LENGTH 320

namespace io = google::protobuf::io;


struct ComparableBuffer{
    explicit ComparableBuffer(rathed::Datagrama &data):data(data){}
    rathed::Datagrama data;
    bool operator <(ComparableBuffer const& other)const{return data.packnumber()<other.data.packnumber();}
};

class Leecher {

private:
    int socket_fd, total_bytes_file[4], rastreadorPorta = 8080, numthreads = 4;
    std::thread threads[4];
    PrioritDataGramaFIFO filaBuffer;
    std::set<ComparableBuffer>tempBuffer;
    struct sockaddr_in rastreador_address;
    CamadaDeRede *camadaDeRede;
    int total_de_pacotes;

    rathed::Datagrama
    EnviarDataGramaParaRede(long tempInicial,short type, const char* hash, long bytes, struct sockaddr_in *pointer_address);

    std::vector<std::string> ConsultarRastreador(const char* hash);

    long ConsultarFileSize(const char* hash,struct sockaddr_in* pointer_address);

    void IniciarDownloadP2PSequencial(const char *hash, const char *path, struct sockaddr_in seed_address[]);

    void IniciarDownloadP2PAleatorio(const char* hash, const char* path, struct sockaddr_in seed_address[]);

    void DownloandP2P(const char* hash, long bytes, struct sockaddr_in* pointer_addresss);

public:
    Leecher();

    ~Leecher();
    long total_bytes_baixados=0,velocidade = 100;
    void Run(std::string hash, std::string path, int type_download);




};


#endif //UNTITLED_LEECHERS_H
