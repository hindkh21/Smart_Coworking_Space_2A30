#include "abonnement.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include "mainwindow.h"
#include<QTableView>
abonnement::abonnement()
{
ID_A=0;
}

abonnement::abonnement(int ID_A,int nb_mois)
{this->ID_A=ID_A;this->nb_mois=nb_mois;}
int abonnement::getID_A(){return ID_A;}
int abonnement::getnb_mois(){return  nb_mois;}
void abonnement::setID(int ID_A){this->ID_A=ID_A;}
void abonnement::setnb_mois(int nb_mois){this->nb_mois=nb_mois;}


bool abonnement::ajouter()
{
    QString id_string=QString::number(ID_A);
    QSqlQuery query;
          query.prepare("INSERT INTO abonnement (ID_A,nb_mois) "
                        "VALUES (:id, :nb_mois)");
          query.bindValue(":id", id_string);
          query.bindValue(":nb_mois", nb_mois);

 return query.exec();
}


QSqlQueryModel* abonnement::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("select * from abonnement");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NB_MOIS"));
    return model;

}
bool abonnement::supprimer(int ID_A)
{
    QSqlQuery query;
          query.prepare("DELETE FROM abonnement where ID_A= :ID_A");

          query.bindValue(0,ID_A);

          return query.exec();
}
bool abonnement::modifier()
{

    QSqlQuery query;
    QString id_string=QString::number(ID_A);
    query.prepare("UPDATE abonnement SET NB_MOIS=:NB_MOIS WHERE ID_A=:ID_A");
    query.bindValue(":ID_A", id_string);
    query.bindValue(":NB_MOIS", nb_mois);
    return query.exec();

}
void abonnement::chercheID(QTableView *table, int ID_A)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from abonnement where regexp_like(ID_A,:ID_A);");
   query->bindValue(":ID_A",ID_A);
   if(ID_A==0)
   {
       query->prepare("select * from abonnement;");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}
void abonnement::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}
QSqlQueryModel * abonnement::tri_ID_A()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from ABONNEMENT order by ID_A");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_A"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NB_MOIS"));


    return model;
}
QSqlQueryModel * abonnement::tri_NB_MOIS()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from ABONNEMENT order by NB_MOIS");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_A"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NB_MOIS"));

    return model;
}


