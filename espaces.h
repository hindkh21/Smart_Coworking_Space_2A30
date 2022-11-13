#ifndef ESPACES_H
#define ESPACES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QPixmap>
class Espaces
{
    QString ID_ES,categorie,description,disponibilite;
    QString image;
    int nb_places;
    float superficie,tarif;

public:
    //constructeurs
    Espaces();
    Espaces(QString,QString,QString,int,float,float,QString,QString);
    Espaces(QString,float,QString);

    //getters
    QString getID(){return ID_ES;}
    QString getCategorie(){return categorie;}
    QString getDescription(){return description;}
    float getSuperficie(){return superficie;}
    float getTarif(){return tarif;}
    int getNbDePlaces(){return nb_places;}
    QString getDisponibilite(){return disponibilite;}
    QString getImage(){return image;}

    //setters
    void setID(QString n1){ID_ES=n1;}
    void setCategorie(QString n2){categorie=n2;}
    void setDescription(QString n3){description=n3;}
    void setSuperficie(float n4){superficie=n4;}
    void setTarif(float n5){tarif=n5;}
    void setNbDePlaces(int n6){nb_places=n6;}
    void setDisponibilite(QString n7){disponibilite=n7;}
    void setImage(QString n8){image=n8;}

    //fonctionnalités de base relatives a l'entité etudiant
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString ID_ES);
    bool modifier();
    QSqlQueryModel * tri_espaces();
    QSqlQueryModel * chercher(QString cher);
    QSqlQuery select(QString val);
    float calculer();

};

#endif // ESPACES_H
