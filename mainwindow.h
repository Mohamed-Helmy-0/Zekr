#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QFile>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QTimer>
#include <QCoreApplication>

#include "about.h"
#include "setting.h"
#include "main.h"


class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
private slots:
    void openAboutWidget(void);
    void openSettingWidget(void);
    void setNotificationHourRateNewValue(int value);
private:

    void createActions(void);
    void notfiyZekr(void);
    QVector<QString> Prayers;
    QTimer prayerTimer;

    QAction *aboutAction;
    QAction *quitAction;
    QAction *settingAction;
    about aboutWidget;
    Setting *settingWidget;
    void createTrayIcon(void);
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;


};
#endif // MAINWINDOW_H
