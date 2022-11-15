#ifndef GESTION_DABONNEMENT_H
#define GESTION_DABONNEMENT_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
{
public:
    Connection();
    bool createconnect();
};

#endif // GESTION_DABONNEMENT_H
