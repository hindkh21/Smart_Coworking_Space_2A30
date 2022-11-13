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


    void on_upload_pb_clicked();

    void on_pushButton_2_clicked();


    void on_Descr_pb_clicked();

    void on_Facture_pb_clicked();

    float calculer();

private:
    Ui::MainWindow *ui;
    Espaces ES;
};
#endif // MAINWINDOW_H
