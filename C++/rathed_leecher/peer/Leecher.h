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
#include <google/protobuf/io/coded_stream.h>
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
#define MAX_LENGTH_FILE (320-10)


#include <stack>
#include <QtCore>
#include <player/Player.h>


namespace io = google::protobuf::io;


//class Leecher :public QThread{

class Leecher {

private:
    const char *hash, *path,*log_player;
    int tipo_download,socket_fd,rtt, *total_bytes_file, total_de_pacotes=0, rastreador_porta=0, numthreads=0 ,total_bytes_baixados=0;
    std::thread *threads;
    PrioritDataGramaFIFO filaBuffer;
    std::set<int>  filaConfirma;
    std::set<Buffer> setBuffer;
    struct sockaddr_in rastreador_address, *seed_address;
    CamadaDeRede *camadaDeRede;
    std::ofstream *ofs;

    rathed::Datagrama
    EnviarDataGramaParaRede(int type_down, const rathed::Datagrama &data_, struct sockaddr_in &memory_seed_address);

    std::vector<std::string> ConsultarRastreador(const char* hash);

    long ConsultarFileSize(const char *hash, struct sockaddr_in &pointer_address);

    void IniciarDownloadP2PSequencial();

    void IniciarDownloadP2PAleatorio();
    void IniciarDownloadP2PAleatorioComRange();

    void RequisicaoP2P(int type_down, const char* hash, int pack_number, struct sockaddr_in seed_address);


public:

    double velocidade = 100,velocidade_media{};
    ~Leecher();
    Leecher(int peers,int tipo_download, int rastreador_porta, int rtt, int e,int falha );
    void ConfigFileDownload(const char *path, const char *hash,const char *log,const char *log_player);
    void Run();


};


#endif //UNTITLED_LEECHERS_H
