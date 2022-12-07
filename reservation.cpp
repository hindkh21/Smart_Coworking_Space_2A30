#include "reservation.h"
#include <QtDebug>
#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QDateTime>
#include <QDate>
#include <QFile>

reservation::reservation()
{
    CIN=0;
    NOM=" ";
    PRENOM=" ";
    NUM_TEL=0;
    PLACES=" ";
    PERSONNES=0;
}
reservation::reservation(int  CIN, QString NOM, QString PRENOM ,int  NUM_TEL ,QString PLACES,int  PERSONNES,QString RFID)
{
    this->CIN=CIN;
    this->NOM=NOM;
    this->PRENOM=PRENOM;
    this->NUM_TEL=NUM_TEL;
    this->PLACES=PLACES;
    this->PERSONNES=PERSONNES;
    this->RFID=RFID;

}
int reservation::getcin(){return CIN;}
QString reservation::getnom(){return NOM;}
QString reservation::getprenom(){return PRENOM;}
int reservation::getnumtel(){return NUM_TEL;}
QString reservation::getplace(){return PLACES;}
int  reservation::getpersonnes(){return PERSONNES;}
QString reservation::getrfid(){return RFID;}



void reservation::setcin(int CIN){this->CIN=CIN;}
void reservation::setnom(QString NOM){this->NOM=NOM;}
void reservation::setprenom(QString PRENOM){this->PRENOM=PRENOM;}
void reservation::setnumtel(int NUM_TEL){this->NUM_TEL=NUM_TEL;}
void reservation::setplace(QString PLACES){this->PLACES=PLACES;}
void reservation::setpersonnes(int PERSONNES){this->PERSONNES=PERSONNES;}
void reservation::setrfid(QString RFID){this->RFID=RFID;}



bool reservation::AjouterF()
{
    QSqlQuery query;
    QString cin_string=QString::number(CIN);
         query.prepare("INSERT INTO RESERVATION(CIN,NOM,PRENOM,NUM_TEL,PLACES,PERSONNES,RFID)" "VALUES (:CIN,:NOM,:PRENOM,:NUM_TEL,:PLACES,:PERSONNES,:RFID)");
         query.bindValue(":CIN", CIN);
         query.bindValue(":NOM", NOM);
         query.bindValue(":PRENOM", PRENOM);
         query.bindValue(":NUM_TEL", NUM_TEL);
         query.bindValue(":PLACES", PLACES);
         query.bindValue(":PERSONNES", PERSONNES);
         query.bindValue(":RFID", RFID);


    return query.exec();
}
bool reservation::SupprimerF(int CIN)
{
    QSqlQuery query;
         query.prepare("DELETE FROM RESERVATION where CIN= :CIN");
         query.bindValue(0, CIN);
    return query.exec();
}
QSqlQueryModel* reservation::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT* FROM RESERVATION");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUM_TEL"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("PLACES"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("PERSONNES"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("RFID"));

    return  model;
}
bool reservation::ModifierF()
{
    QSqlQuery query;
        query.prepare("UPDATE RESERVATION SET NOM=:NOM, PRENOM=:PRENOM, NUM_TEL=:NUM_TEL, PLACES=:PLACES, PERSONNES=:PERSONNES WHERE CIN=:CIN ");
        query.bindValue(":NOM", NOM);
        query.bindValue(":PRENOM", PRENOM);
        query.bindValue(":NUM_TEL", NUM_TEL);
        query.bindValue(":PLACES", PLACES);
        query.bindValue(":CIN", CIN);
        query.bindValue(":PERSONNES", PERSONNES);
        query.bindValue(":RFID", RFID);

    return query.exec();
}
QSqlQueryModel* reservation::afficher_cin()
{
    QSqlQueryModel* model=new QSqlQueryModel();
        model->setQuery("SELECT CIN from RESERVATION");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    return model;
}
QSqlQueryModel * reservation::tri_cin()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from RESERVATION order by CIN");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUM_TEL"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("PLACES"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("PERSONNES"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("RFID"));



    return model;
}
QSqlQueryModel * reservation::tri_numtel()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from RESERVATION order by NUM_TEL");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUM_TEL"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("PLACES"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("PERSONNES"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("RFID"));


    return model;
}
QString reservation::read()
{
    QFile file("C:/Users/hamza/Documents/AtelierCRUD/history.txt");
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0,"info",file.errorString());
    QTextStream in(&file);
    return  in.readAll();
}
void reservation::write(QString time, QString txt)
{
    QFile file("C:/Users/hamza/Documents/AtelierCRUD/history.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream<<time<<" "<<txt<<endl;
        file.close();
    }
}
QString reservation::time()
{
    QDateTime time=time.currentDateTime();
    return  time.toString();
}
void reservation::clearh()
{
    QFile file("C:/Users/hamza/Documents/AtelierCRUD/history.txt");
    file.open(QFile::WriteOnly|QFile::Truncate);
}
void reservation::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}
void reservation::chercheCIN(QTableView *table, int x)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from RESERVATION where regexp_like(CIN,:CIN);");
   query->bindValue(":CIN",x);
   if(x==0)
   {
       query->prepare("select * from RESERVATION;");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}
void reservation::chercheNumTel(QTableView *table, int x)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from RESERVATION where regexp_like(NUM_TEL,:NUM_TEL);");
   query->bindValue(":NUM_TEL",x);
   if(x==0)
   {
       query->prepare("select * from RESERVATION;");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}

