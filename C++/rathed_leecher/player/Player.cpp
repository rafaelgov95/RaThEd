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
    int total_bytes_atual, loading = 0, bytes = 320, cont_bytes = 0, total_blocos = 0;
    long tempInicio, tempFim, tempLocal;
    bool flag = true;
    double pausaMedia = 0, tempCount = 0, tempMaior = 0;
    tempInicio = MyTempMiS_();

    std::cout << "Path: " << path << " Log: " << log << std::endl;
    std::cout << "Player Vai Começar" << std::endl;
    while (flag) {
        tempLocal = MyTempMiS_();
        auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        total_bytes_atual = fileSize(path);
        usleep(20000);
        tempFim = MyTempMiS_();
        if ((cont_bytes ) >= total_bytes_file) {
            flag = false;
            cont_bytes += (total_bytes_file - (cont_bytes));
            *ofs << "Time: " << ctime(&timenow) << " Acabou Reprodução" << std::endl;
            *ofs << "Time: " << ctime(&timenow) << " Reproduzindo Bytes: " << cont_bytes
                 << " Total de Bytes Atual: " << total_bytes_atual << std::endl;

        } else {

            if (total_bytes_atual >= (cont_bytes)) {
                total_blocos++;
                *ofs << (double) (tempFim - tempInicio) * pow(10, -6) << ";"
                     << (((bytes * 8) / ((double) ((double) 20 / 1000))) / 1000) << " ; " << (cont_bytes + bytes) << ";"
                     << total_bytes_atual << std::endl;
                cont_bytes += bytes;
                tempCount = 0;
            } else {
                loading++;
                tempCount += (double) (tempFim - tempLocal) * pow(10, -6);
                pausaMedia += (double) (tempFim - tempLocal) * pow(10, -6);
                if (tempCount > tempMaior) {
                    tempMaior = tempCount;
                }
                *ofs << (double) (tempFim - tempInicio) * pow(10, -6) << ";" << 0 << ";" << 0 << ";" << 0 << std::endl;


            }

        }
    }
    *ofs << "Tempo Fim: " <<(long) MyTempMiS_()  <<" TimeStamp Milessegundos" <<std::endl;

    *ofs << "Tempo Inicio: " << (long) tempInicio <<" TimeStamp Milessegundos" <<std::endl;

    *ofs << "Maior tempo em espera: " << tempMaior << std::endl;
    *ofs << "Tempo de pausa Total :  " << pausaMedia << std::endl;
    *ofs << "Media de pausa:  " << pausaMedia / loading << std::endl;
    *ofs << "Total blocos atrasados: " << loading << std::endl;
    *ofs << "Total blocos: " << total_blocos << std::endl;


}