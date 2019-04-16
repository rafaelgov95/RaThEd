//
// Created by rafael on 08/04/19.
//

#ifndef UNTITLED_Rastreador_H
#define UNTITLED_Rastreador_H

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
#include <algorithm>    // std::find_if
#include <numeric>

#include "Seed.h"
#include "util.h"
#include "model.pb.h"

#define MAX_LENGTH 360
//char *END_FLAG = "================END";

class Rastreador {

private:
    fd_set original_socket;
    fd_set readfds;
    struct timeval tv;
    int numfd=1;
    int socket_fd, bytes_read;
    unsigned int address_length;
    char recieve_data[MAX_LENGTH - 20],send_data[MAX_LENGTH - 20];
    struct sockaddr_in server_address, client_address;
    std::vector<std::pair<std::string,std::vector<std::string>>> filesPeers;


    void run();
    void selectOpcao(rathed::Datagrama);
    void enviarPeers(std::string hash);

public:
    Rastreador(int porta);
    ~Rastreador();

    void consultaFiles(rathed::Datagrama &data);
    void atualizarPeer(rathed::Datagrama data);

    void listarFiles(rathed::Datagrama data);

};


#endif //UNTITLED_Rastreador_H
