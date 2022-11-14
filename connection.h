#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>

//test

class Connection
{
    QSqlDatabase db;
public:
    Connection();
    bool createconnection();
    void closeconnection();

};

#endif // CONNECTION_H
