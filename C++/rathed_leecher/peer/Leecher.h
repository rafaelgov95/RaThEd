//
// Created by rafael on 08/04/19.
//

#ifndef UNTITLED_LEECHERS_H
#define UNTITLED_LEECHERS_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>//use select() for multiplexing
#include <sys/fcntl.h> // for non-blocking
#include "iostream"
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include "vector"
#include "thread"
#include "util.h"
#include "model.pb.h"
#include <pthread.h>
#include <semaphore.h>
#include "PrioritDataGramaFIFO.h"

#include "CamadaDeRede.h"

#define MAX_LENGTH 320
#define MAX_LENGTH_BUFFER ((MAX_LENGTH-10)*4)

namespace io = google::protobuf::io;
struct comp{
    bool operator()(const rathed::Datagrama& a,const rathed::Datagrama& b){
        return a.packnumber()>b.packnumber();
    }
};

class Leecher {

private:
    int socket_fd, buff_int = 0, num_threads,total_bytes_file,rastreadorPorta = 8080;
    std::thread threads[4];
    char buffer[MAX_LENGTH_BUFFER];
    PrioritDataGramaFIFO filaBuffer;

    struct sockaddr_in rastreador_address;
    CamadaDeRede *camadaDeRede;

public:
    sem_t mutex;
    Leecher();
    ~Leecher();

    void run(std::string hash, std::string path);

    void downloandP2P(sockaddr_in seed_address,std::string hash,long buff_int);

    long consultarFileSize(std::string hash, sockaddr_in seed);

    std::vector<std::string> consultarRastreador(std::string hash);
    long MyTempMS();
};


#endif //UNTITLED_LEECHERS_H
