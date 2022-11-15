#include "todolist.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QMessageBox>
#include<QSqlQueryModel>

ToDoList::ToDoList(){}

ToDoList::ToDoList(QString id_emp, QString task, QString etat)
{
    this->id_emp=id_emp;
    this->task=task;
    this->etat=etat;
}

bool ToDoList::ajouter()
{
    QSqlQuery query;

    query.prepare("insert into taches (task, etat, id_emp)" "values (:task , :etat ,:id_emp)");

    query.bindValue(":task",task);
    query.bindValue(":etat",etat);
    query.bindValue(":id_emp",id_emp);

    return query.exec();
}


QSqlQueryModel * ToDoList::afficher(QString id)
{
    QSqlQuery *qry= new QSqlQuery();
    qry->prepare("select id_tache, task, etat from taches where id_emp=:id_emp");
    qry->bindValue(":id_emp",id);
    qry->exec();

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(*qry);

    return model;
}

QSqlQuery ToDoList::select(QString val)
{
    QSqlQuery qry;
    qry.prepare("select * from taches where id_tache=?");
    qry.addBindValue(val);

    return qry;
}

bool ToDoList::supprimer(QString id_tache)
{
    QSqlQuery query;

    query.prepare("Delete from taches where id_tache= :id_tache");
    query.bindValue(":id_tache",id_tache);
    return query.exec();
}

bool ToDoList::modifier(int id_tache)
{
    QSqlQuery query;
    QString id=QString::number(id_tache);

    query.prepare("update taches set task= :task, etat= :etat where id_tache= :id_tache" );
    query.bindValue(":id_tache",id);
    query.bindValue(":etat",etat);
    query.bindValue(":task",task);

    return  query.exec();
}

int ToDoList::nbr_tache(QString etat)
{
     QSqlQuery query;
     query.prepare("SELECT * FROM TACHES where etat= :etat");
     query.bindValue(":etat", etat);
     query.exec();

     int total = 0;
     while (query.next())
      {
          total++;
      }

     return total;
}

QString ToDoList::verification(QString id)
{
    QSqlQuery qry;
    qry.prepare("select profile_emp from employe where id_emp=?");
    qry.addBindValue(id);
    qry.exec();
    qry.first();
    QString profile=qry.value(0).toString();
    return profile;
}

QSqlQueryModel * ToDoList::filtre(QString etat, QString id)
{
    QSqlQuery *qry= new QSqlQuery();
    qry->prepare("SELECT * FROM TACHES WHERE etat= :etat and id_emp= :id_emp");
    qry->bindValue(":etat",etat);
    qry->bindValue(":id_emp",id);
    qry->exec();

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(*qry);

    return model;
}


