#ifndef EMPLOYE_H
#define EMPLOYE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDate>

class Employe
{
    QString nom_emp, prenom_emp, id_emp, profile_emp, email_emp, login_emp , pwd_emp;
    int cin_emp;
    float salaire;
    QDate date_nais;


public:
    Employe();
    Employe(QString,QString,QString,QString,QString,QString,int,float,QString,QDate);

    //Get
    QString getID(){return id_emp;}
    QString getNom(){return nom_emp;}
    QString getPrenom(){return prenom_emp;}


    //Set
    void setID(QString id){this->id_emp=id;}
    void setNom(QString n){nom_emp=n;}
    void setPrenom(QString p){prenom_emp=p;}



    //CRUD
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier();

    QSqlQuery select(QString);
    QSqlQueryModel * recherche(QString);

};

#endif // EMPLOYE_H
