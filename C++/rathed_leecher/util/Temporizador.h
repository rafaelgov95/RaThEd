//
// Created by rafael on 05/05/19.
//

#ifndef RATHED_LEECHER_TEMPORIZADOR_H
#define RATHED_LEECHER_TEMPORIZADOR_H


#include <iostream>
#include <future>
#include <chrono>
#include <util/util.h>
#include "CamadaDeRede.h"

class Temporizador {
public:
    Temporizador(std::shared_future<void> f, std::chrono::milliseconds interval, CamadaDeRede *camada,short type, const char *hash, long bytes, struct sockaddr_in *pointer_address);
    std::future<void> run() ;
private:
    std::mutex cout_mutex;
    short type;
    const char *hash;
    long bytes;
    struct sockaddr_in *pointer_address;
    CamadaDeRede *camada;
    const std::chrono::milliseconds interval;
    std::shared_future<void> done;
    void tickWrapper() ;
    void tickfunction() ;
};


#endif //RATHED_LEECHER_TEMPORIZADOR_H




static std::mutex cout_mutex;

class Ticker
{
};