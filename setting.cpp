#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    setWindowTitle("Setting");
    QPixmap setting_icon(":/Images/Pro_Icon.png");
    this->setWindowIcon(setting_icon);
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);


//PROMGRAM_NAME
    QString tempString="Start ";
    tempString.append(PROMGRAM_NAME);
    tempString.append(" with Windows");
    ui->StartWithWindowsCheckBox->setText(tempString);

    QSettings settingsValues("MH",PROMGRAM_NAME);
    settingsValues.beginGroup("Setting");
    NotificationHourRate=settingsValues.value("NotificationHourRate",13).toInt();
    if(NotificationHourRate == 13)
    {
        settingsValues.setValue("NotificationHourRate",1);
        NotificationHourRate=1;
    }
    startWithWindows=settingsValues.value("startWithWindows",2).toInt();
    if(startWithWindows == 2)
    {
        settingsValues.setValue("startWithWindows",1);
        startWithWindows=1;
    }

    settingsValues.endGroup();
    //default
    ui->StartWithWindowsCheckBox->setChecked(startWithWindows);
    ui->hourSpinBox->setValue(NotificationHourRate);
    connect(&timerforStartup,&QTimer::timeout,this,&Setting::timeOut);

    timerforStartup.start(1000);

}

Setting::~Setting()
{
    delete ui;
}


void Setting::on_ObuttonBox_accepted()
{
    QSettings bootUpSettings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);


    QSettings setting("MH",PROMGRAM_NAME);
    setting.beginGroup("Setting");
    setting.setValue("NotificationHourRate", ui->hourSpinBox->value());
    if(ui->StartWithWindowsCheckBox->checkState() == Qt::Unchecked )
    {
        setting.setValue("startWithWindows", 0 );
        bootUpSettings.remove(PROMGRAM_NAME);



    }else
    {
        setting.setValue("startWithWindows", 1);

        QString app_path = QCoreApplication::applicationFilePath();
        QString apostroph = "\"";
        app_path.replace("/","\\");
        app_path = apostroph + app_path + apostroph + " --argument";
        bootUpSettings.setValue(PROMGRAM_NAME, app_path);


    }
    setting.endGroup();
    NotificationHourRate=ui->hourSpinBox->value();
    emit sig_notificationRateChange(NotificationHourRate);
    this->hide();
}


void Setting::on_ObuttonBox_rejected()
{
    this->hide();
}

void Setting::timeOut()
{
    emit sig_notificationRateChange(NotificationHourRate);
    timerforStartup.stop();
}

