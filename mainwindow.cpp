#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include "todolist.h"
#include<QMessageBox>
#include <QDate>
#include<QComboBox>
#include<QRegExp>
#include<QTextEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_cin->setValidator(new QIntValidator(0,99999999, this));
    ui->tab_emp->setModel(Etmp.afficher());   
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
    bool valide=true;

    //Recuperation des donnees
    QString id=ui->le_id->text();
    int cin=ui->le_cin->text().toInt();
    float salaire=ui->le_salaire->text().toFloat();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString login=ui->le_login->text();
    QString pwd=ui->le_pwd->text();
    QString email=ui->le_email->text();
    QString profile=ui->cb_profile->currentText();
    QDate date=ui->dateEdit->date();


    //controle de saisie EMAIL
    /**************************/
    QRegExp Exp_mail ("^[\\w|\\.]+@[\\w]+\\.[\\w]{2,4}$");
    QRegExp Exp_nom ("^[A-Z]'?[- a-zA-Z]+$");
    QRegExp Exp_salaire ("([0-9]*[.])?[0-9]+");
    QRegExp Exp_login ("^[a-zA-Z0-9]+([._]?[a-zA-Z0-9]+)*$");
    QRegExp Exp_pwd ("^(?=.*[A-Za-z])(?=.*[0-9])[A-Za-z0-9]{8,}$");
    QRegExp Exp_id ("^[0-9]{3}[A-Z]{3}$");

    if (id.contains(Exp_id)==false)
    {
            QMessageBox::critical (this, "Validation", " ID n'est pas valide !");
            valide=false;
    }
    if (nom.contains(Exp_nom)==false)
    {
            QMessageBox::critical (this, "Validation", " NOM n'est pas valide !");
            valide=false;
    }
    if (prenom.contains(Exp_nom)==false)
    {
            QMessageBox::critical (this, "Validation", " ¨PRENOM n'est pas valide !");
            valide=false;
    }
    if (ui->le_salaire->text().contains(Exp_salaire)==false)
    {
            QMessageBox::critical (this, "Validation", " SALAIRE n'est pas valide !");
            valide=false;
    }
    if (email.contains(Exp_mail)==false)
    {
            QMessageBox::critical (this, "Validation", " EMAIL n'est pas valide !");
            valide=false;
    }
    if (login.contains(Exp_login)==false)
    {
            QMessageBox::critical (this, "Validation", " LOGIN n'est pas valide !");
            valide=false;
    }
    if (pwd.contains(Exp_pwd)==false)
    {
            QMessageBox::critical (this, "Validation", " PWD n'est pas valide !");
            valide=false;
    }

    /**************************/


    if(valide)
    {
    Employe E(id,nom,prenom,login,pwd,email,cin,salaire,profile,date);
    bool test=E.ajouter();

    if(test)
    {
        //refresh
        ui->tab_emp->setModel(E.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Ajout effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("Ajout NON effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

}

void MainWindow::on_pb_supprimer_clicked()
{
    QString id_emp=ui->le_id->text();
    bool test=Etmp.supprimer(id_emp);

    if(test)
    {
        //refresh
        ui->tab_emp->setModel(Etmp.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Suppresion effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("Suppresion NON effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pb_modifier_clicked()
{
    bool valide=true;

    //Recuperation des donnees
    QString id=ui->le_id->text();
    int cin=ui->le_cin->text().toInt();
    float salaire=ui->le_salaire->text().toFloat();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString login=ui->le_login->text();
    QString pwd=ui->le_pwd->text();
    QString email=ui->le_email->text();
    QString profile=ui->cb_profile->currentText();
    QDate date=ui->dateEdit->date();

    //controle de saisie EMAIL
    /****************************************************************************/
    QRegExp Exp_mail ("^[\\w|\\.]+@[\\w]+\\.[\\w]{2,4}$");
    QRegExp Exp_nom ("^[A-Z]'?[- a-zA-Z]+$");
    QRegExp Exp_salaire ("([0-9]*[.])?[0-9]+");
    QRegExp Exp_login ("^[a-zA-Z0-9]+([._]?[a-zA-Z0-9]+)*$");
    QRegExp Exp_pwd ("^(?=.*[A-Za-z])(?=.*[0-9])[A-Za-z0-9]{8,}$");
    QRegExp Exp_id ("^[0-9]{3}[A-Z]{3}$");

    if (id.contains(Exp_id)==false)
    {
            QMessageBox::critical (this, "Validation", " ID n'est pas valide !");
            valide=false;
    }
    if (nom.contains(Exp_nom)==false)
    {
            QMessageBox::critical (this, "Validation", " NOM n'est pas valide !");
            valide=false;
    }
    if (prenom.contains(Exp_nom)==false)
    {
            QMessageBox::critical (this, "Validation", " ¨PRENOM n'est pas valide !");
            valide=false;
    }
    if (ui->le_salaire->text().contains(Exp_salaire)==false)
    {
            QMessageBox::critical (this, "Validation", " SALAIRE n'est pas valide !");
            valide=false;
    }
    if (email.contains(Exp_mail)==false)
    {
            QMessageBox::critical (this, "Validation", " EMAIL n'est pas valide !");
            valide=false;
    }
    if (login.contains(Exp_login)==false)
    {
            QMessageBox::critical (this, "Validation", " LOGIN n'est pas valide !");
            valide=false;
    }
    if (pwd.contains(Exp_pwd)==false)
    {
            QMessageBox::critical (this, "Validation", " PWD n'est pas valide !");
            valide=false;
    }
    /****************************************************************************/

    if(valide)
    {
        Employe E(id,nom,prenom,login,pwd,email,cin,salaire,profile,date);

        bool test=E.modifier();

        if(test)
        {
            //refresh
            ui->tab_emp->setModel(E.afficher());

            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("edit effectué\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                        QObject::tr("edit NON effectué\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_tab_emp_activated(const QModelIndex &index)
{
       QString val=ui->tab_emp->model()->data(index).toString();
       QSqlQuery qry;
       Employe E;

       qry=E.select(val);

       if(qry.exec())
       {
           while (qry.next())
           {
               ui->le_id->setText(qry.value(0).toString());
               ui->le_nom->setText(qry.value(1).toString());
               ui->le_prenom->setText(qry.value(2).toString());
               ui->le_cin->setText(qry.value(3).toString());
               ui->le_login->setText(qry.value(4).toString());
               ui->le_pwd->setText(qry.value(5).toString());
               ui->le_email->setText(qry.value(6).toString());
               ui->le_salaire->setText(qry.value(7).toString());
               ui->cb_profile->setCurrentText(qry.value(8).toString());
               ui->dateEdit->setDate(qry.value(9).toDate());
           }
       }
}

void MainWindow::on_pb_recherche_clicked()
{
    QString rech=ui->le_recherche->text();
    if(rech!="")
    {
        QSqlQueryModel *tab_emp=Etmp.recherche(rech);
        if (tab_emp!=nullptr)
        {
            ui->tab_emp->setModel(tab_emp);
        }
    }
}


void MainWindow::on_pb_trierNom_clicked()
{
    QString critere=ui->cb_trie->currentText();
    if (critere=="nom")
        ui->tab_emp->setModel(Etmp.trier_nom());
    else
    {
        if (critere=="prenom")
        ui->tab_emp->setModel(Etmp.trier_prenom());
        else
            ui->tab_emp->setModel(Etmp.trier_salaire());
    }
}


void MainWindow::on_pb_refresh_clicked()
{
    ui->tab_emp->setModel(Etmp.afficher());
    ui->le_id->setText("");
    ui->le_nom->setText("");
    ui->le_prenom->setText("");
    ui->le_salaire->setText("");
    ui->le_cin->setText("");
    ui->le_email->setText("");
    ui->le_login->setText("");
    ui->le_pwd->setText("");
    ui->le_recherche->setText("");

}
/********************************************************ToDoList*********************************************************************/

void MainWindow::on_pb_afficherTache_clicked()
{
    QString id=ui->le_id_2->text();
    if(id!="")
    {
        QSqlQueryModel *tab_tache=Tmp.afficher(id);
        if (tab_tache!=nullptr)
        {
            ui->tab_tache->setModel(tab_tache);
        }
    }
}

void MainWindow::on_pb_ajoutTache_clicked()
{
    bool valide=true;

    //Recuperation des donnees
    QString id=ui->le_id_2->text();
    QString task=ui->des_tache->text();
    QString etat="A FAIRE";                 //PAR DEFAULT A FAIRE

    if(valide)
    {
    ToDoList T(id,task,etat);
    bool test=T.ajouter();

    if(test)
    {
        //REFRECH
        ui->tab_tache->setModel(Tmp.afficher(id));

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Ajout effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("Ajout NON effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_tab_tache_activated(const QModelIndex &index)
{
    QString val=ui->tab_tache->model()->data(index).toString();
    QSqlQuery qry;

    qry=Tmp.select(val);

    if(qry.exec())
    {
        while (qry.next())
        {
            ui->le_idTache->setText(qry.value(0).toString());
            ui->des_tache->setText(qry.value(2).toString());
        }
    }
}

void MainWindow::on_pb_suppTache_clicked()
{
    QString id_tache=ui->le_idTache->text();
    QString id=ui->le_id_2->text();

    bool test=Tmp.supprimer(id_tache);

    if(test)
    {
        //REFRECH
        ui->tab_tache->setModel(Tmp.afficher(id));

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("DELETE effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("DELETE NON effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pb_modifTache_clicked()
{
    bool valide=true;

    //Recuperation des donnees
    int id=ui->le_idTache->text().toInt();
    QString id_emp=ui->le_id_2->text();
    QString task=ui->des_tache->text();
    QString etat=ui->etat_tache->currentText();

    if(valide)
    {
        ToDoList T(id_emp,task,etat);

        bool test=T.modifier(id);
        if(test)
        {
            //REFRECH
            ui->tab_tache->setModel(Tmp.afficher(id_emp));

            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("EDIT effectué\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                        QObject::tr("EDIT NON effectué\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);


        }
}
