//
// Created by rafael on 16/04/19.
//

#ifndef RATHED_LEECHER_WIDGET_H
#define RATHED_LEECHER_WIDGET_H


#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
//static void startLeecher(std::string hash,std::string path);


private slots:
    void on_btn_add_clicked();              // Slot para processar adicionando faixas através da caixa de diálogo

private:
    Ui::Widget *ui;
    QStandardItemModel  *m_playListModel;   // Modelo de dados da lista de reprodução para exibição
    QMediaPlayer        *m_player;          // Jogador pista
    QMediaPlaylist      *m_playlist;        // Lista de reprodução do player
};

#endif //RATHED_LEECHER_WIDGET_H
