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

#define MAX_LENGTH 320




class CamadaDeRede {

private:

    int socket_fd, bytes_read;
    unsigned int address_length;
    char recieve_data[MAX_LENGTH];
    struct sockaddr_in rastreador_address;
    long rtt=20,F=5;
    std::mutex m,mm;
    rathed::Datagrama ConsultarRastreador(std::string hash);
    void StartTemporizacao(rathed::Datagrama data);
public:
    CamadaDeRede(int socket,struct sockaddr_in &rastreador);
    PrioritFIFO filaDataGramas;
    void InterfaceConsultarRastreador(const std::string& hash);
    void InterfaceDownloandP2P(const std::string& hash, long bytes, struct sockaddr_in seed_address) ;
    void InterfaceConsultarFileSize(const std::string& hash, long bytes, struct sockaddr_in seed_address);


};


#endif //UNTITLED_CAMADADEREDE_H
