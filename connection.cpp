#include "connection.h"

Connection::Connection(){}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("MIMI");
db.setUserName("rayou");//inserer nom de l'utilisateur
db.setPassword("raya");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}

void Connection::closeConnection() { db.close();}
