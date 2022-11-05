#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "employe.h"

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

private:
    Ui::MainWindow *ui;
    Employe Etmp;
};

#endif // MAINWINDOW_H
