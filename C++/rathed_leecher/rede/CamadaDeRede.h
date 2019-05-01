//
// Created by rafael on 08/04/19.
//

#ifndef UNTITLED_CAMADADEREDE_H
#define UNTITLED_CAMADADEREDE_H

#include "iostream"
#include <queue>
#include <netinet/in.h>
#include <semaphore.h>
#include "util.h"
#include "model.pb.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#define MAX_LENGTH 320


typedef std::pair<long, rathed::Datagrama> pack;

class CompPack
{
public:
    bool operator () (pack lhs, pack rhs) {
        return lhs.first > rhs.first;
    }
};


class CamadaDeRede {

private:

    int socket_fd, bytes_read;
    unsigned int address_length;
    char recieve_data[MAX_LENGTH];
    struct sockaddr_in rastreador_address;
    long rtt=20,F=35;


    rathed::Datagrama ConsultarRastreador(std::string hash);
    void StartTemporizacao(rathed::Datagrama data);
public:
    sem_t mutex;


    CamadaDeRede(int socket,struct sockaddr_in &rastreador);
    std::priority_queue<pack, std::vector<pack>, CompPack> filaDataGramas;


    void InterfaceConsultarRastreador(std::string hash);
    void InterfaceDownloandP2P(std::string hash, long bytes,struct sockaddr_in seed_address) ;


};


#endif //UNTITLED_CAMADADEREDE_H
