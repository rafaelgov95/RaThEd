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
#define MAX_LENGTH (320)
#define MAX_LENGTH_FILE (320-15)


#include <stack>
#include <QtCore>


namespace io = google::protobuf::io;



class Leecher :public QThread{

private:
   const  char *hash, *path;
    int tipo_download,socket_fd, total_bytes_file[4], total_de_pacotes, rastreador_porta, numthreads = 4,total_bytes_baixados;
    std::thread threads[4];
    PrioritDataGramaFIFO filaBuffer;
    PrioritDataGramaFIFO filaConfirma;
    std::set<ComparableBuffer> setBuffer;
    struct sockaddr_in rastreador_address, *seed_address;
    CamadaDeRede *camadaDeRede;


    rathed::Datagrama
    EnviarDataGramaParaRede(int type_down, const rathed::Datagrama &data_, struct sockaddr_in &memory_seed_address);

    std::vector<std::string> ConsultarRastreador(const char *hash);

    long ConsultarFileSize(const char *hash, struct sockaddr_in &pointer_address);

    void IniciarDownloadP2PSequencial( const char *hash, const char *path, struct sockaddr_in *pointers_address);

    void IniciarDownloadP2PAleatorio( const char *hash, const  char *path, struct sockaddr_in *pointer_address);

    void RequisicaoP2P(int type_down, const char *hash, int num_pacote, struct sockaddr_in seed_address);

    void ConfirmaRequisicaoP2P(int type_down, const rathed::Datagrama& data_, struct sockaddr_in seed_address);

    void ConfirmarPacotes(const char *hash, int num_pacote);

public:
    Leecher(int tipo_download, int rastreador_porta, int rtt, int falha );
    void configFileDownload(std::string path, std::string hash);
    ~Leecher();
    double velocidade = 100,velocidade_media;
    void run();


};


#endif //UNTITLED_LEECHERS_H
