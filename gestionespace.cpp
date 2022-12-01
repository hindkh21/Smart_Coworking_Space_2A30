#include "gestionespace.h"
#include "ui_gestionespace.h"
#include "espaces.h"
#include "exportexcelobject.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QRegExp>
#include <QString>
#include <QTextStream>
#include <QTextDocument>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QPixmap>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QPainter>

gestionEspace::gestionEspace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gestionEspace)
{
    ui->setupUi(this);

    //Controle de saisie pour le tarif et superficie(chiffres seulement)
    m_BotD = 1.0;
    m_TopD = 300.0;
    QDoubleValidator* SValid(new QDoubleValidator(m_BotD, m_TopD, 2, this));
    ui->le_tarif_espace->setValidator(SValid);
    QDoubleValidator* TValid(new QDoubleValidator(m_BotD, m_TopD, 2, this));
    ui->le_supr_espace->setValidator(TValid);

    //affichage du tableau
    ui->tableView_espace->setModel(ES.afficher());

    //generer le contenu des combobox
    const int rowCount = ui->tableView_espace->model()->rowCount();
     for (int row = 0; row < rowCount; row++)
     {
         if (!ui->tableView_espace->isColumnHidden(0)) {
         ui->select_esp->addItem(ui->tableView_espace->model()->data(ui->tableView_espace->model()->index(row, 0)).toString().simplified());
         ui->ComboBox_Descr->addItem(ui->tableView_espace->model()->data(ui->tableView_espace->model()->index(row, 0)).toString().simplified());
     }
     }

     //Connexion arduino
      int ret=A.connect_arduino(); // lancer la connexion à arduino
      switch(ret){
      case (0): qDebug()<< "arduino is available and connected to : " << A.getarduino_port_name ();
      break;
      case (1):qDebug() << "arduino is available but not connected to :" << A.getarduino_port_name();
      break;
      case (-1):qDebug() << "arduino is not available"; }
      QObject::connect(A.getserial(),SIGNAL(readyRead()),this, SLOT(update_label())); //permet de lancer le slot update_label suite à la reception du signal readyRead (reception des données).

      m_a_j_stat(); //mise à jour des statistiques

}

gestionEspace::~gestionEspace()
{
    delete ui;
}

void gestionEspace::on_ajouter_pb_clicked()
{
    QString image=on_upload_pb_clicked();
    QString categorie;
    QString ID_ES=ui->le_id_espace->text();
    if(ui->radioButton_espace->isChecked())
        categorie="Coworking Space";
    if(ui->radioButton_2_espace->isChecked())
        categorie="Bureau Privatif";
    if(ui->radioButton_3_espace->isChecked())
        categorie="Salle de Reunion";
    if(ui->radioButton_4_espace->isChecked())
        categorie="Salle de Conference";
    QString description=ui->le_descr_espace->text();
    float superficie=ui->le_supr_espace->text().toFloat();

    float tarif=ui->le_tarif_espace->text().toFloat();
    int nb_places=ui->spinBox_nbplaces->value();
    QString disponibilite=ui->comboBox_espace->currentText();


    Espaces ES(ID_ES,categorie,description,nb_places,superficie,tarif,disponibilite,image);

    bool test=ES.ajouter();
    if(test)
    {
        ui->tableView_espace->setModel(ES.afficher());
        m_a_j_stat();
        QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("ajout effectué\n" "Click cancel to exit\n"),QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),QObject::tr("ajout non effectué\n" "Click cancel to exit\n"),QMessageBox::Cancel);
}



void gestionEspace::on_supr_pb_clicked()
{
    Espaces ES;
    ES.setID(ui->le_id_espace->text());
    bool test=ES.supprimer(ES.getID());
    if(test)
    {
        ui->tableView_espace->setModel(ES.afficher());
        m_a_j_stat();
        QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Suppression avec succes\n" "Click cancel to exit\n"),QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),QObject::tr("Echec de suppression\n" "Click cancel to exit\n"),QMessageBox::Cancel);
}

void gestionEspace::on_tableView_espace_activated(const QModelIndex &index)
{
    QString val=ui->tableView_espace->model()->data(index).toString();
    QSqlQuery qry;
    Espaces ES1;
    qry=ES1.select(val);
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->le_id_espace->setText(qry.value(0).toString());
            if(qry.value(1)=="Coworking Space")
               ui->radioButton_espace->setChecked(true);
            if(qry.value(1)=="Bureau Privatif")
                ui->radioButton_2_espace->setChecked(true);
            if(qry.value(1)=="Salle de Réunion")
                ui->radioButton_3_espace->setChecked(true);
            if(qry.value(1)=="Salle de Conference")
                ui->radioButton_4_espace->setChecked(true);
            ui->le_descr_espace->setText(qry.value(2).toString());
            ui->le_supr_espace->setText(qry.value(4).toString());
            ui->le_tarif_espace->setText(qry.value(5).toString());
            ui->spinBox_nbplaces->setValue(qry.value(3).toInt());
            if(qry.value(6)=="Oui")
                ui->comboBox_espace->setEditText("Oui");
            if(qry.value(6)=="Non")
                ui->comboBox_espace->setEditText("Non");
        }
    }
}

void gestionEspace::on_modif_pb_clicked()
{
    QString categorie;
    QString ID_ES=ui->le_id_espace->text();
    if(ui->radioButton_espace->isChecked())
        categorie="Coworking Space";
    if(ui->radioButton_2_espace->isChecked())
        categorie="Bureau Privatif";
    if(ui->radioButton_3_espace->isChecked())
        categorie="Salle de Réunion";
    if(ui->radioButton_4_espace->isChecked())
        categorie="Salle de Conference";
    QString description=ui->le_descr_espace->text();
    float superficie=ui->le_supr_espace->text().toFloat();
    float tarif=ui->le_tarif_espace->text().toFloat();
    int nb_places=ui->spinBox_nbplaces->value();
    QString disponibilite=ui->comboBox_espace->currentText();
    QString image=on_upload_pb_clicked();;

    Espaces ES(ID_ES,categorie,description,nb_places,superficie,tarif,disponibilite,image);
    bool test=ES.modifier();
       if(test)
       {
           ui->tableView_espace->setModel(ES.afficher());
           m_a_j_stat();
           QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Modification avec succes\n" "Click cancel to exit\n"),QMessageBox::Cancel);
       }
           else
            QMessageBox::critical(nullptr,QObject::tr("NOT OK"),QObject::tr("Echec de modification\n" "Click cancel to exit\n"),QMessageBox::Cancel);
}


void gestionEspace::on_tri_pb_clicked()
{
        Espaces ES;;
        ES.tri_espaces() ;
        ui->tableView_espace->setModel(ES.tri_espaces());

}

void gestionEspace::on_PDF_pb_clicked()
{
    QPdfWriter pdf("C:/Users/abdel/OneDrive/Documents/Gestion_Espaces/Liste.pdf");

                         QPainter painter(&pdf);

                         int i = 2500;

                         painter.setPen(Qt::red);
                         painter.setFont(QFont("Arial",15));
                         painter.drawText(4000,1000,"LISTE DES ESPACES");

                         painter.drawRect(0,1700,9600,500);
                         painter.setPen(Qt::black);
                         painter.setFont(QFont("Arial", 9));
                         painter.drawText(200,2000,"ID_ES");
                         painter.drawText(1800,2000,"CATEGORIE");
                         painter.drawText(3500,2000,"DESCRIPTION");
                         painter.drawText(5500,2000,"NB_PLACES");
                         painter.drawText(6500,2000,"SUPERFICIE");
                         painter.drawText(7500,2000,"TARIF");
                         painter.drawText(8200,2000,"DISPONIBILITE");

                         QSqlQuery query;
                         query.prepare("select * from Espaces");
                         query.exec();
                         while (query.next())
                         {
                             painter.drawText(200,i,query.value(0).toString());
                             painter.drawText(1800,i,query.value(1).toString());
                             painter.drawText(3500,i,query.value(2).toString());
                             painter.drawText(5500,i,query.value(3).toString());
                             painter.drawText(6500,i,query.value(4).toString());
                             painter.drawText(7500,i,query.value(5).toString());
                             painter.drawText(8200,i,query.value(6).toString());

                             i = i +500;
                         }

                         int answer = QMessageBox::question(this, "PDF généré avec succes", "Voulez vous afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                         if (answer == QMessageBox::Yes)
                         {
                             QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/abdel/OneDrive/Documents/Gestion_Espaces/Liste.pdf"));

                             painter.end();
                         }
                         if (answer == QMessageBox::No)
                         {
                             painter.end();
                         }



}


void gestionEspace::on_chercher_pb_clicked()
{
    Espaces ES ;
       QString cher =ui->chercher_line_2->text();
       ui->tableView_espace->setModel(ES.chercher(cher));
}



QString gestionEspace::on_upload_pb_clicked()
{
    Espaces ES;
    QString filename=QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.png *.jpg *.jpeg *.bmp)"));

    if(QString::compare(filename, QString())!=0)
     {
        QImage image;
        bool valid=image.load(filename);

        if(valid)
        {
            image=image.scaledToWidth(ui->lbl_image->width(), Qt::SmoothTransformation);
            ui->lbl_image->setPixmap(QPixmap::fromImage(image));

        }

        else
           {
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),QObject::tr("Echec importation d'image\n" "Click cancel to exit\n"),QMessageBox::Cancel);
        }
     }
return filename;
}




void gestionEspace::on_Descr_pb_clicked()
{

    QPdfWriter pdf("C:/Users/abdel/OneDrive/Documents/Gestion_Espaces/Description.pdf");

                         QPainter painter(&pdf);

                         int i = 2500;

                         painter.setPen(Qt::red);
                          painter.setFont(QFont("Arial",15 , 15 , true));
                         painter.drawText(2300,1000,"DESCRIPTION DE L'ESPACE:");



                         painter.setPen(Qt::black);
                         painter.setFont(QFont("Arial", 9));

                         QString des;
                         QString des2;
                         QString des3;
                         QString s="Superficie:";
                         QString t="Tarif(journée):";
                         QString n="Nombre de places:";
                         QString val=ui->ComboBox_Descr->currentText();
                         QSqlQuery qry;
                         Espaces ES1;
                         qry=ES1.select(val);

                         if(qry.exec())
                         {
                         while (qry.next())
                         {
                             if(qry.value(1)=="Salle de Reunion")
                                {

                                 des="Équipée d’un écran de projection, un système de visioconférence, d’un tableau blanc et d’un flip chart.\n";
                                 des2="Cette salle est idéale pour accueillir, que ce soit une personne pour un conf-call, ou toute une équipe pour le brainstorming.\n";
                                 des3="Aussi, si vous avez des clients à rencontrer ou une présentation à faire, ce bureau privé est l’espace idéale pour vous.\n";

                                 }
                             if(qry.value(1)=="Bureau Privatif")
                               {
                                  des="Que ce soit pour une personne ou pour toute une équipe, nos bureaux privés et privatifs vous permettent d’avoir un espace de travail calme, tout en ayant accès à toutes les commodités du coworking space.\n";
                                  des2 ="Nos prix sont parfaitement étudiés pour vous permettre de faire des économies par rapport à l’une des plus grandes charges de la société, et bien sûr, vous n’aurez aucune caution à payer.\n";
                                  des3="Bien sûr, vous aurez un accès en 24/7 et tout est inclus dans nos tarifs et vous n’aurez aucune autre charge cachée à payer.\n";

                             }
                             if(qry.value(1)=="Coworking Space")
                              {
                                 des="L’open space de notre coworking est un espace de travail partagé parfaitement équipé.\n";
                                 des2="Il a été pensé pour permettre à nos coworkers d’avoir accès à toutes les commodités et ainsi leurs permettre de se focaliser sur ce qui est important.\n";
                                 des3="Notre espace peut ainsi offrir la possibilité d’accueillir des formations et des ateliers et ainsi créer un esprit de partage entre nos membres.\n";

                                }
                             if(qry.value(1)=="Salle de Conference")
                             {
                                 des="C'est un lieu qui permet d’accueillir des événements spécifiques tels que des réunions professionnelles, des séminaires, des formations ou le lancement d’une nouvelle marque développée.\n";
                                 des2="Invitez vos participants et profitez d’un lieu qui vous accueillera dans les meilleures conditions possibles.\n";
                                 des3=" ";
                             }

                             painter.drawText(200,i,des);
                             painter.drawText(200,i+200,des2);
                             painter.drawText(200,i+400,des3);
                             painter.drawText(200,i+1000,s);
                             painter.drawText(1000,i+1000,qry.value(4).toString());
                             painter.drawText(200,i+1500,n);
                             painter.drawText(1500,i+1500,qry.value(3).toString());
                             painter.drawText(200,i+2000,t);
                             painter.drawText(1300,i+2000,qry.value(5).toString());
                             QString filename=qry.value(7).toString();
                             painter.drawImage(QRect(1800,5000,4000,4000), QImage(filename));


                         }

                         int answer = QMessageBox::question(this, "PDF généré avec succes", "Voulez vous afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                         if (answer == QMessageBox::Yes)
                         {
                             QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/abdel/OneDrive/Documents/Gestion_Espaces/Description.pdf"));

                             painter.end();
                         }
                         if (answer == QMessageBox::No)
                         {
                             painter.end();
                         }

    }
}

float gestionEspace::calculer()
{
    Espaces ES ;
    float fact=0;
       QString cher =ui->select_esp->currentText();
       QSqlQuery qry;
       qry=ES.select(cher);
       if(qry.exec())
       {
           while(qry.next())
           {
               fact+=qry.value(5).toFloat();
           }
       }
    if(ui->checkBox_espace->isChecked())
        fact+=10;
    if(ui->checkBox_2_espace->isChecked())
        fact+=20;

    if(ui->checkBox_3_espace->isChecked())
        fact+=5;
    if(ui->checkBox_4_espace->isChecked())
        fact+=5;
    if(ui->checkBox_5_espace->isChecked())
        fact+=10;
  return fact;
}

void gestionEspace::on_Facture_pb_clicked()
{
    Espaces ES;
    QString cher =ui->select_esp->currentText();
    QSqlQuery qry;
    qry=ES.select(cher);
    QString opt;
    QString p;
    float f=calculer();
    QString b = QString::number(f);
    QPdfWriter pdf("C:/Users/abdel/OneDrive/Documents/Gestion_Espaces/Facture.pdf");

                         QPainter painter(&pdf);

                         int i = 2500;

                         painter.setPen(Qt::red);
                         painter.setFont(QFont("Arial",15 , 15 , true));
                         painter.drawText(2300,1000,"FACTURE DU CLIENT:");


                         painter.drawRect(0,1700,9600,500);
                         painter.setPen(Qt::black);
                         painter.setFont(QFont("Arial", 9));
                         painter.drawText(200,2000,"CATEGORIE");
                         painter.drawText(2000,2000,"TARIF");
                         painter.drawText(3800,2000,"OPTIONS");
                         painter.drawText(9000,2000,"TOTAL");



                             if(ui->checkBox_espace->isChecked())
                                {
                                 opt="ecran de projection";
                                 p="10dt";
                                }
                             if(ui->checkBox_2_espace->isChecked())
                             {
                                 opt="systeme de visioconference";
                                 p="20dt";
                                }
                             if(ui->checkBox_3_espace->isChecked())
                             {
                                 opt="tableau";
                                 p="5dt";
                                }
                             if(ui->checkBox_4_espace->isChecked())
                             {
                                 opt="flip chart";
                                 p="5dt";
                                }
                             if(ui->checkBox_5_espace->isChecked())
                             {
                                 opt="video projecteur";
                                 p="10dt";
                                }
                             if(ui->checkBox_espace->isChecked() && ui->checkBox_2_espace->isChecked())
                             {
                                 opt="ecran de projection & systeme de visioconference\n";
                                 p="10dt + 20dt";
                                }
                             if(ui->checkBox_espace->isChecked() && ui->checkBox_3_espace->isChecked())
                             {
                                 opt="ecran de projection & tableau";
                                 p="10dt + 5dt";
                                }
                             if(ui->checkBox_espace->isChecked() && ui->checkBox_4_espace->isChecked())
                             {
                                 opt="ecran de projection & flip chart";
                                 p="10dt + 5dt";
                                }
                             if(ui->checkBox_espace->isChecked() && ui->checkBox_5_espace->isChecked())
                             {
                                 opt="ecran de projection & video projecteur";
                                 p="10dt + 10dt";
                                }

                             if(ui->checkBox_2_espace->isChecked() && ui->checkBox_3_espace->isChecked())
                             {
                                 opt="tableau & systeme de visioconference\n";
                                 p="5dt + 20dt";
                                }
                             if(ui->checkBox_2_espace->isChecked() && ui->checkBox_4_espace->isChecked())
                             {
                                 opt="systeme de visioconference & flip chart";
                                 p="20dt + 5dt";
                                }
                             if(ui->checkBox_2_espace->isChecked() && ui->checkBox_5_espace->isChecked())
                             {
                                 opt="systeme de visioconference & video projecteur";
                                 p="20dt + 10dt";
                                }

                             if(ui->checkBox_3_espace->isChecked() && ui->checkBox_4_espace->isChecked())
                             {
                                 opt="tableau & flip chart\n";
                                 p="5dt + 5dt";
                                }
                             if(ui->checkBox_3_espace->isChecked() && ui->checkBox_5_espace->isChecked())
                             {
                                 opt="tableau & video projecteur";
                                 p="5dt + 10dt";
                                }

                             if(ui->checkBox_4_espace->isChecked() && ui->checkBox_5_espace->isChecked())
                             {
                                 opt="flip chart & video projecteur";
                                 p="5dt + 10dt";
                                }

                             if(ui->checkBox_4_espace->isChecked() && ui->checkBox_5_espace->isChecked() && ui->checkBox_espace->isChecked())
                             {
                                 opt="flip chart & video projecteur & ecran de projection";
                                 p="5dt + 10dt + 10dt";
                                }



                             if(qry.exec())
                             {
                                 while(qry.next())
                                 {
                                     painter.drawText(200,i,qry.value(1).toString());
                                     painter.drawText(2000,i,qry.value(5).toString());
                                 }
                             }

                             painter.drawText(3800,i,opt);
                             painter.drawText(4300,i+200,p);
                             painter.drawText(9000,i,b);


                         int answer = QMessageBox::question(this, "Facture générée avec succes", "Voulez vous afficher la facture? ?", QMessageBox::Yes |  QMessageBox::No);
                         if (answer == QMessageBox::Yes)
                         {
                             QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/abdel/OneDrive/Documents/Gestion_Espaces/Facture.pdf"));

                             painter.end();
                         }
                         if (answer == QMessageBox::No)
                         {
                             painter.end();
                         }




}
void gestionEspace::on_Excel_pb_clicked()
{
    //exporter le tableau en pdf
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                                     tr("Excel Files (*.xls)"));
                     if (fileName.isEmpty())
                         return;

                     ExportExcelObject obj(fileName, "Espaces", ui->tableView_espace);

                     //colums to export
                     obj.addField(0, "ID_ES", "char(20)");
                     obj.addField(1, "Catégorie", "char(20)");
                     obj.addField(2, "Description", "char(20)");
                     obj.addField(3, "Nb_Places", "char(20)");
                     obj.addField(4, "Superficie", "char(20)");
                     obj.addField(5, "Tarif", "char(20)");
                     obj.addField(6, "Disponibilite", "char(20)");
                     obj.addField(7, "Image", "char(20)");




                     int retVal = obj.export2Excel();
                     if( retVal > 0)
                     {
                         QMessageBox::information(this, tr("Done"),
                                                  tr("Toutes les informations ont été enregistrée"));
                     }
}

void gestionEspace::update_label()
{
   data=A.read_from_arduino();
    if (data=="1111")
    {
      ui->le_doesntexist->setText("EXIST");
      ui->le_lampe->setText("ON");
      ui->le_buzzer->setText("ON");// si les données reçues de arduino via la liaison série sont égales à 1 alors afficher ON
    }
        else if (data=="0000")
    {
        ui->le_doesntexist->setText("DOESNT EXIST");
        ui->le_lampe->setText("OFF");
        ui->le_buzzer->setText("OFF");
        // si les données reçues de arduino via la liaison série sont égales à o //alors afficher OF
     }
    qDebug()<<"data"<<data;

}



void gestionEspace::m_a_j_stat()
{
    // set dark background gradient:
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->customplot->setBackground(QBrush(gradient));


    // create empty bar chart objects:
    QCPBars *nombre = new QCPBars(ui->customplot->xAxis, ui->customplot->yAxis);
    nombre->setAntialiased(false);
    nombre->setStackingGap(1);

    // set names and colors:
    nombre->setName("Nombre d'espaces");
    nombre->setPen(QPen(QColor(111, 9, 176).lighter(170)));
    nombre->setBrush(QColor(111, 9, 176));

    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4;
    labels << "Coworking space" << "Bureau privatif" << "Salle de reunion" << "Salle de conference";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->customplot->xAxis->setTicker(textTicker);
    ui->customplot->xAxis->setTickLabelRotation(0);
    ui->customplot->xAxis->setSubTicks(false);
    ui->customplot->xAxis->setTickLength(0, 4);
    ui->customplot->xAxis->setRange(0,6);
    ui->customplot->xAxis->setBasePen(QPen(Qt::white));
    ui->customplot->xAxis->setTickPen(QPen(Qt::white));
    ui->customplot->xAxis->grid()->setVisible(true);
    ui->customplot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->customplot->xAxis->setTickLabelColor(Qt::white);
    ui->customplot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    ui->customplot->yAxis->setRange(0, 12.1);
    ui->customplot->yAxis->setPadding(5); // a bit more space to the left border
    ui->customplot->yAxis->setLabel("Le nombre d'espaces existants\n pour chaque catégorie");
    ui->customplot->yAxis->setBasePen(QPen(Qt::white));
    ui->customplot->yAxis->setTickPen(QPen(Qt::white));
    ui->customplot->yAxis->setSubTickPen(QPen(Qt::white));
    ui->customplot->yAxis->grid()->setSubGridVisible(true);
    ui->customplot->yAxis->setTickLabelColor(Qt::white);
    ui->customplot->yAxis->setLabelColor(Qt::white);
    ui->customplot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->customplot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    QVector<double> data;

    int cs=0;
    int sr=0;
    int bp=0;
    int sc=0;
    const int ligne = ui->tableView_espace->model()->rowCount();
     for (int row = 0; row < ligne; row++)
     {
         if (!ui->tableView_espace->isColumnHidden(1)) {

         if(ui->tableView_espace->model()->data(ui->tableView_espace->model()->index(row, 1))=="Coworking Space")
               cs++;
         else if (ui->tableView_espace->model()->data(ui->tableView_espace->model()->index(row, 1))=="Bureau Privatif")
             bp++;
         else if (ui->tableView_espace->model()->data(ui->tableView_espace->model()->index(row, 1))=="Salle de Reunion")
             sr++;
         else if(ui->tableView_espace->model()->data(ui->tableView_espace->model()->index(row, 1))=="Salle de Conference")
             sc++;
     }
     }


    data  << cs << bp << sr << sc ;

    nombre->setData(ticks, data);

    // setup legend:
    ui->customplot->legend->setVisible(true);
    ui->customplot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->customplot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->customplot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customplot->legend->setFont(legendFont);
    ui->customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}


