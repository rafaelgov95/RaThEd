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
#include "vector"
#include "thread"
#include "util.h"
#include "model.pb.h"

#define MAX_LENGTH 320



class Leecher {

private:
    int socket_fd, bytes_read,total_bytes_file,rastreadorPorta = 8080;
    unsigned int address_length;
    char recieve_data[MAX_LENGTH];
    struct sockaddr_in rastreador_address;
    std::vector<std::pair<std::string, std::vector<std::string>>> tableFiles;

public:
    Leecher();

    ~Leecher();

    void run(std::string hash, std::string path);

    void downloandP2P(sockaddr_in seed_address,std::string path,std::string hash);

    bool consultarFileSize(std::string hash, sockaddr_in seed);

    std::vector<std::string> consultarRastreador(std::string hash);

};


#endif //UNTITLED_LEECHERS_H
