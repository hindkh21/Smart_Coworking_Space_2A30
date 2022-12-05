#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gestionemploye.h"
#include "gestionclient.h"
#include "gestionespace.h"
#include"gestion_abonnement.h"
#include "login.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);
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

void MainWindow::on_pb_ab_clicked()
{ gestion_abonnement *A;
    A=new gestion_abonnement();
    A->show();

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_motdepasseoublier_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_8_clicked()
{
    QString username=ui->lineEdit_email->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString nom=ui->lineEdit_nom->text();
    QString motdepasse=ui->lineEdit_motdepasse->text();
    QString question=ui->quest->currentText();
    QString reponse=ui->reponse->text();
    login L(username,prenom,nom,motdepasse,question,reponse);


    bool test=L.ajouterL();
    if(test)
    {

    QMessageBox::information(nullptr, QObject::tr("Ok"),
                  QObject::tr("Ajout effectué.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
    ui->lineEdit_nom->setText("");
    ui->lineEdit_prenom->setText("");
    ui->lineEdit_email->setText("");
    ui->lineEdit_motdepasse->setText("");
    ui->reponse->setText("");
    ui->quest->setCurrentText("");
  }
         else

             QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                  QObject::tr("Ajout non effectué.\n""minimum 8 caractère mot de passe\n""minimum 5 caractère username\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_valid_2_clicked()
{
    QString username,password;
    username=ui->lineEdit_email_2->text();
    password=ui->pass_2->text();
    QSqlQuery qry;
    if(qry.exec("select *from login where username='"+username+"'and motdepasse='"+password+"'"))
    {
        int count=0;
        while(qry.next())
        {
            count++;
        }
        if(count==1){
           ui->stackedWidget->setCurrentIndex(0);
        }
        if(count<1)
            ui->label->setText("username or password incorrect");
    }
    ui->lineEdit_email_2->setText("");
    ui->pass_2->setText("");
}

void MainWindow::on_AJOUTER_4_clicked()
{
    QString username,question,reponse;
    username=ui->lineEdit_email_3->text();
    reponse=ui->reponse_2->text();
    question=ui->quest_2->currentText();
    QSqlQuery qry;
    if(qry.exec("select *from login where username='"+username+"'and question='"+question+"'and reponse='"+reponse+"'"))
    {
        int nb=0;
        while(qry.next())
        {
            nb++;
        }
        if(nb==1){
        ui->stackedWidget->setCurrentIndex(4);
        ui->reponse_2->setText("");
        ui->label_2->setText("");
    }
        if(nb<1)
            ui->label_3->setText("username or question or reponse incorrect");
    }
}

void MainWindow::on_confnouv_clicked()
{
    QString motdepasse=ui->new_2->text();
    QString username=ui->lineEdit_email_3->text();
    qDebug() << username + "" + motdepasse;

    login l(motdepasse,username);
    bool test=l.modifier();
    if (test)
    {
    QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Modification effectue\n ""click cancel"),QMessageBox::Cancel);

    }
    else
    {QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("Modification non fonctional\n""click to cancel"),QMessageBox::Cancel);}

    ui->new_2->setText("");
}

void MainWindow::on_retouroublier_2_clicked()
{
   ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_retouroublier_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_retouroublier_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
int modes=1;
void MainWindow::on_checkBox_2_clicked()
{
    if(modes==1)
    {
    ui->pass_2->setEchoMode(QLineEdit::Normal);
    modes=0;
    }
    else
    {
        ui->pass_2->setEchoMode(QLineEdit::Password);
        modes=1;
    }
}

void MainWindow::on_checkBox_3_clicked()
{
    if(modes==1)
    {
    ui->new_2->setEchoMode(QLineEdit::Normal);
    modes=0;
    }
    else
    {
        ui->new_2->setEchoMode(QLineEdit::Password);
        modes=1;
    }
}
