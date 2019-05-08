//
// Created by rafael on 05/05/19.
//

#include "Temporizador.h"

//Temporizador::Temporizador(std::shared_future<void>f,std::chrono::milliseconds interval, CamadaDeRede *camada,short type, const char *hash, long bytes, struct sockaddr_in *pointer_address): interval{interval}, done{f},camada{camada},type{type},hash{hash},pointer_address{pointer_address}
//{ }

Temporizador::Temporizador(std::shared_future<void> &f,std::chrono::milliseconds interval,PrioritDataGramaFIFO &fila, rathed::Datagrama &data):interval{interval}, done{f}, fila(fila), data(data)
{ }

std::future<void> Temporizador::run() {
    return std::async(std::launch::async, &Temporizador::tickWrapper, this);
}
constexpr std::chrono::milliseconds operator ""ms(unsigned long long ms)
{
    return std::chrono::milliseconds(ms);
}
void Temporizador::tickWrapper() {
    std::future_status status;
    do {
        status = done.wait_for(interval);
        if (status == std::future_status::timeout) {
            tickfunction();
        }
    } while (status != std::future_status::ready);
}
void Temporizador::tickfunction() {
    std::lock_guard<std::mutex> lock(cout_mutex);
//    camada->InterfaceRede(type, hash, bytes, pointer_address);
    fila.push(data);
    std::cout << "tick (" << std::this_thread::get_id() << ")" << "TEMP: "<<MyTempMS()<<std::endl;
}

