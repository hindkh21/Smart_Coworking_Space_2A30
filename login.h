#ifndef LOGIN_H
#define LOGIN_H
#include <QString>
#include <QSqlQueryModel>
#include <QDate>
#include<QTableView>
//77
class login
{
public:
    login();
    login(QString,QString);
    login(QString,QString,QString,QString,QString,QString);
    QString getnom();
    QString getprenom();
    QString getusername();
    QString getmotdepasse();
    QString getquestion();
    QString getreponse();
    void setnom(QString);
    void setprenom(QString);
    void setusername(QString);
    void setmotdepasse(QString);
    void setquestion(QString);
    void setreponse(QString);
    bool ajouterL();
    bool modifier();
private:
    QString nom,prenom,username,motdepasse,question,reponse;
};

#endif // LOGIN_H
