#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        MainWindow w;
        connection c;
        bool test=c.CreateConnexion();
        if(test)
        {
            w.show();
            QMessageBox::information(nullptr, QObject::tr("DataBase is open"),
                        QObject::tr("Connection Successful."), QMessageBox::Close);

    }
        else
            QMessageBox::critical(nullptr, QObject::tr("DataBase in not open"),
                        QObject::tr("Connection Failed."), QMessageBox::Close);
        return a.exec();
}
