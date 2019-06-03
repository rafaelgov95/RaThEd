//
// Created by rafael on 03/05/19.
//
//    QApplication a(argc, argv);
//    Widget w;
//    w.show();
//
//    return a.exec();
#include "widget.h"
#include <QApplication>
#include "thread"

void StartLeecher(int peers,int tipo_download,int portaRastreador,int rtt, int e,int falha,const char *path, const char *hash, const char *log_leecher, const char *log_player){
    Leecher leecher( peers,tipo_download,portaRastreador,rtt,e,falha);
    leecher.ConfigFileDownload(hash,path,log_leecher,log_player);
    leecher.Run();
}


int main(int argc, char *argv[])
{
////
//    QApplication a(argc, argv);
//    Widget w;
//    w.show();
//
//    return a.exec();


    std::ifstream i("/home/rafael/Documentos/Projetos/RaThEd/C++/config/config.json");
    json j;
    i >> j;
    std::string hash = j["leecher"]["hash_file"];
    std::string path = j["leecher"]["local_download"];
    std::string logBase = j["leecher"]["log"];
    std::string log;
    std::string logPlayer;
    std::string logLeecher;
    int peers=j["seeder"]["peers"];
    int rtt=j["camada_de_rede"]["rtt"];
    int e=j["camada_de_rede"]["E[X]"];
    int falha=j["camada_de_rede"]["falha"];
    int atraso= j["seeder"]["disponibilidade"];
    int tipo_download=j["tipo_download"];
    int porta_rastreador=j["rastreador"]["porta"];

    log= "PEERS:_"+std::to_string(peers)+"_TIPO_"+std::to_string(tipo_download)+"_-_RTT_"+ std::to_string(rtt)+"_-_FALHA_"+ std::to_string(falha)+"_-DISPO"+std::to_string(atraso)+".txt";
    logLeecher=logBase+"Leecher__"+log;
    logPlayer=logBase+"Play__"+log;
    std::thread Tleecher( StartLeecher,peers,tipo_download,porta_rastreador,rtt,e,falha,path.c_str(),hash.c_str(),logLeecher.c_str(),logPlayer.c_str());
    Tleecher.join();

}
