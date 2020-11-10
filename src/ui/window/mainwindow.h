#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

#include "clash/clash.h"

namespace Ui {
class MainWindow;
}
class QTreeWidgetItem;
class QButtonGroup;
class QAbstractButton;
class NetSpeedLabel;


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    void onLogLevelClicked(QAbstractButton *button);
    void onModeClicked(QAbstractButton *button);
    void onConfigUpdate(const QByteArray &rawJson);

    void updateProxies(const QByteArray &rawjson);
    void updateGroup(const QJsonObject &proxies, QString group, QTreeWidgetItem *item);
    void updateSelector(QString group, QString proxy);

    void loadProfiles();
    void saveProfiles();
    void useProfiles();
    void onProfileChanged(int index);

    void onClashStarted();

    void sendMixedPort();
    void sendHttpPort();
    void sendSocksPort();

    void allowLan(bool checked);

    void manageProfile();

private:
    Ui::MainWindow *ui;
    Clash &clash;

    QButtonGroup *log_level_group, *model_group;

    QStringList groups;
    QMap<QString, QTreeWidgetItem *> group_items;
    QMap<QString, QStringList> group_proxies;

    Clash::ProfileList profile_list;

    NetSpeedLabel *net_speed_label;
};

#endif  // MAINWINDOW_H
