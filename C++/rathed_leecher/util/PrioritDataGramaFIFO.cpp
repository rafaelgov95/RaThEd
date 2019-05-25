//
// Created by rafael on 03/05/19.
//

#include "PrioritDataGramaFIFO.h"

void PrioritDataGramaFIFO::push(const rathed::Datagrama& elem) {
    std::lock_guard<std::mutex> lock(m);
    fila.push(elem);
}

bool PrioritDataGramaFIFO::next(rathed::Datagrama& elem) {
    std::lock_guard<std::mutex> lock(m);
    if (fila.empty()) {
        return false;
    }
    elem = fila.top();

    fila.pop();
    return true;
}
void PrioritDataGramaFIFO::pop() {
    std::lock_guard<std::mutex> lock(m);
     fila.pop();
}
rathed::Datagrama PrioritDataGramaFIFO::top() {
    std::lock_guard<std::mutex> lock(m);
    return fila.top();
}

void  PrioritDataGramaFIFO::clear( )
{
    std::priority_queue<rathed::Datagrama, std::vector<rathed::Datagrama>, compPack> empty;
    std::swap( fila, empty );
}
bool PrioritDataGramaFIFO::empty(){
    std::lock_guard<std::mutex> lock(m);
    return fila.empty();
}

