
#include "about.h"


about::about(QWidget *parent) :
    QDialog(parent)
{


    setWindowIcon(QIcon(":/Images/Pro_Icon.png"));
    setWindowTitle("About");



    programNameLabel= new QLabel(PROMGRAM_NAME);
    programNameLabel->setAlignment(Qt::AlignHCenter);
    programNameLabel->setFont(QFont("times",20,QFont::Normal));


    programVerLabel= new QLabel("ver 1.0");
    programVerLabel->setAlignment(Qt::AlignHCenter);
    programVerLabel->setFont(QFont("times",8,QFont::Normal));

    duaIconLabel = new QLabel("");
    duaIconLabel->setAlignment(Qt::AlignHCenter);
    QPixmap dua_image(":/Images/Dua_icon.png");

    duaIconLabel->setPixmap(dua_image.scaled(100,100,Qt::KeepAspectRatio));
    QString tempString=PROMGRAM_NAME;
    tempString.append(" program developed by Mohamed Helmy");
    programDeveloperNameLabel= new QLabel(tempString);
    programDeveloperNameLabel->setAlignment(Qt::AlignHCenter);
    programDeveloperNameLabel->setFont(QFont("times",10,QFont::Normal));

    closeButton = new QPushButton("Close",this);
    connect(closeButton, &QPushButton::clicked, this, &about::hide);


    QVBoxLayout *iconLayout = new QVBoxLayout;
    iconLayout->addWidget(programNameLabel,0, Qt::AlignTop);
    iconLayout->addWidget(programVerLabel,0,Qt::AlignTop);
    iconLayout->addWidget(duaIconLabel);
    iconLayout->addSpacing(25);
    iconLayout->addWidget(programDeveloperNameLabel);
    iconLayout->addSpacing(50);
    iconLayout->addWidget(closeButton);

    setLayout(iconLayout);
    resize(400, 300);
}

about::~about()
{
    delete programNameLabel;
    delete programVerLabel;
    delete programDeveloperNameLabel;
}
