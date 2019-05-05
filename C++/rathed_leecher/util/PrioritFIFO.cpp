//
// Created by rafael on 03/05/19.
//

#include "PrioritFIFO.h"

void PrioritFIFO::push(const pack &elem) {
    std::lock_guard<std::mutex> lock(m);
    fila.push(elem);
}

void PrioritFIFO::clear() {
    std::priority_queue<pack, std::vector<pack>, compPackPair> empty;
    std::swap(fila, empty);
}


bool PrioritFIFO::myPack(short type,long packnumber, pack &data, short round) {
    std::lock_guard<std::mutex> lock(m);
    if (!fila.empty()) {
        if (fila.top().second.packnumber() == packnumber && type==2 ) {
            data = fila.top();
            fila.pop();
            return true;
        }else if(type==3){
            data = fila.top();
            fila.pop();
            return true;
        }
        fila.pop();
    }
    return false;
}