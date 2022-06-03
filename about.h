#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QIcon>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QGroupBox>
#include <QPixmap>

#include <QDebug>
#include <QSpacerItem>
#include <QPushButton>

#include "main.h"

namespace Ui {
class about;
}

class about : public QDialog
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = nullptr);
    ~about();

private:
    QLabel *programNameLabel;
    QLabel *programVerLabel;
    QLabel *programDeveloperNameLabel;
    QLabel *duaIconLabel;
    QPushButton *closeButton;


};

#endif // ABOUT_H
