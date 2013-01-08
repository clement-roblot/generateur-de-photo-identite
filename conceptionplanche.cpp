#include "conceptionplanche.h"
#include "ui_conceptionplanche.h"

ConceptionPlanche::ConceptionPlanche(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ConceptionPlanche)
{
    ui->setupUi(this);
}

ConceptionPlanche::~ConceptionPlanche()
{
    delete ui;
}
