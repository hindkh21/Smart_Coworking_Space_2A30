#ifndef GESTIONEMPLOYE_H
#define GESTIONEMPLOYE_H
#include <QMainWindow>
#include <QPrinter>
#include "employe.h"
#include "todolist.h"
#include "statemp.h"
#include "arduinoEmp.h"

namespace Ui {
class GestionEmploye;
}

class GestionEmploye : public QMainWindow
{
    Q_OBJECT

public:
    explicit GestionEmploye(QWidget *parent = nullptr);
    ~GestionEmploye();

private slots:
    void on_pb_ajouter_clicked();
    void on_pb_supprimer_clicked();
    void on_pb_modifier_clicked();
    void on_tab_emp_activated(const QModelIndex &index);
    void on_pb_recherche_clicked();
    void on_pb_refresh_clicked();
    void on_pb_ajoutTache_clicked();
    void on_pb_afficherTache_clicked();
    void on_tab_tache_activated(const QModelIndex &index);
    void on_pb_suppTache_clicked();
    void on_pb_modifTache_clicked();
    void on_pb_trierNom_clicked();
    void on_pb_stat_clicked();
    void on_pb_stat_2_clicked();
    void on_pb_pdf_clicked();
    void on_pb_afficherDrct_clicked();
    void on_pb_refresh_2_clicked();
    void on_pb_fitre_clicked();
    void on_pb_arduino_clicked();

private:
    Ui::GestionEmploye *ui;
    Employe Etmp;
    ToDoList Tmp;
    statEmp *s;
    QByteArray data;
    Arduino A;
};

#endif // GESTIONEMPLOYE_H


