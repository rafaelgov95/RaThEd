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

bool PrioritFIFO::myPack(short type, long packnumber, pack &data, short type_dow,short round) {
    std::lock_guard<std::mutex> lock(m);
    if (!fila.empty()) {
        if (type == 2 && type_dow == 2) {
            data = fila.top();
            fila.pop();
            return true;
        } else if (fila.top().second.packnumber() == packnumber && type == 2 && type_dow == 1) {
            data = fila.top();
            fila.pop();
            return true;
        }else if (type == 2 && type_dow == 1 && round==1) {
            fila.pop();
        } else if (type == 1 ) {
            data = fila.top();
            fila.pop();
            return true;
        }else if(type==3)  {
            data = fila.top();
            fila.pop();
            return true;
        }else{
            fila.pop();
        }
    }
    return false;
}