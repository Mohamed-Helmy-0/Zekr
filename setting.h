#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSettings>
#include <QAbstractButton>
#include <QDebug>
#include <QTimer>


#include "main.h"


namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();


private slots:

    void on_ObuttonBox_accepted();

    void on_ObuttonBox_rejected();

private:
    Ui::Setting *ui;
    int NotificationHourRate=1;
    int startWithWindows=true;
    QTimer timerforStartup;
    void timeOut(void);

signals:
    void sig_notificationRateChange(int value);

};

#endif // SETTING_H
