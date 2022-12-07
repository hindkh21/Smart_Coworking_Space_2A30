#include "gestionreservation.h"
#include "ui_gestionreservation.h"
#include "connection.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPushButton>
#include <QPdfWriter>
#include <QPainter>
#include <QRadioButton>
#include "QWidget"
#include "dialog_stats.h"
#include "dialog_map.h"
gestionreservation::gestionreservation(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::gestionreservation)
{
    ui->setupUi(this);
    ui->lineEdit_cin->setValidator( new QIntValidator(0, 99999999, this));
    ui->lineEdit_Numtel->setValidator( new QIntValidator(0, 99999999, this));
    ui->line_Perso->setValidator( new QIntValidator(0, 99, this));
    QRegularExpression rx("^[A-Za-z_][A-za-z]*");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->lineEdit_Nom->setValidator(validator);
    ui->lineEdit_Prenom->setValidator(validator);
    ui->comboBox->setModel(R.afficher_cin());
    ui->tableView->setModel (R.afficher());
    ptrBook  = new book(this);
    ptrCancel = new cancel(this);
    connect(ptrBook, &book::mysignal, this, &gestionreservation::updateUI);
    connect(ptrCancel, &cancel::mysignal1, this, &gestionreservation::updateUI);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
        break;
    case(-1):qDebug() << "arduino is not available";
    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_RFID())); // permet de lancer
    //le slot update_label suite à la reception du signal readyRead (reception des données).
    updateUI();

}

gestionreservation::~gestionreservation()
{
    delete ui;
    delete ptrBook;
    delete ptrCancel;
}


void gestionreservation::on_pb_ajouter_clicked()
{
    int CIN=ui->lineEdit_cin->text().toInt();
    QString NOM=ui->lineEdit_Nom->text();
    QString PRENOM=ui->lineEdit_Prenom->text();
    int NUM_TEL=ui->lineEdit_Numtel->text().toInt();
     QString PLACES=ui->lineEdit_Place->text();
     int PERSONNES=ui->line_Perso->text().toInt();
     QString RFID=ui->label_14->text();


    reservation R(CIN,NOM,PRENOM,NUM_TEL,PLACES,PERSONNES,RFID);
    bool test=R.AjouterF();
    if(test)
    {
        ui->label_Info->setText("Ajout Effectué");
        ui->comboBox->setModel(R.afficher_cin());
        ui->tableView->setModel(R.afficher());
    }
    else
    {
        ui->label_Info->setText("Ajout non Effectué");
    }
}

void gestionreservation::on_pb_Supprimer_clicked()
{
    reservation R;
    R.setcin(ui->comboBox->currentText().toInt());
    bool test=R.SupprimerF(R.getcin());
    if(test)
    {
        ui->label_Info->setText("Suppression effectué");
        ui->tableView->setModel(R.afficher());
        ui->comboBox->setModel(R.afficher_cin());
    }
    else
    {
        ui->label_Info->setText("Suppression non effectué");
    }
}

void gestionreservation::on_pb_Modifier_clicked()
{
    int CIN=ui->lineEdit_cin->text().toInt();
    QString NOM=ui->lineEdit_Nom->text();
    QString PRENOM=ui->lineEdit_Prenom->text();
    int NUM_TEL=ui->lineEdit_Numtel->text().toInt();
    QString PLACES=ui->lineEdit_Place->text();
    int PERSONNES=ui->line_Perso->text().toInt();
    reservation R(CIN,NOM,PRENOM,NUM_TEL,PLACES,PERSONNES,RFID);
    bool test=R.ModifierF();
    if(test)
    {
        ui->label_Info->setText("Modification effectué");
        ui->tableView->setModel(R.afficher());
        ui->comboBox->setModel(R.afficher_cin());
    }
    else
    {
        ui->label_Info->setText("Modification non effectué");
    }
}

void gestionreservation::on_comboBox_currentIndexChanged(int)
{
    int cin=ui->comboBox->currentText().toInt();
    QString cin_1=QString::number(cin);
    QSqlQuery query;
    query.prepare("SELECT * FROM RESERVATION where CIN='"+cin_1+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->lineEdit_cin->setText(query.value(0).toString()) ;
            ui->lineEdit_Nom->setText(query.value(1).toString()) ;
            ui->lineEdit_Prenom->setText(query.value(2).toString()) ;
            ui->lineEdit_Numtel->setText(query.value(3).toString()) ;
            ui->lineEdit_Place->setText(query.value(4).toString()) ;
            ui->line_Perso->setText(query.value(5).toString()) ;
            ui->label_14->setText(query.value(6).toString()) ;

        }
    }
}

void gestionreservation::on_pb_Quitter_clicked()
{
    close();
}

void gestionreservation::on_pB_TrierParCIN_clicked()
{
    {
        ui->label_Info->setText("Tri par CIN est effectué");
        ui->tableView->setModel(R.tri_cin());
    }

}


void gestionreservation::on_pb_TrierParNom_clicked()
{
    ui->label_Info->setText("Tri par Num Tel est effectué");
    ui->tableView->setModel(R.tri_numtel());
}


void gestionreservation::on_pB_Recherche_clicked()
{
    reservation R;
    QString text;

    if (ui->rB_CIN->isChecked()==true)
    {
        R.clearTable(ui->tableView);
        int cin=ui->lineEdit_CINRecherche->text().toInt();
        R.chercheCIN(ui->tableView,cin);
    }
    if (ui->rB_NumTel->isChecked()==true)
    {
        R.clearTable(ui->tableView);
        int Numt=ui->lineEdit_CINRecherche->text().toInt();
        R.chercheNumTel(ui->tableView,Numt);
    }
}
void gestionreservation::updateUI()
{
    qDebug() << "in updateUI()";

    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("select Seat, Available from cppbuzz_movie_ticket_booking");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        //ui->lblInfo->setText(query.lastError().text());
    }
    else{
        qDebug() << "read was successful "<< query.lastQuery();
    }

   // int no = 1;
    while(query.next())
    {
        QString sLabel = "lbl" + query.value(0).toString();
        qDebug() <<"label is : "<< sLabel;
        QLabel * ptr = this->findChild<QLabel*>(sLabel);
        if(ptr!=nullptr)
        {   qDebug() << "label found "<<sLabel;
            if(query.value(1).toString().compare("N") == 0)
            {
                //int no = (qrand() % ((6 + 1) - 1) + 1);
                QPixmap pm ("C:/Users/chtar/Desktop/Smart_Coworking_Space_2A30-integration-reservation/imageres/reserved.png");
                ptr->setPixmap(pm);
                ptr->setScaledContents(true);
                qDebug()<<query.value(0).toString() << " : is booked";
            }
            else
            {
                QPixmap pm ("C:/Users/chtar/Desktop/Smart_Coworking_Space_2A30-integration-reservation/imageres/workplace.png");
                ptr->setPixmap(pm);
                ptr->setScaledContents(true);
                qDebug()<<query.value(0).toString() << " : is Available";
            };


        }
    }

}

void gestionreservation::on_btnBook_clicked()
{
    ptrBook->updateUI();
    ptrBook->show();
}

void gestionreservation::on_btnCancel_clicked()
{
    ptrCancel->updateUI();
    ptrCancel->show();
}

void gestionreservation::on_btnReset_clicked()
{

    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("update cppbuzz_movie_ticket_booking set Available = 'Y'");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        //ui->lblInfo->setText(query.lastError().text());
    }
    else{
        if(query.numRowsAffected() > 0)
        {

            qDebug() << "Update was successful. "<< query.lastQuery();
        }
        else
        {
            qDebug() << "Update Failed. "<< query.lastQuery();
        }

    }

    updateUI();

}


void gestionreservation::on_pB_ExPDF_clicked()
{
    QPdfWriter pdf("C:/Users/chtar/Desktop/Smart_Coworking_Space_2A30-integration-reservation/Liste3.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 20));
    painter.drawPixmap(QRect(100,400,2000,2000),QPixmap("C:/Users/chtar/Desktop/Smart_Coworking_Space_2A30-integration-reservation/image/310432895_2325982227549440_2476852675195435336_n.png"));
    painter.drawText(3000,1500,"LISTE DES RESERVATION");
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 38));
    painter.drawRect(2700,200,6300,2600);
    painter.drawRect(0,3000,9600,500);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300,3300,"CIN");
    painter.drawText(1300,3300,"NOM");
    painter.drawText(2300,3300,"PRENOM");
    painter.drawText(3300,3300,"NUMTEL");
    painter.drawText(4300,3300,"PLACE");
    painter.drawText(5300,3300,"PERSONNES");


    QSqlQuery query;
    query.prepare("<SELECT CAST( GETDATE() AS Date ) ");
    time_t tt;
    struct tm* ti;
    time(&tt);
    ti=localtime(&tt);
    asctime(ti);
    painter.drawText(500,300, asctime(ti));
    query.prepare("select * from RESERVATION");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(1300,i,query.value(1).toString());
        painter.drawText(2300,i,query.value(2).toString());
        painter.drawText(3300,i,query.value(3).toString());
        painter.drawText(4300,i,query.value(4).toString());
        painter.drawText(5300,i,query.value(5).toString());
        painter.drawText(6300,i,query.value(6).toString());


        i = i +500;
    }
    int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/chtar/Desktop/Smart_Coworking_Space_2A30-integration-reservation/Liste3.pdf"));
        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}

void gestionreservation::on_pB_ExPDF_2_clicked()
{
    dialog_stats stats;
    stats.setModal(true);
    stats.exec();
}

void gestionreservation::on_pB_Map_clicked()
{
    dialog_map map;
    map.setModal(true);
    map.exec();

}
void gestionreservation::update_RFID()
{
    QSqlQuery query,q2;
    QByteArray data="";
    QString UserMessage="";
    data=A.read_from_arduino();
    RFID=RFID+data;
    if(RFID!="" && RFID.length()==11)
    {
        query.prepare("select * from RESERVATION where RFID='"+RFID+"'");
        if(query.exec())
        {
            if (query.next())
            {
                QString NOM= query.value(1).toString();
                QString PRENOM= query.value(2).toString();
                UserMessage=NOM+" "+PRENOM;
                QString c;
                QByteArray m= UserMessage.toUtf8();
                A.write_to_arduino(m);
                ui->label_14->setText(RFID);
                qDebug() <<  " RFID is: " <<RFID;
                qDebug() <<  " User: " <<UserMessage;
                // qDebug() <<  " Arduino Signal: " <<message;

            }
            else
            {
                ui->label_14->setText(RFID);
                QString message ="Error";
                QByteArray br = message.toUtf8();
                A.write_to_arduino(br);
                qDebug() <<  " RFID is: " <<RFID;
                qDebug() <<  " Arduino Signal: " <<message;
            }
        }
        if(RFID.length()==11)
        {
            RFID="";
        }
}
   }
