#include "gestionclient.h"
#include "ui_gestionclient.h"
#include "client.h"
#include <QMessageBox>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QTextDocument>
#include <QPieSeries>
#include <QtCharts>
#include <QColor>
#include <QtCore>
#include <QFile>
#include <QFileDialog>
#include <QSaveFile>
#include "smtp.h"

gestionClient::gestionClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gestionClient)
{
    ui->setupUi(this);
    ui->tab_client_4->setModel(C.afficher());
    ui->lineEdit_id_4->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_numtel_4->setValidator(new QIntValidator(0,99999999,this));
    QRegularExpression rx("\\b[a-zA-Z]{1,20}\\b");
    ui->lineEdit_prenom_4->setValidator(new QRegularExpressionValidator(rx,this));
    ui->lineEdit_nom_4->setValidator(new QRegularExpressionValidator(rx,this));
    //ui->lineEdit_prenom->setInputMask("AAAAAAAAAAAAAAAAAAAA");
    //ui->lineEdit_nom->setInputMask("AAAAAAAAAAAAAAAAAAAA");
    ui->tabWidget->setGeometry(0,0,1500,1000);
    ui->paswd_5->setText("nuoqikogfnfeebao");
    chart();
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
}

gestionClient::~gestionClient()
{
    delete ui;
}


void gestionClient::on_pushButton_34_clicked()
{

    int id = ui->lineEdit_id_4->text().toInt();
    QString prenom=ui->lineEdit_prenom_4->text();
    QString nom=ui->lineEdit_nom_4->text();
    int numtel= ui->lineEdit_numtel_4->text().toInt();
    QString email=ui->lineEdit_email_4->text();
    QString type=ui->comboBox_4->currentText();
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
       mailREX.setCaseSensitivity(Qt::CaseInsensitive);
       mailREX.setPatternSyntax(QRegExp::RegExp);
       bool regMat = mailREX.exactMatch(ui->lineEdit_email_4->text());
    Client C(id,prenom,nom,numtel,email,type);


    if(ui->lineEdit_id_4->text().isEmpty() || ui->lineEdit_prenom_4->text().isEmpty()|| ui->lineEdit_nom_4->text().isEmpty()|| ui->lineEdit_numtel_4->text().isEmpty()|| ui->lineEdit_email_4->text().isEmpty())
    {
            ui->tab_client_4->setModel(C.afficher());
            chart();
            QMessageBox::warning(nullptr, QObject::tr("Attention"),
                        QObject::tr("Veuillez remplir tout les champs.\n"), QMessageBox::Ok);
    }
    else if(!regMat)
    {
        ui->label_email_valid_4->setText("mail non verifiee");
    }
    else
    {

                   bool test=C.ajouter();
                   //ui->tableView->setModel(ajt.afficher());
                   QMessageBox msgBox;
                   if (test)
                   {
                       ui->label_email_valid_4->setText("mail verifiee");
                       //ui->tableView->setModel(ajt.afficher());
                       msgBox.setText("Ajout avec succés.");
                       msgBox.exec();
                       ui->tab_client_4->setModel(C.afficher());
                   }
                   else {
                       QMessageBox::critical(nullptr, QObject::tr("Ajouter un PRODUIT"),
                                                 QObject::tr("Erreur !.\n"
                                                             "Click Cancel to exit."), QMessageBox::Cancel);

                   }
      }
    chart();




}

/*void MainWindow::on_pushButton_4_clicked()
{
    C.recherche(ui->lineEdit_id->text().toInt());
    ui->lineEdit_prenom->setText(C.getprenom());
    ui->lineEdit_nom->setText(C.getprenom());
    ui->lineEdit_numtel->setText(QString::number(C.getnumtel()));
    ui->lineEdit_email->setText(C.getemail());
    ui->comboBox->setCurrentText(C.gettype());
}*/

void gestionClient::on_pushButton_39_clicked()
{
    QString nom = ui->id_sup_4->text();
            Client C1;
            bool test=C1.supprimer(nom);
            ui->tab_client_4->setModel(C.afficher());//refresh
            if(test)
            {

                QMessageBox::information(nullptr, QObject::tr("Supprimer un client"),
                            QObject::tr("client supprimé.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                ui->tab_client_4->setModel(C.afficher());//refresh
                chart();
            }
}




void gestionClient::on_pushButton_35_clicked()
{
        ui->tab_client_4->setModel(C.afficher());
        ui->tab_client_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        int id=ui->lineEdit_id_4->text().toInt();
        QString nom=ui->lineEdit_nom_4->text();
        QString prenom=ui->lineEdit_prenom_4->text();
        int num_tel=ui->lineEdit_numtel_4->text().toInt();
        QString email=ui->lineEdit_email_4->text();
        QString type = ui->comboBox_4->currentText();
        Client C(id,nom,prenom,num_tel,email,type);
        bool test=C.modifier(id);
        QMessageBox msBox;
        if(test)
        {
            ui->tab_client_4->setModel(C.afficher());
            ui->tab_client_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            msBox.setText("modification reussite");
            msBox.exec();
        }
        else
        {
            msBox.setText("ERREUR");
            msBox.exec();
        }
}



void gestionClient::on_pushButton_40_clicked()
{
    ui->tab_client_4->setModel(C.afficher1());
}

void gestionClient::on_pushButton_38_clicked()
{
    QString strStream;
                        QTextStream out(&strStream);

                        const int rowCount = ui->tab_client_4->model()->rowCount();
                        const int columnCount = ui->tab_client_4->model()->columnCount();

                        out <<  "<html>\n"
                            "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg("strTitle")
                            <<  "</head>\n"
                            "<body bgcolor=#ffffff link=#5000A0>\n"

                           //     "<align='right'> " << datefich << "</align>"
                            "<center> <H1>Liste des clients </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                        // headers
                        out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                        for (int column = 0; column < columnCount; column++)
                            if (!ui->tab_client_4->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tab_client_4->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";

                        // data table
                        for (int row = 0; row < rowCount; row++) {
                            out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                            for (int column = 0; column < columnCount; column++) {
                                if (!ui->tab_client_4->isColumnHidden(column)) {
                                    QString data = ui->tab_client_4->model()->data(ui->tab_client_4->model()->index(row, column)).toString().simplified();
                                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                }
                            }
                            out << "</tr>\n";
                        }
                        out <<  "</table> </center>\n"
                            "</body>\n"
                            "</html>\n";

                  QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                   QPrinter printer (QPrinter::PrinterResolution);
                    printer.setOutputFormat(QPrinter::PdfFormat);
                   printer.setPaperSize(QPrinter::A4);
                  printer.setOutputFileName(fileName);

                   QTextDocument doc;
                    doc.setHtml(strStream);
                    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                    doc.print(&printer);
}

void gestionClient::chart()
{
    QHBoxLayout *layout = new QHBoxLayout();

    QPieSeries *series = new QPieSeries();
    int nb_etudiant=C.calcul_type_stat("Etudiant");
    int nb_eleve=C.calcul_type_stat("Eleve");
    int nb_total=nb_etudiant+nb_eleve;
    QPieSlice *s1=new QPieSlice();
    s1->setLabel("Etudiant");
    s1->setValue(nb_etudiant);
    s1->setColor(QColor(250, 216, 255));
    QPieSlice *s2=new QPieSlice();
    s2->setLabel("Eleve");
    s2->setValue(nb_eleve);

    s2->setColor(QColor(250, 170, 255));

    series->append(s1);
    series->append(s2);
    series->setPieSize(nb_total);

    QChart *chart = new QChart();


    chart->addSeries(series);

    chart->setTitle("Qt5 Pie Chart Example");
    chart->setAnimationOptions(QChart::AllAnimations);
    QChartView *chartView = new QChartView(chart);
    chartView->resize(580,300);
    //chartView->setParent(ui->frame);
    layout->addWidget(chartView);
    ui->frame_4->setLayout(layout);
    ui->frame_4->layout()->deleteLater();
    //qDebug() << "hind";


}


void gestionClient::on_pushButton_42_clicked()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file_5->setText( fileListString );

}

void gestionClient::on_pushButton_43_clicked()

{
    qDebug()  <<  "hi";
    Smtp* smtp = new Smtp(ui->uname_5->text(), ui->paswd_5->text(), ui->server_5->text(), ui->port_5->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    if( !files.isEmpty() )
        smtp->sendMail(ui->uname_5->text(), ui->rcpt_5->text() , ui->subject_5->text(),ui->msg_5->toPlainText(), files );
    else
        smtp->sendMail(ui->uname_5->text(), ui->rcpt_5->text() , ui->subject_5->text(),ui->msg_5->toPlainText());
}
void gestionClient::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}



void gestionClient::on_pushButton_41_clicked()
{
    QSqlQuery query;
    query.exec("SELECT DISPONIBILITE FROM RESERVATION WHERE ID_RES = '"+ui->lineEdit_sms_id_4->text()+"'");
    query.first();
    std::string text=query.value(0).toString().toStdString();
    std::string num_tel=ui->lineEdit_sms_num_tel_4->text().toStdString();
    std::string s = "curl -X \"POST\" \"https://rest.nexmo.com/sms/json\"  "
                   "-d \"from=ComfyBox\" "
                   "-d \"text="+text+"\" "
                   "-d \"to=216"+num_tel+"\" "
                   "-d \"api_key=3d23f342\"  "
                   "-d \"api_secret=8xXF0BZmKQIgI8ne\"";
    const char* str = s.c_str();
    system(str);

}


void gestionClient::on_pushButton_36_clicked(){
    C.getDatabaseValue(ui->lineEdit_id_4->text().toInt());
    ui->lineEdit_nom_4->setText(C.getnom());
    ui->lineEdit_prenom_4->setText(C.getprenom());
    ui->lineEdit_email_4->setText(C.getemail());
    ui->lineEdit_numtel_4->setText(QString::number(C.getnumtel()));
    ui->comboBox_4->setCurrentText(C.gettype());
}
/*void gestionClient::update_label()
{

    data=A.read_from_arduino();
    qDebug() << data;
    QSqlQuery query;

    if(data=="1")
          {

            qDebug() << query.exec("select NOM_EMP from EMPLOYES where ID_CARD='83 6C DF 91'");
        query.first();
            ui->label_40->setText("Bonjour "+query.value(0).toString());// si les données reçues de arduino via la liaison série sont égales à 1

            }
    if(data=="2")
    {
        qDebug() << query.exec("select NOM_EMP from EMPLOYES where ID_CARD='13 74 5E A7'");
        query.first();
        ui->label_40->setText("Bonjour "+query.value(0).toString());// si les données reçues de arduino via la liaison série sont égales à 1
    }
    if(data=="0")
        ui->label_40->setText("refusé");   // si les données reçues de arduino via la liaison série sont égales à 0

}*/
void gestionClient::on_pushButton_11_clicked()
{

    QSqlQuery query;
    data=A.read_from_arduino();
    QString idk=data;
   /* //idk= idk.remove(' ');
    qDebug()<<"data "<<idk;
    int f=idk.toInt();
    //QString ohr="83 6C DF 91";
    query.exec("select * from EMPLOYES where ID_CARD='"+QString::number(f)+"'");
    query.first();
    qDebug()<< query.value(7).toString();
    if(query.value(7).toString()==1)
    {

        qDebug()<< "Autorisé";
        A.write_to_arduino("1");
    }
    else
    A.write_to_arduino("0");
    */

}



























// void gestionClient::on_lineEdit_4_textChanged(const QString &arg1)
// {
    // ui->tab_client_4->setModel(C.recherche(ui->lineEdit_4->text(),ui->lineEdit_4->text(),ui->lineEdit_4->text()));
// }

