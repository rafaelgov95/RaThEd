/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTableView *playlistView;
    QLabel *currentTrack;
    QProgressBar *progressBar;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QToolButton *btn_add;
    QToolButton *btn_play;
    QToolButton *btn_pause;
    QToolButton *btn_stop;
    QToolButton *btn_previous;
    QToolButton *btn_next;
    QSlider *volume;
    QLCDNumber *lcdNumber;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(482, 300);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        playlistView = new QTableView(Widget);
        playlistView->setObjectName(QString::fromUtf8("playlistView"));
        playlistView->setGeometry(QRect(10, 90, 461, 201));
        currentTrack = new QLabel(Widget);
        currentTrack->setObjectName(QString::fromUtf8("currentTrack"));
        currentTrack->setGeometry(QRect(150, 70, 161, 16));
        progressBar = new QProgressBar(Widget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(110, 40, 361, 20));
        progressBar->setValue(0);
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(12, 10, 414, 24));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btn_add = new QToolButton(layoutWidget);
        btn_add->setObjectName(QString::fromUtf8("btn_add"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/buttons/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_add->setIcon(icon);

        horizontalLayout->addWidget(btn_add);

        btn_play = new QToolButton(layoutWidget);
        btn_play->setObjectName(QString::fromUtf8("btn_play"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/buttons/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_play->setIcon(icon1);

        horizontalLayout->addWidget(btn_play);

        btn_pause = new QToolButton(layoutWidget);
        btn_pause->setObjectName(QString::fromUtf8("btn_pause"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/buttons/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_pause->setIcon(icon2);

        horizontalLayout->addWidget(btn_pause);

        btn_stop = new QToolButton(layoutWidget);
        btn_stop->setObjectName(QString::fromUtf8("btn_stop"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/buttons/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_stop->setIcon(icon3);

        horizontalLayout->addWidget(btn_stop);

        btn_previous = new QToolButton(layoutWidget);
        btn_previous->setObjectName(QString::fromUtf8("btn_previous"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/buttons/skip-previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_previous->setIcon(icon4);

        horizontalLayout->addWidget(btn_previous);

        btn_next = new QToolButton(layoutWidget);
        btn_next->setObjectName(QString::fromUtf8("btn_next"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/buttons/skip-next.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_next->setIcon(icon5);

        horizontalLayout->addWidget(btn_next);

        volume = new QSlider(layoutWidget);
        volume->setObjectName(QString::fromUtf8("volume"));
        volume->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(volume);

        lcdNumber = new QLCDNumber(Widget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(20, 40, 64, 23));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Rathred - Player", nullptr));
        currentTrack->setText(QString());
        btn_play->setText(QApplication::translate("Widget", "...", nullptr));
        btn_pause->setText(QApplication::translate("Widget", "...", nullptr));
        btn_stop->setText(QApplication::translate("Widget", "...", nullptr));
        btn_previous->setText(QApplication::translate("Widget", "...", nullptr));
        btn_next->setText(QApplication::translate("Widget", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
