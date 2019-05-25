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
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <util/json.hpp>
#define MAX_LENGTH (320)
#define MAX_LENGTH_FILE (320-10)
using json = nlohmann::json;
namespace io = google::protobuf::io;
class Seed {


private:
    fd_set readfds;
    char *hash,*path;
    int fd_arq, opcao, R, my_port, numfd = 0, socket_fd, bytes_read, bytes_total;
    io::ZeroCopyInputStream *raw_input;
    io::CodedInputStream *coded_input;
    unsigned int address_length;
    char recieve_data[MAX_LENGTH];
    struct sockaddr_in server_address, client_address, rastreador_address;
    std::vector<std::pair<std::string, std::string>> file;
    std::vector<rathed::Datagrama>buffer;

    long total_de_pacotes=0;

    rathed::Datagrama SelecionarBloco(rathed::Datagrama &data);
    void TratarMensagem(rathed::Datagrama& data);
    void EnviarAleatorio(rathed::Datagrama& data);
    void EnviarSequencial(rathed::Datagrama& data);
    void AtualizacaoRealizada(rathed::Datagrama& data);
    void ConsultaFileSize(rathed::Datagrama& data);
    void ConfirmarPacote(rathed::Datagrama& data);
    void IsTypeEnviar(rathed::Datagrama& data);

public:

    Seed(int tipo_download, int porta,int rastreadorPorta,int disponibilidade);
    ~Seed();

    void AtualizarRastreador(const char* &hash,const char* &path);
    void Run();

};


#endif //UNTITLED_SEEDS_H
