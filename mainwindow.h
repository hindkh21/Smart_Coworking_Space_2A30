#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "espaces.h"
#include <QMainWindow>
#include <QRegExpValidator>
#include <QSql>
#include <QSqlDatabase>
#include <QFileInfo>
#include <QDebug>
#include <QPushButton>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    Ui::MainWindow *ui;
    Espaces ES;
    QByteArray data; //variable contenant les donnees recues
    Arduino A; //objet temporaire
};
#endif // MAINWINDOW_H
