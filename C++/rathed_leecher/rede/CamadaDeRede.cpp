//
// Created by rafael on 08/04/19.
//

#include "CamadaDeRede.h"

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <libnet.h>
#include <chrono>
CamadaDeRede::~CamadaDeRede(){

}


CamadaDeRede::CamadaDeRede(unsigned int socket, struct sockaddr_in &rastreador, int rtt, int e, int falha) : socket_fd(socket),
                                                                                  rastreador_address(rastreador),rtt(rtt),e(e),F(falha) {
    srand((unsigned int) time(NULL));
    address_length = sizeof(struct sockaddr);
}


void CamadaDeRede::StartTemporizacao(const rathed::Datagrama &data, double temp1) {
    int x = rand() % 100 + 1;
    if((100-F) >= x) {
        double wx = generadorDistribucionExponencial(e);
        int timeEnvio = ((rtt/2) + (int)wx)+temp1;
        int newtime=  MyTempMS()+timeEnvio;
       filaDataGramas.push(std::make_pair(newtime, data));
    }
}


void CamadaDeRede::InterfaceRede( const rathed::Datagrama &data,struct sockaddr_in seed_address) {
    std::lock_guard<std::mutex> lock(m);
    rathed::Datagrama data_; //X = 80
    int x = rand() % 100 + 1;
    if((100-F) >= x) { //Falha 20
        double wx = generadorDistribucionExponencial(e);
        int timeEnvio = ((rtt/2) + (int)wx);
        if (sendto(socket_fd, DataGramaSerial(data), data.ByteSize(), 0,
                   (struct sockaddr *) &seed_address, sizeof(struct sockaddr)) <= 0)
            error("Erro ao enviar");

        bytes_read = recvfrom(socket_fd, recieve_data, MAX_LENGTH, 0, (struct sockaddr *) &seed_address,
                              &address_length);

        data_.ParseFromArray(recieve_data, bytes_read);
        StartTemporizacao(data_,timeEnvio);
    }
}


PrioritCamadaDeRedeFIFO &CamadaDeRede::InterfaceGetFilaBuffer() {
    return filaDataGramas;
}