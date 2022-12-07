#ifndef GESTIONRESERVATION_H
#define GESTIONRESERVATION_H
#include <QWidget>
#include <QMainWindow>
#include <QDoubleValidator>
#include "reservation.h"
#include "mydb.h"
#include "book.h"
#include "cancel.h"
#include "arduino.h"

namespace Ui {
class gestionreservation;
}

class gestionreservation : public QWidget
{
    Q_OBJECT

public:
    explicit gestionreservation(QWidget *parent = nullptr);
    ~gestionreservation();
    void updateUI();
private slots:
    void on_pb_ajouter_clicked();

    void on_pb_Supprimer_clicked();

    void on_pb_Modifier_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pb_Quitter_clicked();

    void on_pB_TrierParCIN_clicked();

    void on_pb_TrierParNom_clicked();

    void on_pushButton_clicked();

    void on_pB_Recherche_clicked();

    void on_confirm_clicked();

    void on_btnBook_clicked();

    void on_btnCancel_clicked();

    void on_btnReset_clicked();

    void on_pB_ExPDF_clicked();

    void on_pB_ExPDF_2_clicked();

    void on_pB_Map_clicked();
    void update_RFID();

private:
    Ui::gestionreservation *ui;
    reservation R;
    book *ptrBook;
    cancel *ptrCancel;
    QByteArray data; // variable contenant les données reçues
    QString RFID="";

    Arduino A; // objet temporaire

};

#endif // GESTIONRESERVATION_H
