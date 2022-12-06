#ifndef GESTIONESPACE_H
#define GESTIONESPACE_H
#include "espaces.h"
#include <QRegExpValidator>
#include <QSql>
#include <QSqlDatabase>
#include <QFileInfo>
#include <QDebug>
#include <QPushButton>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "arduino.h"
#include <QWidget>

namespace Ui {
class gestionEspace;
}

class gestionEspace : public QWidget
{
    Q_OBJECT

public:
    explicit gestionEspace(QWidget *parent = nullptr);
    ~gestionEspace();

    double m_BotD, m_TopD;
    QRegExpValidator *m_pValid;

private slots:
    void on_ajouter_pb_clicked();

    void on_supr_pb_clicked();


    void on_modif_pb_clicked();

    void on_tri_pb_clicked();

    void on_PDF_pb_clicked();

    void on_chercher_pb_clicked();


    QString on_upload_pb_clicked();


    void on_Descr_pb_clicked();

    void on_Facture_pb_clicked();

    float calculer();

    void on_Excel_pb_clicked();

    void update_label(); //slot permettant la màj de l etat de ... , il est lancé a chaque reception dun msg de arduino

    void on_tableView_espace_activated(const QModelIndex &index);

    void m_a_j_stat();


private:
    Ui::gestionEspace *ui;
    Espaces ES;
    QByteArray data; //variable contenant les donnees recues
    Arduino A; //objet temporaire
};

#endif // GESTIONESPACE_H
