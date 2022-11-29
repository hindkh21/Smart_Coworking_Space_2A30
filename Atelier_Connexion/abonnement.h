#ifndef ABONNEMENT_H
#define ABONNEMENT_H
#include <QString>
#include <QSqlQueryModel>
#include <QDate>
#include<QTableView>
//7
class abonnement
{
public:
    abonnement();
    abonnement(int,int);
    int getID_A();
    int getnb_mois();
    void setID(int);
    void setnb_mois(int);
    bool ajouter();
    bool supprimer(int);
    QSqlQueryModel* afficher();
    bool modifier();
    void clearTable(QTableView *table);
    void chercheID(QTableView *table, int ID_A);
    QSqlQueryModel * tri_ID_A();
    QSqlQueryModel * tri_NB_MOIS();
private:
    int ID_A;
    int nb_mois;
};

#endif // ABONNEMENT_H
