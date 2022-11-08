#include"client.h"
#include <QObject>
Client::Client()
{
id=0;
prenom="";
nom="";
num_tel=0;
email="";
type="";
}
Client::Client(int id,QString nom,QString prenom,int num_tel,QString email,QString type)
{   this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->email=email;
    this->num_tel=num_tel;
    this->type=type;
}

bool Client::ajouter()
{

    QSqlQuery query;
    QString id_string=QString::number(id);
    QString num_tel_string=QString::number(num_tel);
    query.prepare("INSERT INTO CLIENT(ID_CLIENT,NOM_CL,PRENOM_CL,NUM_TEL,EMAIL_CL,TYPE)"
                  "VALUES(:id,:nom,:prenom,:num_tel,:email,:type)");
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":email",email);
    query.bindValue(":num_tel",num_tel);
    query.bindValue(":type",type);
    return query.exec();
}


QSqlQueryModel * Client::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from CLIENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CLIENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM_CL"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM_CL"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL_CL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUM_TEL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TYPE"));


    return model;
}
QSqlQueryModel * Client::afficher1()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT ORDER BY TYPE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CLIENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM_CL"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM_CL"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL_CL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUM_TEL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TYPE"));



    return model;
}
bool Client::supprimer(QString nom)
{
    QSqlQuery query;
    query.prepare("Delete from CLIENT where NOM_CL =:nom");
    query.bindValue(":nom",nom);
    return query.exec();
}
int Client::getid(){return id;}
QString Client::getnom(){return nom;}
QString Client::getprenom(){return prenom;}
int Client::getnumtel(){return num_tel;}
QString Client::getemail(){return email;}
QString Client::gettype(){return type;}
void Client::setid(int id){this->id=id;}
void Client::setprenom(QString prenom){this->prenom=prenom;}
void Client::setnom(QString nom){this->nom=nom;}
void Client::setnumtel(int num_tel){this->num_tel=num_tel;}
void Client::setemail(QString email){this->email=email;}
void Client::settype(QString type){this->type=type;}


bool Client::modifier(int id )
{

    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET   PRENOM_CL= :prenom ,NOM_CL = :nom  ,NUM_TEL = :num_tel, EMAIL_CL = :email ,TYPE = :type WHERE ID_CLIENT = :id");
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":num_tel",num_tel);
    query.bindValue(":email",email);
    query.bindValue(":type",type);
    if(!query.exec())
       qDebug() << query.lastError();
          return query.exec();
}

 QSqlQueryModel * Client::recherche(QString nom,QString prenom,QString type)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT WHERE NOM_CL LIKE '%"+nom+"%' OR PRENOM_CL LIKE '%"+prenom+"%' OR TYPE LIKE '%"+type+"%'");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CLIENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM_CL"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM_CL"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL_CL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUM_TEL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TYPE"));
    return  model;


}
 int Client::calcul_type_stat(QString t)
 {
     QSqlQuery query;
     query.prepare("SELECT TYPE FROM CLIENT WHERE TYPE = '"+t+"'");
     query.exec();
     int size=0;


     while(query.next())
        size++;

     return size;

 }

void Client::getDatabaseValue(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT WHERE ID_CLIENT = '"+QString::number(id)+"'");
    query.exec();
    query.next();
    this->id = query.value(0).toInt();
    prenom = query.value(1).toString();
    nom = query.value(2).toString();
    email = query.value(3).toString();
    num_tel=query.value(4).toInt();
    type=query.value(5).toString();

}



