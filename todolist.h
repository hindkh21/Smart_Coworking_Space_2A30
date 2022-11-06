#ifndef TODOLIST_H
#define TODOLIST_H
#include <QString>
#include <QSqlQueryModel>

class ToDoList
{
    QString id_emp,task,etat;

public:
    ToDoList();
    ToDoList(QString, QString, QString);


    bool ajouter();
    QSqlQueryModel * afficher(QString);
    bool supprimer(QString);
    bool modifier(int);


    QSqlQuery select(QString);
};

#endif // TODOLIST_H
