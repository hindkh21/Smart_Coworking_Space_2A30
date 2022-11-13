#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnection()
{
    db=QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("MIMI");
    db.setUserName("rayou");
    db.setPassword("raya");
    if(db.open())
        test=true;
   return test;
}

void Connection::closeconnection()
{
    db.close();
}
