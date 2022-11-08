#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include <QObject>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void chart();
    ~MainWindow();
    void mailSent(QString status);
std::string encode(std::string url);
private slots:


    void on_pushButton_3_clicked();


    void on_pushButton_5_clicked();

    void on_pushButton_9_clicked();


    void on_lineEdit_textChanged(const QString &arg1);



    void on_pushButton_7_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();


    //void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
    QStringList files;
    Client C;
};
#endif // MAINWINDOW_H
