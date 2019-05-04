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

namespace io = google::protobuf::io;

class Leecher {

private:
    int socket_fd,total_bytes_file[4],rastreadorPorta = 8080;
    std::thread threads[4];
    PrioritDataGramaFIFO filaBuffer;
    struct sockaddr_in rastreador_address;
    CamadaDeRede *camadaDeRede;

public:
    Leecher();
    ~Leecher();

    void Run(const std::string& hash, const std::string& path);
    std::vector<std::string> ConsultarRastreador(const std::string& hash);
    long ConsultarFileSize(const std::string& hash, sockaddr_in seed);
    void IniciarDownloadP2P(const std::string& hash, const std::string& path, struct sockaddr_in seed_address[]);
    void DownloandP2P(const std::string& hash, long bytes, sockaddr_in seed_address);
    long MyTempMS();
};


#endif //UNTITLED_LEECHERS_H
