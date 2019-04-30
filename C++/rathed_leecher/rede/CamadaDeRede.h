//
// Created by rafael on 08/04/19.
//

#ifndef UNTITLED_CAMADADEREDE_H
#define UNTITLED_CAMADADEREDE_H

#include "iostream"
#include <queue>
#include "thread"
#include "util.h"
#include "model.pb.h"

class CamadaDeRede {

private:
    static int rtt, E,F;
    std::thread temporizador;
    std::queue<std::vector<int, rathed::Datagrama>>  filaDataGramas;

  static void AdicionarAFila();

public:
    static void StartTemporizacao();

    static void SimularRede(rathed::Datagrama data);

};


#endif //UNTITLED_CAMADADEREDE_H
