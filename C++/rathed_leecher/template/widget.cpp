//
// Created by rafael on 16/04/19.
//

#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDir>
#include <Leecher.h>
#include <player/Player.h>


Widget::Widget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Widget) {
    ui->setupUi(this);

    m_playListModel = new QStandardItemModel(this);
    ui->playlistView->setModel(m_playListModel);    // defini modelo de dados
    ui->lcdNumber->display(QString::number(leecher->velocidade, 'f', 0));
    // Definir cabecalhos da tabela
    m_playListModel->setHorizontalHeaderLabels(QStringList() << tr("Audio Stream")
                                                             << tr("Audio Path"));
    ui->playlistView->hideColumn(1);    // Oculta caminho do arquivo
    ui->playlistView->verticalHeader()->setVisible(false);                  // Oculta numeracao de linhas
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);  // Ativa Selecao de linhas
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection); // Somente uma linha seja selecionada
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);   // Destivar Edicao
    ui->progressBar->setValue(20);

    // Habilida o ajuste do tamanho da ultima coluna visivel
    ui->playlistView->horizontalHeader()->setStretchLastSection(true);
    m_player = new QMediaPlayer(this);          // Inicializar Play
    m_playlist = new QMediaPlaylist(m_player);  // Iniciliar lista de repoducao
    m_player->setPlaylist(m_playlist);          // Instale a lista de reprodução no player
    m_player->setVolume(70);                    // Definir o volume de reprodução das faixas
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);  // Definir o modo cíclico da lista de reprodução
    ui->volume->setValue(m_player->volume());  // vinculando volume
    // conecta botões de controle para controlar os slots
    // Observe aqui que a playlist é navegada pela playlist
    // iniciar / pausar / parar no próprio player
    connect(ui->btn_previous, &QToolButton::clicked, m_playlist, &QMediaPlaylist::previous);
    connect(ui->btn_next, &QToolButton::clicked, m_playlist, &QMediaPlaylist::next);
    connect(ui->btn_play, &QToolButton::clicked, m_player, &QMediaPlayer::play);
    connect(ui->btn_pause, &QToolButton::clicked, m_player, &QMediaPlayer::pause);
    connect(ui->btn_stop, &QToolButton::clicked, m_player, &QMediaPlayer::stop);
    connect(ui->volume, &QSlider::valueChanged, m_player, &QMediaPlayer::setVolume); // conectando volume

//    connect(leecher.total_bytes_baixados,ui->lcdNumber,&QLCDNumber::value);
    // Quando um clique duplo na faixa da tabela, defina a faixa na lista de reprodução
    connect(ui->playlistView, &QTableView::doubleClicked, [this](const QModelIndex &index) {
        m_playlist->setCurrentIndex(index.row());
    });

    // ao alterar o índice da faixa atual na lista de reprodução, defina o nome do arquivo em uma etiqueta especia
    connect(m_playlist, &QMediaPlaylist::currentIndexChanged, [this](int index) {
        ui->currentTrack->setText(m_playListModel->data(m_playListModel->index(index, 0)).toString());
    });
//
//    connect(m_player,&QMediaPlayer::durationChanged,ui->progressBar,&QProgressBar::maximum);
//    connect(m_player,&QMediaPlayer::positionChanged,ui->progressBar,&QProgressBar::value);

//    connect( ui->lcdNumber,SIGNAL(), [this](int index) {
//        ui->lcdNumber->display(QString::number(leecher.velocidade,'f',0));
//    });

}

Widget::~Widget() {
    delete ui;
    delete m_playListModel;
    delete m_playlist;
    delete m_player;
}
//void StartLeecher(int peers,int tipo_download,int portaRastreador,int rtt, int e,int falha,const char *path, const char *hash, const char *log_leecher, const char *log_player){
//    Leecher leecher( peers,tipo_download,portaRastreador,rtt,e,falha);
//    leecher.ConfigFileDownload(hash,path,log_leecher,log_player);
//    leecher.Run();
//    leecher.();
//    leecher.start();
//    leecher.wait();

//    Leecher leecher( peers,tipo_download,portaRastreador,rtt,e,falha);
//    leecher.ConfigFileDownload(hash,path,log_leecher,log_player);
//    leecher.run();
//}

void Widget::on_btn_add_clicked() {


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
    Leecher leecher( peers,tipo_download,porta_rastreador,rtt,e,falha);
    leecher.ConfigFileDownload(hash.c_str(),path.c_str(),logLeecher.c_str(),logLeecher.c_str());
    leecher.Run();

////    StartLeecher(peers,tipo_download,porta_rastreador,rtt,e,falha,path.c_str(),hash.c_str(),logLeecher.c_str(),logPlayer.c_str());
//    std::thread Leecher( StartLeecher,peers,tipo_download,porta_rastreador,rtt,e,falha,path.c_str(),hash.c_str(),logLeecher.c_str(),logPlayer.c_str());

    QString filePath = path.c_str();
    QList<QStandardItem *> items;
    items.append(new QStandardItem(filePath));
    m_playListModel->appendRow(items);
    m_player->setMedia(QMediaContent(QUrl::fromLocalFile(filePath)));
    m_player->setPlaylist(m_playlist);
//    leecher->thread().j;
//    Leecher.join();




}