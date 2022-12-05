#include "login.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include "gestion_abonnement.h"
#include<QTableView>
#include <QString>
//1
login::login()
{
    nom=" ",prenom="",username="",motdepasse="",reponse="",question="";
}
login::login(QString nom,QString prenom,QString username,QString motdepasse,QString question,QString reponse)
{
    this->nom=nom;this->prenom=prenom;this->username=username;this->motdepasse=motdepasse;this->question=question;this->reponse=reponse;
}
login::login(QString motdepasse,QString username)
{
    this->motdepasse=motdepasse;this->username=username;
}
QString login::getnom(){return nom;}
QString login::getprenom(){return prenom;}
QString login::getusername(){return username;}
QString login::getmotdepasse(){return motdepasse;}
QString login::getquestion(){return question;}
QString login::getreponse(){return reponse;}
void login::setnom(QString nom){this->nom=nom;}
void login::setprenom(QString prenom){this->prenom=prenom;}
void login::setusername(QString username){this->username=username;}
void login::setmotdepasse(QString motdepasse){this->motdepasse=motdepasse;}
void login::setquestion(QString question){this->question=question;}
void login::setreponse(QString reponse){this->reponse=reponse;}
bool login::ajouterL()
{
    QSqlQuery query;
          query.prepare("INSERT INTO LOGIN (nom,prenom,username,motdepasse,question,reponse) "
                        "VALUES (:nom,:prenom,:username,:motdepasse,:question,:reponse)");
          query.bindValue(":nom",username);
          query.bindValue(":prenom",prenom);
          query.bindValue(":username",nom);
          query.bindValue(":motdepasse",motdepasse);
          query.bindValue(":question",question);
          query.bindValue(":reponse",reponse);

 return query.exec();
}
bool login::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE login set MOTDEPASSE=:MOTDEPASSE WHERE username=:username");
    query.bindValue(":MOTDEPASSE", motdepasse);
    query.bindValue(":username", username);
    return query.exec();
}
