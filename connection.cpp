#include "connection.h"

connection::connection(){}
bool connection::CreateConnexion()
{
    bool test=false;
        db = QSqlDatabase::addDatabase("QODBC");
        db.setDatabaseName("test_bd");
        db.setUserName("mimi");//inserer nom de l'utilisateur
        db.setPassword("malek");//inserer mot de passe de cet utilisateur

        if (db.open())
            test=true;

        return  test;
}

void connection::FermerConnexion(){db.close();}

bool connection::OuvrirConnexion(){
    if (db.open())
        return true ;
    else
        return false;

}
