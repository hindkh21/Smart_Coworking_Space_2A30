#ifndef gestion_abonnement_H
#define gestion_abonnement_H
#include "abonnement.h"
#include <QStandardItemModel>
#include "arduino.h"

#include <QMainWindow>
//7
namespace Ui {
class gestion_abonnement;
}

class gestion_abonnement : public QMainWindow
{
    Q_OBJECT

public:
    explicit gestion_abonnement(QWidget *parent = nullptr);
    ~gestion_abonnement();

private slots:

    void on_AJOUTER_2_clicked();

    void on_supp_clicked();

    void on_checkBox_2_clicked();

    void on_pushButton_valid_2_clicked();

    void on_B_GestionIntervenant_clicked();

    void on_pushButton_2_clicked();

    void on_supp_2_clicked();

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

    void on_checkBox_3_clicked();
    void update_label();
    void on_AJOUTER_5_clicked();

    void on_retouroublier_3_clicked();

private:
    Ui::gestion_abonnement *ui;
    abonnement f;
    QByteArray data;
    Arduino a;

};

#endif // gestion_abonnement_H
