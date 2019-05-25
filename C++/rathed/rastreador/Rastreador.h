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
#define MAX_LENGTH (320)
#define MAX_LENGTH_FILE (320-10)
class Rastreador {

private:
    fd_set readfds;
    int numfd=0;
    int socket_fd, bytes_read;
    unsigned int address_length;
    char recieve_data[MAX_LENGTH];
    struct sockaddr_in server_address, client_address;
    std::vector<std::pair<std::string,std::vector<std::string>>> filesPeers;


    void Run();
    void SelectOpcao(rathed::Datagrama &data);
    void EnviarPeers(const char* peers);

public:
    Rastreador(unsigned int porta);
    ~Rastreador();

    void ConsultaFiles(rathed::Datagrama &data);
    void AtualizarPeer(rathed::Datagrama &data);
    void ListarFiles(rathed::Datagrama &data);

};


#endif //UNTITLED_Rastreador_H
