//
// Created by rafael on 03/05/19.
//

#include "PrioritFIFO.h"

void PrioritFIFO::push(const pack &elem) {
    std::lock_guard<std::mutex> lock(m);
    fila.push(elem);
}

bool PrioritFIFO::next(pack &elem) {
    std::lock_guard<std::mutex> lock(m);
    if (fila.empty()) {
        return false;
    }
    elem = fila.top();
    fila.pop();
    return true;
}

void PrioritFIFO::pop() {
    std::lock_guard<std::mutex> lock(m);
    fila.pop();
}

void PrioritFIFO::clear() {
    std::priority_queue<pack, std::vector<pack>, compPackPair> empty;
    std::swap(fila, empty);
}

bool PrioritFIFO::empty() {
    std::lock_guard<std::mutex> lock(m);
    return fila.empty();
}

pack PrioritFIFO::top() {
    std::lock_guard<std::mutex> lock(m);
    return fila.top();
}

bool PrioritFIFO::myPack(short type,long packnumber, pack &data) {
    std::lock_guard<std::mutex> lock(m);
    if (!fila.empty()) {
        if (fila.top().second.packnumber() == packnumber && type==2 ) {
            data = fila.top();
            fila.pop();
            return true;
        }else{
            data = fila.top();
            fila.pop();
            return true;
        }
    }
    return false;
}