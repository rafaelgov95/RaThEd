
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

void StartSeeds(std::thread threads_seeds[],int numThreads,int portaBase) {

    for (int i = 0; i < numThreads; ++i) {
        threads_seeds[i]=std::thread(StartSeed,portaBase+(i+1));
    }
}


int main(int argc, char * argv[])
{
    int numThreads=4;
    std::thread threads_seeds[numThreads];
    std::thread thread_rastreador(StartRastreador, 8080);
    sleep(1);
    StartSeeds(threads_seeds,numThreads,8080);
    sleep(1);
    thread_rastreador.join();
    for (auto & threads_seed : threads_seeds) {
        threads_seed.join();
    }

}