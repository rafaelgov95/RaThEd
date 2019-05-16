
#include <iostream>
#include "vector"
#include "thread"
#include "Rastreador.h"
#include "Seed.h"


void StartRastreador(int portaRastreador) {
    Rastreador rastreador(portaRastreador);
}

void StartSeed(int tipo_download,int portaBase, int rastreador, int atraso, const char *hash, const char *path){
    Seed s( tipo_download, portaBase,  rastreador,  atraso);
    s.AtualizarRastreador(hash, path);
    s.Run();


}

void StartSeeds(std::thread threads_seeds[],int numThreads,int tipo_download,int portaBase, int rastreador, int atraso, const char *hash, const char *path) {

    for (int i = 0; i < numThreads; ++i) {
        threads_seeds[i]=std::thread(StartSeed,tipo_download,portaBase+(i+1),rastreador,atraso,hash,path);
        std::cout<<"Seeder: "<< i+1 << " Tipo Download: "<< tipo_download <<" Porta: "<< portaBase+(i+1)<<" Hash: "<<hash<<" Path: "<<path << std::endl;
    }
}


int main(int argc, char * argv[])
{
    int numThreads=4;
    std::ifstream i("/home/rafael/Documentos/Projetos/RaThEd/C++/config/config.json");
    json j;
    i >> j;
    std::string hash= j["seeder"]["hash_file"];
    std::string path=j["seeder"]["local_file"];
    std::thread threads_seeds[numThreads];
    std::cout<<"Rastreador Porta: "<< j["rastreador"]["porta"]  << std::endl;
    std::thread thread_rastreador(StartRastreador, j["rastreador"]["porta"]);
    sleep(1);
    StartSeeds(threads_seeds,numThreads,j["tipo_download"],j["seeder"]["inicio_porta"],j["rastreador"]["porta"],j["seeder"]["atraso"],hash.c_str(),path.c_str());
    sleep(1);
    thread_rastreador.join();
}