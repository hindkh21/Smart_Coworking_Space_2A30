#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "abonnement.h"
#include <QStandardItemModel>
#include "arduino.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_AJOUTER_2_clicked();

    void on_supp_clicked();

    void on_checkBox_2_clicked();

    void on_pushButton_valid_2_clicked();

    void on_B_GestionIntervenant_clicked();

    void on_B_GestioAffaire_clicked();

    void on_B_GestioAffaire_3_clicked();

    void on_B_BackToMenu_clicked();

    void on_B_BackToMenu_2_clicked();

    void on_B_BackToMenu_3_clicked();

    void on_pushButton_2_clicked();

    void on_supp_2_clicked();

    void on_B_GestioAffaire_4_clicked();

    void on_B_BackToMenu_4_clicked();

    void on_B_BackToMenu_5_clicked();

    void on_B_GestionIntervenant_2_clicked();

    void on_pushButton_3_clicked();

    void on_supp_4_clicked();

    void on_supp_3_clicked();

    void on_supp_6_clicked();

    void on_supp_5_clicked();

    void on_supp_7_clicked();

    void on_supp_8_clicked();

    void on_supp_9_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_AJOUTER_3_clicked();

    void on_motdepasseoublier_clicked();

    void on_retouroublier_clicked();

    void on_AJOUTER_4_clicked();

    void on_retouroublier_2_clicked();

    void on_confnouv_clicked();

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_3_clicked();
    void update_label();
    void on_AJOUTER_5_clicked();

    void on_retouroublier_3_clicked();

private:
    Ui::MainWindow *ui;
    abonnement f;
    QByteArray data;
    arduino a;

};

#endif // MAINWINDOW_H
