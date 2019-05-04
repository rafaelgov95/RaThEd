//
// Created by rafael on 08/04/19.
//

#ifndef UNTITLED_SEEDS_H
#define UNTITLED_SEEDS_H


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
#include "model.pb.h"
#include "thread"
#include "util.h"
#include <unistd.h>

#define MAX_LENGTH 320


class Seed {

private:
    int R=2,rastreadorPorta = 8080;
    fd_set readfds;
    int numfd = 0;
    int socket_fd, bytes_read, bytes_total;
    unsigned int address_length;
    char recieve_data[MAX_LENGTH], send_data[MAX_LENGTH-20];
    struct sockaddr_in server_address, client_address, rastreador_address;
    std::vector<std::pair<std::string, std::string>> file;

    void Run();

    void AtualizarRastreador(const std::string& hash,const std::string& path);

    void TratarMensagem(rathed::Datagrama& data);

    void EnviarArquivo(rathed::Datagrama& data);

    void AtualizacaoRealizada(rathed::Datagrama& data);

    void ConsultaFileSize(rathed::Datagrama& data);

    void Desconectar();

public:
    Seed(int porta);

    ~Seed();


};


#endif //UNTITLED_SEEDS_H
