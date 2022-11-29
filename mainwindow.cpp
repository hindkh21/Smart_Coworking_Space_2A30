#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gestionemploye.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_emp_clicked()
{
    GestionEmploye *Emp;
    Emp = new GestionEmploye();
    Emp->show();

}
