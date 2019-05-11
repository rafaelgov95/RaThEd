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
#include <queue>
#define MAX_LENGTH 320
#define MAX_LENGTH_FILE 305

class Seed {

private:
    int opcao=2, R=2 ,rastreadorPorta = 8080;
    int my_port, numfd = 0, socket_fd, bytes_read, bytes_total;
    unsigned int address_length;
    long total_de_pacotes=0;
    char recieve_data[MAX_LENGTH_FILE];
    struct sockaddr_in server_address, client_address, rastreador_address;
    fd_set readfds;
    std::vector<std::pair<std::string, std::string>> file;
    std::vector<rathed::Datagrama>buffer;


    void Run();
    rathed::Datagrama check_list_enviados(int x );
    void AtualizarRastreador(const std::string& hash,const std::string& path);

    void TratarMensagem(rathed::Datagrama& data);
    void EnviarAleatorio(rathed::Datagrama& data);
    void EnviarSequencial(rathed::Datagrama& data);
    void AtualizacaoRealizada(rathed::Datagrama& data);
    void ConsultaFileSize(rathed::Datagrama& data);
    void ConfirmarPacote(rathed::Datagrama& data);
    void IsTypeEnviar(rathed::Datagrama& data);

public:
    Seed(int porta);
    ~Seed();


};


#endif //UNTITLED_SEEDS_H
