#ifndef RESERVATION_H
#define RESERVATION_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDoubleValidator>
#include <QtDebug>
#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QTableView>


class reservation
{
public:
    reservation();
    reservation(int,QString,QString,int,QString,int,QString);

    int getcin();
    QString getnom();
    QString getprenom();
    int getnumtel();
    QString getplace();
    int getpersonnes();
    QString getrfid();


    void setcin(int);
    void setnom(QString);
    void setprenom(QString);
    void setnumtel(int);
    void setplace(QString);
    void setpersonnes(int);
    void setrfid(QString);


    bool AjouterF();
    bool ModifierF();
    bool SupprimerF(int);
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher_cin();
    QSqlQueryModel* tri_cin();
    QSqlQueryModel* tri_numtel();

    QString read();
    void write(QString,QString);
    QString time();
    void clearh();
    void clearTable(QTableView * table);
    void chercheCIN(QTableView *table, int x);
    void chercheNumTel(QTableView *table, int x);

private:
    int CIN;
    QString NOM;
    QString PRENOM;
    int NUM_TEL;
    QString PLACES;
    int PERSONNES;
    QString RFID;


};

#endif // RESERVATION_H
