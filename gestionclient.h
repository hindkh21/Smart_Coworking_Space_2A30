#ifndef GESTIONCLIENT_H
#define GESTIONCLIENT_H

#include <QMainWindow>
#include "client.h"
#include <QObject>
#include "arduinoEmp.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class gestionClient;
}
QT_END_NAMESPACE
class gestionClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit gestionClient(QWidget *parent = nullptr);
    ~gestionClient();

    void chart();
    void mailSent(QString status);
    std::string encode(std::string url);

private slots:
   // void on_pushButton_3_clicked();
    //void on_pushButton_5_clicked();
    //void on_pushButton_9_clicked();
    //void on_lineEdit_textChanged(const QString &arg1);
    //void on_pushButton_7_clicked();
    //void on_pushButton_2_clicked();
    //void on_pushButton_clicked();
    //void on_pushButton_4_clicked();
    //void on_pushButton_6_clicked();
    //void on_pushButton_8_clicked();
    void update_label();
    void on_pushButton_11_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_39_clicked();

    void on_pushButton_36_clicked();

    //void on_lineEdit_4_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_41_clicked();

   void on_pushButton_40_clicked();

    void on_pushButton_38_clicked();

    void on_pushButton_42_clicked();

    void on_pushButton_43_clicked();

    //void on_label_40_linkActivated(const QString &link);

    void on_lineEdit_4_textChanged(const QString &arg1);

private:
    Ui::gestionClient *ui;
    QStringList files;
    Client C;
    QByteArray data; // variable contenant les données reçues
    //Commandes com;
    Arduino A; // objet temporaire
};

#endif // GESTIONCLIENT_H

