#include "employe.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QMessageBox>

Employe::Employe(){}

Employe::Employe(QString id_emp, QString nom_emp, QString prenom_emp,QString email_emp, QString login_emp, QString pwd_emp, int cin_emp,float salaire,QString profile_emp,QDate date_nais)
{
    this->id_emp=id_emp;
    this->nom_emp=nom_emp;
    this->prenom_emp=prenom_emp;
    this->cin_emp=cin_emp;
    this->salaire=salaire;
    this->email_emp=email_emp;
    this->login_emp=login_emp;
    this->pwd_emp=pwd_emp;
    this->profile_emp=profile_emp;
    this->date_nais=date_nais;
}

bool Employe::ajouter()
{
    QSqlQuery query;
    QString cin_s= QString::number(cin_emp);
    QString salaire_s= QString::number(salaire);

    query.prepare("insert into employe (id_emp, nom_emp, prenom_emp, cin_emp, salaire, email_emp, login_emp, pwd_emp, profile_emp, date_nais)" "values (:id_emp , :nom_emp ,:prenom_emp , :cin_emp, :salaire, :email_emp, :login_emp, :pwd_emp, :profile_emp, :date_nais)");
    query.bindValue(":id_emp",id_emp);
    query.bindValue(":nom_emp",nom_emp);
    query.bindValue(":prenom_emp",prenom_emp);
    query.bindValue(":cin_emp",cin_s);
    query.bindValue(":salaire",salaire_s);
    query.bindValue(":email_emp",email_emp);
    query.bindValue(":login_emp",login_emp);
    query.bindValue(":pwd_emp",pwd_emp);
    query.bindValue(":profile_emp",profile_emp);
    query.bindValue(":date_nais",date_nais);
    return query.exec();  //envoi du requete
}

QSqlQueryModel * Employe::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM employe");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("N°Carte Cin"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Login"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("pwd"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Profile"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Date de Naissance"));
    return model;
}

bool Employe::supprimer(QString id_emp)
{
    QSqlQuery query;
    query.prepare("Delete from employe where id_emp= :id_emp");
    query.bindValue(":id_emp",id_emp);
    return query.exec();
}

bool Employe::modifier()
{
    QSqlQuery query;
    QString cin_s= QString::number(cin_emp);
    QString salaire_s= QString::number(salaire);

    query.prepare("update employe set nom_emp= :nom_emp, prenom_emp= :prenom_emp, cin_emp= :cin_emp, salaire= :salaire, email_emp= :email_emp, login_emp= :login_emp, pwd_emp= :pwd_emp, profile_emp= :profile_emp, date_nais= :date_nais where id_emp= :id_emp" );
    query.bindValue(":id_emp",id_emp);
    query.bindValue(":nom_emp",nom_emp);
    query.bindValue(":prenom_emp",prenom_emp);
    query.bindValue(":cin_emp",cin_s);
    query.bindValue(":salaire",salaire_s);
    query.bindValue(":email_emp",email_emp);
    query.bindValue(":login_emp",login_emp);
    query.bindValue(":pwd_emp",pwd_emp);
    query.bindValue(":profile_emp",profile_emp);
    query.bindValue(":date_nais",date_nais);
    return  query.exec();
}

QSqlQuery Employe::select(QString val)
{
    QSqlQuery qry;
    qry.prepare("select * from employe where id_emp=?");
    qry.addBindValue(val);
    return qry;
}

QSqlQueryModel * Employe::recherche(QString rech)
{
   QSqlQuery *qry= new QSqlQuery();
   qry->prepare("select * from employe where nom_emp=:nom_emp or profile_emp=:profile_emp or prenom_emp=:prenom_emp or id_emp=:id_emp");
   qry->bindValue(":nom_emp",rech);
   qry->bindValue(":profile_emp",rech);
   qry->bindValue(":prenom_emp",rech);
   qry->bindValue(":id_emp",rech);
   qry->exec();
   QSqlQueryModel *model = new QSqlQueryModel();
       model->setQuery(*qry);

   return model;
}

/***********************************************************TRIE***************************************************************************/
QSqlQueryModel * Employe::trier_nom()  //ASC
    {
        QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM EMPLOYE ORDER BY NOM_EMP");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("N°Carte Cin"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Login"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("pwd"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("Salaire"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("Profile"));
        model->setHeaderData(9, Qt::Horizontal, QObject::tr("Date de Naissance"));
        return model;
    }

    QSqlQueryModel * Employe::trier_prenom()
    {
        QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM EMPLOYE ORDER BY PRENOM_EMP");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("N°Carte Cin"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Login"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("pwd"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("Salaire"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("Profile"));
        model->setHeaderData(9, Qt::Horizontal, QObject::tr("Date de Naissance"));
        return model;
    }

    QSqlQueryModel * Employe::trier_salaire()  //ASC
    {
        QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM EMPLOYE ORDER BY SALAIRE");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("N°Carte Cin"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Login"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("pwd"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("Salaire"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("Profile"));
        model->setHeaderData(9, Qt::Horizontal, QObject::tr("Date de Naissance"));
        return model;
    }



