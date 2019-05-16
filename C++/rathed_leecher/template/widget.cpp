//
// Created by rafael on 16/04/19.
//

#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDir>
#include <Leecher.h>


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

void Widget::on_btn_add_clicked() {
    std::ifstream i("/home/rafael/Documentos/Projetos/RaThEd/C++/config/config.json");
    json j;
    i >> j;
    std::string hash = j["leecher"]["hash_file"];
    std::string path = j["leecher"]["local_download"];
    std::string log = j["leecher"]["log"];
    int rtt=j["camada_de_rede"]["rtt"];
    int falha=j["camada_de_rede"]["falha"];

    leecher = new Leecher(j["tipo_download"],j["rastreador"]["porta"],rtt,falha);
    leecher->configFileDownload(hash,path,log.c_str());
    leecher->start();


    QString filePath = path.c_str();
    QList<QStandardItem *> items;
    items.append(new QStandardItem(filePath));
    m_playListModel->appendRow(items);
    m_player->setMedia(QMediaContent(QUrl::fromLocalFile(filePath)));
    m_player->setPlaylist(m_playlist);

}