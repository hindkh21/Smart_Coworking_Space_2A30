#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pb_emp_clicked();

    void on_pb_client_clicked();

    void on_pb_espace_clicked();

    void on_pb_ab_clicked();

    void on_pushButton_2_clicked();

    void on_motdepasseoublier_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_valid_2_clicked();

    void on_AJOUTER_4_clicked();

    void on_confnouv_clicked();

    void on_retouroublier_2_clicked();

    void on_retouroublier_clicked();

    void on_retouroublier_3_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_3_clicked();

    void on_pb_reserv_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
