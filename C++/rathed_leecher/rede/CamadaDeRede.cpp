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

CamadaDeRede::CamadaDeRede(int socket, struct sockaddr_in &rastreador) : socket_fd(socket),
                                                                         rastreador_address(rastreador) {
    srand((unsigned int) time(NULL));
}


void CamadaDeRede::StartTemporizacao(rathed::Datagrama data) {
    std::lock_guard<std::mutex> lock(mm);

    int x = rand() % 100 + 1; //distribuicao não sei fazer
    if (F >= x) {
        std::cout << "Pacote Perdido: " << x << std::endl;
    } else {
        int wx = rand() % (rtt + 1); //distribuicao não sei fazer
        int timeEnvio = rtt + wx;// tempodoTime
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()
        );
        long tempofinal = ms.count();
        tempofinal += timeEnvio;
        std::cout << "Pacote Recebido Fila: " << ms.count() << " Temporizador: " << tempofinal << " Tempo Envio:  "
                  << timeEnvio << " | " << data.packnumber() << std::endl;
        filaDataGramas.push(std::make_pair(tempofinal, data));
    }
}


void CamadaDeRede::InterfaceConsultarRastreador(const std::string &hash) {

    rathed::Datagrama data = DataGrama(2, 0, hash.c_str());
    if (sendto(socket_fd, DataGramaSerial(data), data.ByteSizeLong(), 0, (struct sockaddr *) &rastreador_address,
               sizeof(struct sockaddr)) <= 0)
        error("Erro ao enviar");
    bytes_read = 0;

    bytes_read = recvfrom(socket_fd, recieve_data, MAX_LENGTH, 0, (struct sockaddr *) &rastreador_address,
                          &address_length);
    data.clear_data();
    data.ParseFromArray(recieve_data, bytes_read);
    std::cout << "CAMADA DE REDE - datagrama consultar Rastreador: " << data.data() << std::endl;
    StartTemporizacao(data);
}


void CamadaDeRede::InterfaceDownloandP2P(const std::string &hash, long bytes, struct sockaddr_in seed_address) {
    std::lock_guard<std::mutex> lock(m);
    rathed::Datagrama data = DataGrama(2, bytes, hash);
    if (sendto(socket_fd, DataGramaSerial(data), data.ByteSizeLong(), 0,
               (struct sockaddr *) &seed_address, sizeof(struct sockaddr)) <= 0)
        error("Erro ao enviar");
    bytes_read = recvfrom(socket_fd, recieve_data, MAX_LENGTH, 0, (struct sockaddr *) &seed_address,
                          &address_length);
    data.clear_data();
    data.ParseFromArray(recieve_data, bytes_read);
    StartTemporizacao(data);
}


void CamadaDeRede::InterfaceConsultarFileSize(const std::string &hash, long bytes, struct sockaddr_in seed_address) {
    rathed::Datagrama data = DataGrama(3, 0, hash);

    if (sendto(socket_fd, DataGramaSerial(data), data.ByteSizeLong(), 0,
               (struct sockaddr *) &seed_address, sizeof(struct sockaddr)) <= 0)
        error("Erro ao enviar");

    bytes_read = recvfrom(socket_fd, recieve_data, MAX_LENGTH, 0, (struct sockaddr *) &seed_address,
                          &address_length);
    data.clear_data();
    data.ParseFromArray(recieve_data, bytes_read);
    StartTemporizacao(data);
}

PrioritFIFO &CamadaDeRede::get_FilaBuffer() {
    return filaDataGramas;
}