//
// Created by cyril on 2020/11/3.
//

#include "tray.h"

#include <QAction>
#include <QApplication>
#include <QDebug>
#include <QMenu>

#include "clash/clash.h"
#include "mainwindow.h"
#include "util/instance.h"

Tray::Tray(QObject *parent) : QSystemTrayIcon(parent) {
    setIcon(QIcon(":/icon/clash"));
    setToolTip(QApplication::applicationName());
    connect(this, &QSystemTrayIcon::activated, this, &Tray::onActivate);


    menu = new QMenu;
    auto quit = new QAction(QIcon::fromTheme("application-exit"), tr("Quit"));
    menu->addAction(quit);
    connect(quit, &QAction::triggered, this, [] { qApp->quit(); });
    setContextMenu(menu);

    connect(getInstance<Clash>().api(), &Clash::RestfulApi::errorHappened, this, &Tray::onReceiveError);
}
void Tray::onActivate(QSystemTrayIcon::ActivationReason reason) {
    switch (reason) {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            getInstance<MainWindow>().show();
            getInstance<MainWindow>().activateWindow();
            break;
        default:;
    }
}
void Tray::onReceiveError(QString content) { this->showMessage("Error Happened", content, MessageIcon::Warning); }
