

#include <QApplication>
#include <QDebug>
#include <QMessageBox>

#include "mainwindow.h"
#include "setting.h"
#include "main.h"
#include "runguard.h"



int main(int argc, char *argv[])
{

    QCoreApplication::setOrganizationName("MH");
    QCoreApplication::setApplicationName("El Zekr");

    QApplication a(argc, argv);
    RunGuard guard( "EL_Zekrv1.0" );
    if ( !guard.tryToRun() )
    {
        QMessageBox::information(0,"ERROR","Program Zekr is Already Runnning");
        return 0;
    }
    MainWindow w;
    return a.exec();                  
}
