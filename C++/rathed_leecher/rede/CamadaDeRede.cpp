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
}


void CamadaDeRede::StartTemporizacao(const rathed::Datagrama &data) {
    int x = rand() % 100 + 1; //distribuicao não sei fazer
    if (F > x) {
//        std::cout<<"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"<<std::endl;
    } else {
        int wx = 0;
        int timeEnvio = rtt + wx;// tempodoTime
       filaDataGramas.push(std::make_pair(MyTempMS()+timeEnvio, data));
    }
}


void CamadaDeRede::InterfaceRede(rathed::Datagrama data,struct sockaddr_in seed_address) {
    std::lock_guard<std::mutex> lock(m);
    rathed::Datagrama data__;


    if (sendto(socket_fd, DataGramaSerial(data), data.ByteSizeLong(), 0,
               (struct sockaddr *) &seed_address, sizeof(struct sockaddr)) <= 0)
        error("Erro ao enviar");
    bytes_read = recvfrom(socket_fd, recieve_data, MAX_LENGTH, 0, (struct sockaddr *) &seed_address,
                          &address_length);
    data.clear_data();
//    std::cout << "Bytes Datagrama Antes: " << data__.ByteSize() << std::endl;
    data.ParseFromArray(recieve_data, bytes_read);
//    data.set_seqnumber(11111111111111111111);
    std::cout << " Bytes Datagrama: " << data.data().size() << std::endl;
    std::cout << " Bytes Datagrama ByteSize: " << data.ByteSize()<< std::endl;

    StartTemporizacao(data);
}


PrioritFIFO &CamadaDeRede::InterfaceGetFilaBuffer() {
    return filaDataGramas;
}