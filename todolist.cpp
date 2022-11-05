#include "todolist.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QMessageBox>

ToDoList::ToDoList()
{

}
/*
bool ToDoList::ajouter()
{
    QSqlQuery query;

    query.prepare("insert into taches (task, etat, id_emp, id_tache)" "values (:task , :etat ,:id_emp , :id_tache)");

    query.bindValue(":task",task);
    query.bindValue(":etat",etat);
    query.bindValue(":id_emp",id_emp);
    query.bindValue(":id_tache",id_tache);

    return query.exec();
}*/

/*
QSqlQueryModel * ToDoList::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from employe e, taches t where e.id_emp=t.id_emp and e.id_emp:=id_emp ");
    /////

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("TACHES"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ETAT"));

    return model;
}

*/

/*
bool ToDoList::supprimer(QString id_emp)
{
    QSqlQuery query;

    query.prepare("Delete from taches where id_emp= :id_emp");
    query.bindValue(":id_emp",id_emp);

    return query.exec();
}

bool Employe::modifier()
{
    QSqlQuery query;

    query.prepare("update taches set task:=task, etat:=etat" );

    query.bindValue(":id_emp",id_emp);
    query.bindValue(":nom_emp",nom_emp);

    return  query.exec();
}

  */

/*
  select * from employe e, taches t where e.id_emp=t.id_emp and e.id_emp='154ADF'
  insert into taches (task, etat, id_emp,id_tache) VALUES('mathhhh','faite','154ADF','8')
*/
