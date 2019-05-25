//
// Created by rafael on 17/05/19.
//

#ifndef RATHED_LEECHER_PLAYER_H
#define RATHED_LEECHER_PLAYER_H

#include <fstream>
#include "iostream"
#include "util.h"
class Player {

private:
    const char *path;
    const char *log;
    int total_bytes_file;
    std::ofstream *ofs;

public:

    Player(const char *path,const char *log, int total_bytes_file);
    void run();

    ~Player();


};


#endif //RATHED_LEECHER_PLAYER_H
