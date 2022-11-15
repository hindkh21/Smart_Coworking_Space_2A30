#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPrinter>
#include "employe.h"
#include "todolist.h"
#include "statistiques.h"

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

private:
    Ui::MainWindow *ui;
    Employe Etmp;
    ToDoList Tmp;
    statistiques *s;
};

#endif // MAINWINDOW_H
