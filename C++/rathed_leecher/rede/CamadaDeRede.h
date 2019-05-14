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
#include <util/PrioritFIFO.h>

#define MAX_LENGTH (320*8)
#define MAX_LENGTH_FILE ((320*8)-48)

class CamadaDeRede {

private:
    unsigned int socket_fd,bytes_read,address_length;
    char recieve_data[MAX_LENGTH];
    struct sockaddr_in rastreador_address;
    PrioritFIFO filaDataGramas;
    long rtt=20,F=50;
    std::mutex m;
    void StartTemporizacao(const rathed::Datagrama& data);

public:
    CamadaDeRede(unsigned int socket, struct sockaddr_in &rastreador);
    void InterfaceRede(rathed::Datagrama data, struct sockaddr_in seed_address) ;
    PrioritFIFO& InterfaceGetFilaBuffer();
};


#endif //UNTITLED_CAMADADEREDE_H
