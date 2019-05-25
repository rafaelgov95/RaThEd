//
// Created by rafael on 17/05/19.
//

#include "Player.h"

Player::~Player() {
    ofs->close();
}

Player::Player(const char *path, const char *log, int total_bytes_file) : path(path), log(log),
                                                                          total_bytes_file(total_bytes_file) {
    ofs = new std::ofstream(log, std::ofstream::out);
}

void Player::run() {
    int total_bytes_atual, loading = 0,bytes=320,cont_bytes=0;
    double tempInicio,tempFim;
    bool flag = true;
    std::cout << "Path: " << path << " Log: " << log << std::endl;
        std::cout << "Player Vai Começar" << std::endl;
        while (flag) {
            tempInicio = MyTempMiS_();
            auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            total_bytes_atual = fileSize(path);
            if ((cont_bytes + bytes) >= total_bytes_file)  {
                flag = false;
                cont_bytes += (total_bytes_file-(cont_bytes + bytes));
                *ofs << "Time: " << ctime(&timenow) << " Acabou Reprodução" <<std::endl;
                *ofs << "Time: " << ctime(&timenow) << " Reproduzindo Bytes: " << cont_bytes
                     << " Total de Bytes Atual: " << total_bytes_atual << std::endl;
            } else {
                if (total_bytes_atual >= (cont_bytes + bytes)) {
                    *ofs << MyTempMS() << ","<<(((bytes*8)/((double)((double)20/1000)))/1000) << " , " << (cont_bytes + bytes)<<","<< total_bytes_atual << std::endl;

//                *ofs <<<<"Velocidade: "<<(((bytes*8)/((double)((double)20/1000)))/1000) << " Kbps Reproduzindo Bytes: " << (cont_bytes + bytes)
//                     << " Total de Bytes Atual: " << total_bytes_atual << " Time: " << ctime(&timenow) ;
                cont_bytes += bytes;
            } else {
                loading++;
//                *ofs << "Time: " << ctime(&timenow) << " Aguardando Looding :" << loading<<" Bytes Atual: " << (cont_bytes)
//                     << " Total de Bytes Atual: " << total_bytes_atual << std::endl;
                    *ofs << MyTempMS() << ","<< 0<< ","<< 0<< ","<< 0  << std::endl ;

            }
            usleep(20000);
        }
    }
}