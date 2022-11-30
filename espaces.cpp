#include "espaces.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>
#include <QTextStream>
#include <QTextDocument>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
Espaces::Espaces()
{

}

Espaces::Espaces(QString ID_ES,QString categorie,QString description,int nb_places,float superficie,float tarif,QString disponibilite,QString image)
{
    this->ID_ES=ID_ES;
    this->categorie=categorie;
    this->description=description;
    this->nb_places=nb_places;
    this->superficie=superficie;
    this->tarif=tarif;
    this->disponibilite=disponibilite;
    this->image=image;
}

Espaces::Espaces(QString ID_ES,float tarif,QString disponibilite)
{
    this->ID_ES=ID_ES;
    this->tarif=tarif;
    this->disponibilite=disponibilite;
}

bool Espaces::ajouter()
{
    QSqlQuery query;

    QString nb= QString::number(nb_places);
    QString t= QString::number(tarif);
    QString sup=QString::number(superficie);
    query.prepare("INSERT into espaces (ID_ES, categorie, description, nb_places, superficie, tarif, disponibilite, image)" "values (:ID_ES, :categorie, :description, :nb_places, :superficie, :tarif, :disponibilite, :image)");

    query.bindValue(":ID_ES",ID_ES);
    query.bindValue(":categorie",categorie);
    query.bindValue(":description",description);
    query.bindValue(":nb_places",nb);
    query.bindValue(":superficie",sup);
    query.bindValue(":tarif",t);
    query.bindValue(":disponibilite",disponibilite);
    query.bindValue(":image",image);
   return query.exec();
}


QSqlQueryModel* Espaces::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from Espaces");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_ES"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Categorie"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nb_Places"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Superficie"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Tarif"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Disponibilte"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Image"));

return model;
}

bool Espaces::supprimer(QString ID_ES)
{
    QSqlQuery query;
    query.prepare("Delete from Espaces where ID_ES=:ID_ES");

    query.bindValue(":ID_ES",ID_ES);

   return query.exec();
}

bool Espaces::modifier()
{
  QSqlQuery query;
  QString nb= QString::number(nb_places);
  QString t= QString::number(tarif);
  QString sup=QString::number(superficie);
  query.prepare("UPDATE ESPACES SET ID_ES=:ID_ES, categorie=:categorie, description=:description, nb_places=:nb_places, superficie=:superficie, tarif=:tarif, disponibilite=:disponibilite, image=:image WHERE ID_ES=:ID_ES ");
  query.bindValue(":ID_ES",ID_ES);
  query.bindValue(":categorie",categorie);
  query.bindValue(":description",description);
  query.bindValue(":nb_places",nb);
  query.bindValue(":superficie",sup);
  query.bindValue(":tarif",t);
  query.bindValue(":disponibilite",disponibilite);
  query.bindValue(":image",image);

return query.exec();
}

QSqlQueryModel * Espaces::tri_espaces()
{
 QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from ESPACES order by ID_ES");
 return model;
}

QSqlQueryModel * Espaces::chercher(QString cher)
{
    QSqlQueryModel * model= new QSqlQueryModel();

 model->setQuery("select * from ESPACES where upper(ID_ES) LIKE upper('%"+cher+"%')");
return model;
}

QSqlQuery Espaces::select(QString val)
{
    QSqlQuery qry;
    qry.prepare("select * from ESPACES where ID_ES=?");
    qry.addBindValue(val);
    return qry;
}
