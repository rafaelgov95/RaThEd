
#include <iostream>
#include "vector"
#include "thread"
#include "Rastreador.h"
#include "Seed.h"


void StartRastreador(int portaRastreador) {
    Rastreador rastreador(portaRastreador);
}

void StartSeed(int porta){

    Seed s(porta);
}

void StartSeeds(std::thread threads_seeds[],int portaBase) {

    for (int i = 0; i < 4; ++i) {
        threads_seeds[i]=std::thread(StartSeed,portaBase+(i+1));
    }
}


int main(int argc, char * argv[])
{

    std::thread threads_seeds[4];
    std::thread thread_rastreador(StartRastreador, 8080);
    sleep(2);
    StartSeeds(threads_seeds,8080);
    thread_rastreador.join();
    for (int i = 0; i <4; ++i) {
        threads_seeds[i].join();
    }

}