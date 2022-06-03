#include "mainwindow.h"

MainWindow::MainWindow()
{
    createActions();
    createTrayIcon();
    trayIcon->show();
    settingWidget= new Setting();


    QFile file("./../Zekr/DB/azkar.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0,"error",file.errorString());
    }
    QTextStream in(&file);
    while(!in.atEnd())
    {
      Prayers.push_back(in.readLine());
    }
    connect(&prayerTimer,&QTimer::timeout,this,&MainWindow::notfiyZekr);
    connect(settingWidget,&Setting::sig_notificationRateChange,this,&MainWindow::setNotificationHourRateNewValue);
    notfiyZekr();

}

MainWindow::~MainWindow()
{
    delete trayIconMenu;
    delete trayIcon;
    delete quitAction;
    delete settingWidget;
}

void MainWindow::createActions()
{
    settingAction = new QAction(tr("&Setting"), this);
    settingAction->setIcon(QIcon(":/Images/setting_icon.png"));
    connect(settingAction, &QAction::triggered, this, &MainWindow::openSettingWidget);

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setIcon(QIcon(":/Images/About_icon.png"));
    connect(aboutAction, &QAction::triggered,  this, &MainWindow::openAboutWidget);

    quitAction = new QAction(tr("&Quit"), this);
    quitAction->setIcon(QIcon(":/Images/exit_icon.png"));
    connect(quitAction, &QAction::triggered, this, &MainWindow::close);

}

void MainWindow::notfiyZekr()
{

    qint32 random = QRandomGenerator::global()->bounded(0, Prayers.size());
    trayIcon->showMessage(PROMGRAM_NAME, Prayers.at(random).toLocal8Bit() ,  QIcon(":/Images/Dua_icon.png"),
                           10000);
}

void MainWindow::openAboutWidget()
{
    aboutWidget.show();
}

void MainWindow::openSettingWidget()
{
    settingWidget->show();
}

void MainWindow::setNotificationHourRateNewValue(int value)
{
    //ms*1000=s*60=m*60=hour
    prayerTimer.start(value*1000*60*60);
}

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(settingAction);
    trayIconMenu->addAction(aboutAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/Images/Pro_Icon.png"));

}
