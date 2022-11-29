#include "statemploye.h"
#include "ui_statemploye.h"

statEmploye::statEmploye(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::statEmploye)
{
    ui->setupUi(this);
}

statEmploye::~statEmploye()
{
    delete ui;
}
