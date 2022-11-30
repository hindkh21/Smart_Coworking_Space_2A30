#ifndef CLIENT_H
#define CLIENT_H

#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QDebug>
#include <QSqlError>

class Client
{
    int id,num_tel;
    QString nom,prenom,email,type;
public:
    Client();
    Client(int,QString,QString,int,QString,QString);
    int getid();
    QString getprenom();
    QString getnom();
    QString getemail();
    QString gettype();
    int getnumtel();
    void setid(int);
    void setprenom(QString);
    void setnom(QString);
    void setnumtel(int);
    void setemail(QString);
    void settype(QString);
    bool ajouter();
    int calcul_type_stat(QString);
    QSqlQueryModel *afficher();
    QSqlQueryModel *afficher1();

    bool supprimer(QString nom);
    bool modifier(int);
    QSqlQueryModel *recherche(QString nom,QString prenom,QString type);
    void getDatabaseValue(int id);

};

#endif // CLIENT_H
