#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "abonnement.h"
#include "login.h"
#include <QMessageBox>
#include "connection.h"
#include <QDate>
#include <QString>
#include <QtGlobal>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPushButton>
#include "dialog_stats.h"
#include "exportexcelobject.h"
//1
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->view->setModel(f.afficher());
    ui->stackedWidget->setCurrentIndex(0);
    ui->id_a->setValidator(new QIntValidator(00000001,99999999,this));
    ui->id_s->setValidator(new QIntValidator(00000001,99999999,this));
    int ret=a.connect_arduino();
    switch(ret){
    case(0):qDebug()<<"arduino is available and connected to :"<<a.getarduino_port_name();
    break;
    case(1):qDebug()<<"arduino is available but not connected to :"<<a.getarduino_port_name();
    break;
    case(-1):qDebug()<<"arduino is not available";
    }
    QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label() ));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_AJOUTER_2_clicked()
{
    int ID_A=ui->id_a->text().toInt();
    int nb_mois=ui->nb_mois->currentIndex();
    abonnement A(ID_A,nb_mois);
    bool test=A.ajouter();
    if(test)
    {
        ui->view->setModel(f.afficher());
    QMessageBox::information(nullptr, QObject::tr("Ok"),
                  QObject::tr("Ajout effectué.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
         }
         else

             QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                  QObject::tr("Ajout non effectué.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
 ui->id_a->setText("");
}


void MainWindow::on_supp_clicked()
{
    int ID_A=(ui->id_s->text().toInt());
        bool test=f.supprimer(ID_A);
        if(test)
        {
            ui->view->setModel(f.afficher());
            QMessageBox::information(nullptr, QObject::tr("Ok"),
                 QObject::tr("Suppression effectué\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else

            QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                 QObject::tr("Suppression non effectué.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);

ui->id_s->setText("");
}
int mode =1;
void MainWindow::on_checkBox_2_clicked()
{
    if(mode==1)
    {
    ui->pass_2->setEchoMode(QLineEdit::Normal);
    mode=0;
    }
    else
    {
        ui->pass_2->setEchoMode(QLineEdit::Password);
        mode=1;
    }
}
void MainWindow::on_supp_2_clicked()
{
        int ID_A=ui->id_a->text().toInt();
        int nb_mois=ui->nb_mois->currentIndex();

        abonnement A(ID_A,nb_mois);
        bool test=A.modifier();
        if (test)
        { ui->view->setModel(f.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Modification effectue\n ""click cancel"),QMessageBox::Cancel);

        }
        else
        {QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("Modification non fonctional\n""click to cancel"),QMessageBox::Cancel);}

        ui->id_s->setText("");

}



void MainWindow::on_supp_4_clicked()
{
    QPdfWriter pdf("C:/Users/gamer/Desktop/Atelier_Connexion/Atelier_Connexion/Liste.pdf");

        QPainter painter(&pdf);

        int i = 4000;

        painter.drawText(3000,1500,"LISTE DES ABONNEMENT");
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Arial", 50));
        painter.drawRect(2700,200,6300,2600);
        painter.drawRect(0,3000,9600,500);
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 9));
        painter.drawText(300,3300,"ID_A");
        painter.drawText(2300,3300,"DATE_D");
        painter.drawText(4300,3300,"DATE_F");
        QSqlQuery query;

        query.prepare("select * from ABONNEMENT");
        query.exec();
        while (query.next())
        {
            painter.drawText(300,i,query.value(0).toString());
            painter.drawText(2300,i,query.value(1).toString());
            painter.drawText(4300,i,query.value(2).toString());

            i = i +500;
        }
        int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
        if (reponse == QMessageBox::Yes)
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/gamer/Desktop/Atelier_Connexion/Atelier_Connexion/Liste.pdf"));
            painter.end();
        }
        if (reponse == QMessageBox::No)
        {
            painter.end();
        }
}

void MainWindow::on_supp_3_clicked()
{
    abonnement a;
        QString text;
            a.clearTable(ui->view);
                int ID_A=ui->id_s->text().toInt();
                a.chercheID(ui->view,ID_A);
}

void MainWindow::on_supp_6_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("tri effectué.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
            ui->view->setModel(f.tri_ID_A());
}

void MainWindow::on_supp_5_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("tri effectué.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
            ui->view->setModel(f.tri_NB_MOIS());
}


void MainWindow::on_supp_8_clicked()
{
    Dialog_stats stats;
    stats.setModal(true);
    stats.exec();

}

void MainWindow::on_supp_9_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                        tr("Excel Files (*.xls)"));
        if (fileName.isEmpty())
            return;

        ExportExcelObject obj(fileName, "ABONNEMENT", ui->view);

        //colums to export
        obj.addField(0, "ID_A", "char(20)");
        obj.addField(1, "NB_MOIS", "char(20)");




        int retVal = obj.export2Excel();
        if( retVal > 0)
        {
            QMessageBox::information(this, tr("Done"),
                                     QString(tr("%1 records exported!")).arg(retVal)
                                     );
        }
    }

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
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
           ui->stackedWidget->setCurrentIndex(2);
        }
        if(count<1)
            ui->label->setText("username or password incorrect");
    }
    ui->lineEdit_email_2->setText("");
    ui->pass_2->setText("");
}

void MainWindow::on_AJOUTER_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->label->setText("");
}

void MainWindow::on_motdepasseoublier_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_retouroublier_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit_email_3->setText("");
    ui->reponse_2->setText("");
    ui->label_2->setText("");
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
            ui->label_2->setText("username or question or reponse incorrect");
    }
}

void MainWindow::on_retouroublier_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit_email_3->setText("");
    ui->new_2->setText("");
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

    ui->id_s->setText("");
}





void MainWindow::on_checkBox_3_clicked()
{
    if(mode==1)
    {
    ui->new_2->setEchoMode(QLineEdit::Normal);
    mode=0;
    }
    else
    {
        ui->new_2->setEchoMode(QLineEdit::Password);
        mode=1;
    }
}

void MainWindow::on_supp_7_clicked()
{
    a.write_to_arduino("1");
}
void MainWindow::update_label()
{
    data = a.read_from_arduino();
    if(data=="1"){
    ui->label_3->setText("MOUVEMENT DETECTEE");
    ui->label_4->setText("ON");

    }
    else if(data=="0"){
        ui->label_3->setText("PAS DE MOUVEMENT");
        ui->label_4->setText("OFF");}
    qDebug()<<"data"<<data;
}

void MainWindow::on_AJOUTER_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_retouroublier_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
