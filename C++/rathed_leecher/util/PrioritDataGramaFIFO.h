//
// Created by rafael on 03/05/19.
//

#ifndef RATHED_LEECHER_PRIORITDATAGRAMAFIFO_H
#define RATHED_LEECHER_PRIORITDATAGRAMAFIFO_H

#include <mutex>
#include <queue>
#include "model.pb.h"


struct compPack{
    bool operator()(const rathed::Datagrama& a,const rathed::Datagrama& b){
        return a.packnumber()>b.packnumber();
    }
};

class PrioritDataGramaFIFO {

private:
    std::priority_queue<rathed::Datagrama, std::vector<rathed::Datagrama>, compPack> fila;
    std::mutex m;
public:
    void push(const rathed::Datagrama& elem);
    bool next(rathed::Datagrama &elem);
    void  pop ();
    void  clear( );
    bool  empty( );
    rathed::Datagrama  top ();

};

#endif //RATHED_LEECHER_PRIORITDATAGRAMAFIFO_H
