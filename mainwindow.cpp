#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gestionemploye.h"
#include "gestionclient.h"
#include "gestionespace.h"

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

void MainWindow::on_pb_client_clicked()
{
    gestionClient *Cl;
    Cl = new gestionClient();
    Cl->show();
}

void MainWindow::on_pb_espace_clicked()
{
   gestionEspace *ES;
   ES=new gestionEspace();
   ES->show();
}
