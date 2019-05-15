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

CamadaDeRede::CamadaDeRede(unsigned int socket, struct sockaddr_in &rastreador) : socket_fd(socket),
                                                                                  rastreador_address(rastreador) {
    srand((unsigned int) time(NULL));
    address_length = sizeof(struct sockaddr);
}


void CamadaDeRede::StartTemporizacao(const rathed::Datagrama &data) {
    int x = rand() % 100 + 1; //distribuicao não sei fazer
    if (F > x) {
    } else {
        int wx = 0;
        int timeEnvio = rtt + wx;// tempodoTime
       filaDataGramas.push(std::make_pair(MyTempMS()+timeEnvio, data));
    }
}


void CamadaDeRede::InterfaceRede( const rathed::Datagrama &data,struct sockaddr_in seed_address) {
    std::lock_guard<std::mutex> lock(m);
    rathed::Datagrama data_;
    if (sendto(socket_fd, DataGramaSerial(data), data.ByteSize(), 0,
               (struct sockaddr *) &seed_address, sizeof(struct sockaddr)) <= 0)
        error("Erro ao enviar");

    bytes_read = recvfrom(socket_fd, recieve_data, MAX_LENGTH, 0, (struct sockaddr *) &seed_address,
                          &address_length);

    data_.ParseFromArray(recieve_data, bytes_read);
//    std::cout << " Bytes Datagrama: " << data_.data().size() << std::endl;
//    std::cout << " Bytes Datagrama ByteSize: " << data_.ByteSize()<< std::endl;

    StartTemporizacao(data_);
}


PrioritFIFO &CamadaDeRede::InterfaceGetFilaBuffer() {
    return filaDataGramas;
}