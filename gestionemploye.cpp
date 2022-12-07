#include "gestionemploye.h"
#include "ui_gestionemploye.h"
#include "employe.h"
#include "todolist.h"
#include "statemp.h"
#include "mychat_employe.h"
#include<QMessageBox>
#include <QDate>
#include<QComboBox>
#include<QRegExp>
#include<QTextEdit>
#include<QtCharts>

GestionEmploye::GestionEmploye(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GestionEmploye)
{
    ui->setupUi(this);

    ui->le_cin->setValidator(new QIntValidator(0,99999999, this));
    ui->tab_emp->setModel(Etmp.afficher());

    ui->groupBox_3->hide();
    ui->groupBox->hide();
    ui->gb_delet->hide();

    /******************************ARDUINO********************************/
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
}

GestionEmploye::~GestionEmploye()
{
    delete ui;
}

/*void GestionEmploye::update_label()
{
    data=A.read_from_arduino();
    qDebug() << data;
    QSqlQuery query;
    QString msg;

    if(data=="1")
     {
        QString id="A3 B3 15 9B";
         msg= A.select(id);
         ui->label_40->setText(msg);
      }
    if(data=="2")
    {
       QString id = "C2 C7 BC 1B";
        msg= A.select("13 74 5E A7");
        ui->label_40->setText(msg);
    }
    if(data=="0")
        ui->label_40->setText("refusé");

    for (int i=0; i < msg.length(); i++)
      {
        QString c = msg.at(i);
        QByteArray m= c.toUtf8();
        A.write_to_arduino(m);
      }
}*/

void GestionEmploye::update_label()
{

    data=A.read_from_arduino();
    qDebug() << data;
    QSqlQuery query;

    if(data=="1")
          {

            qDebug() << query.exec("select NOM_EMP from EMPLOYE where ID_CARD='83 6C DF 91'");
        query.first();
            ui->label_40->setText("Bonjour "+query.value(0).toString());// si les données reçues de arduino via la liaison série sont égales à 1

            }
    if(data=="2")
    {
        qDebug() << query.exec("select NOM_EMP from EMPLOYE where ID_CARD='13 74 5E A7'");
        query.first();
        ui->label_40->setText("Bonjour "+query.value(0).toString());// si les données reçues de arduino via la liaison série sont égales à 1
    }
    if(data=="0")
        ui->label_40->setText("refusé");   // si les données reçues de arduino via la liaison série sont égales à 0

    QString msg= query.value(0).toString();
    for (int i=0; i < msg.length(); i++)
      {
        QString c = msg.at(i);
        QByteArray m= c.toUtf8();
        A.write_to_arduino(m);
      }
}



void GestionEmploye::on_pb_ajouter_clicked()
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

void GestionEmploye::on_pb_supprimer_clicked()
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

void GestionEmploye::on_pb_modifier_clicked()
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

void GestionEmploye::on_tab_emp_activated(const QModelIndex &index)
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

void GestionEmploye::on_pb_recherche_clicked()
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


void GestionEmploye::on_pb_trierNom_clicked()
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

void GestionEmploye::on_pb_refresh_clicked()
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

void GestionEmploye::on_pb_afficherTache_clicked()
{
    QString id=ui->le_id_2->text();
    QString profile=ui->le_profileEmp->text();

    if(id!="")
    {
       QString profile=Tmp.verification(id);
       ui->le_profileEmp->setText(profile);

       if (profile == "Directeur")
       {
            ui->groupBox_3->show();
            ui->groupBox->show();
            ui->gb_delet->show();
       }
       else
       {
           ui->groupBox_3->hide();
           ui->groupBox->hide();
           ui->gb_delet->hide();
           QSqlQueryModel *tab_tache=Tmp.afficher(id);
           if (tab_tache!=nullptr)
           {
               ui->tab_tache->setModel(tab_tache);
           }
       }
    }
}

void GestionEmploye::on_pb_afficherDrct_clicked()
{
     QString id = ui->le_idEmp->text();
     QSqlQueryModel *tab_tache=Tmp.afficher(id);
     if (tab_tache!=nullptr)
     {
         ui->tab_tache->setModel(tab_tache);
     }
}

void GestionEmploye::on_pb_ajoutTache_clicked()
{
    bool valide=true;

    //Recuperation des donnees
    QString id=ui->le_idEmp->text();
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

void GestionEmploye::on_tab_tache_activated(const QModelIndex &index)
{
    QString val=ui->tab_tache->model()->data(index).toString();
    QSqlQuery qry;

    qry=Tmp.select(val);

    if(qry.exec())
    {
        while (qry.next())
        {
            ui->le_idTache->setText(qry.value(0).toString());
            ui->des_tache->setText(qry.value(1).toString());
            ui->etat_tache->setCurrentText(qry.value(2).toString());
        }
    }
}

void GestionEmploye::on_pb_suppTache_clicked()
{
    QString id_tache=ui->le_idTache->text();
    QString id=ui->le_idEmp->text();

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

void GestionEmploye::on_pb_modifTache_clicked()
{
    bool valide=true;

    //Recuperation des donnees
    int id=ui->le_idTache->text().toInt();

    QString id_emp=ui->le_id_2->text();
    QString idE=ui->le_idEmp->text();
    QString task=ui->des_tache->text();
    QString etat=ui->etat_tache->currentText();
    QString profile=ui->le_profileEmp->text();

    if(valide)
    {
        ToDoList T(id_emp,task,etat);
        bool test=T.modifier(id);
        if(test)
        {
            //REFRECH
            if (profile == "Directeur")
                ui->tab_tache->setModel(Tmp.afficher(idE));
            else
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

void GestionEmploye::on_pb_stat_clicked()
{
    s = new statEmp();
    s->setWindowTitle("PRODUCTIVITE en fonction des taches effectuées");
    s->choix_pie();
    s->show();
}

void GestionEmploye::on_pb_stat_2_clicked()       /******************** CHATBOX EMPLOYE ***************************/
{
    MyChat_employe *chat;
    chat = new MyChat_employe();
    chat->setFixedSize(680,500);
    chat->show();
}

void GestionEmploye::on_pb_pdf_clicked()         /********************* PDF **************************************/
{
    QString strStream;
    QTextStream out(&strStream);
    const int rowCount = ui->tab_emp->model()->rowCount();
    const int columnCount =ui->tab_emp->model()->columnCount();


                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("eleve")
                        <<  "</head>\n"
                        "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                            "<h1>Coordonnees des employeurs</h1>"

                            "<table border=1 cellspacing=0 cellpadding=2>\n";

                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tab_emp->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tab_emp->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tab_emp->isColumnHidden(column)) {
                                   QString data = ui->tab_emp->model()->data(ui->tab_emp->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";

        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);

        //QTextDocument document;
        //document.setHtml(html);
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("Coordonnees_employeurs.pdf");
        document->print(&printer);
}


void GestionEmploye::on_pb_refresh_2_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    ui->tab_tache->setModel(model);
    ui->le_id_2->setText("");
    ui->le_profileEmp->setText("");
    ui->le_idEmp->setText("");
    ui->le_idTache->setText("");
    ui->des_tache->setText("");
    ui->etat_tache->setCurrentText("A FAIRE");
    ui->groupBox_3->hide();
    ui->groupBox->hide();
}

void GestionEmploye::on_pb_fitre_clicked()
{
    QString critere=ui->cb_etat->currentText();
    QString profile=ui->le_profileEmp->text();
    QString id=ui->le_id_2->text();

      if (profile == "Directeur")
            id=ui->le_idEmp->text();


    ui->tab_tache->setModel(Tmp.afficher(id));

    if (critere=="A FAIRE")
        ui->tab_tache->setModel(Tmp.filtre("A FAIRE",id));
    else
    {
        if (critere=="EN COURS")
        ui->tab_tache->setModel(Tmp.filtre("EN COURS",id));
        else
        {
            if (critere=="FAIT")
            ui->tab_tache->setModel(Tmp.filtre("FAIT",id));
        }
    }
}

