//
// Created by rafael on 03/05/19.
//

#ifndef RATHED_LEECHER_PRIORITCAMADADEREDEFIFO_H
#define RATHED_LEECHER_PRIORITCAMADADEREDEFIFO_H

#include <mutex>
#include <queue>
#include "model.pb.h"

typedef std::pair<long, rathed::Datagrama> pack;

struct compPackPair{
    bool operator()(const pack& a,const pack& b){
        return a.first>b.first;
    }
};

class PrioritCamadaDeRedeFIFO {

private:
    std::priority_queue<pack, std::vector<pack>, compPackPair> fila;
    std::mutex m;
public:
    void push(const pack& elem);
    bool myPack(short type,long bytes,pack &data, short type_down, short round);
    void  clear( );


};

#endif //RATHED_LEECHER_PRIORITCAMADADEREDEFIFO_H
