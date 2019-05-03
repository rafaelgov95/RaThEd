//
// Created by rafael on 03/05/19.
//

#ifndef RATHED_LEECHER_PRIORITFIFO_H
#define RATHED_LEECHER_PRIORITFIFO_H

#include <mutex>
#include <queue>
#include "model.pb.h"

typedef std::pair<long, rathed::Datagrama> pack;

struct compPackPair{
    bool operator()(const pack& a,const pack& b){
        return a.first>b.first;
    }
};

class PrioritFIFO {

private:
    std::priority_queue<pack, std::vector<pack>, compPackPair> fila;
    std::mutex m;
public:
    void push(const pack& elem);
    bool next(pack &elem);
    void  pop ();
    bool myPack(long bytes,pack &data);
    void  clear( );
    bool  empty( );
    pack  top ();

};

#endif //RATHED_LEECHER_PRIORITFIFO_H
