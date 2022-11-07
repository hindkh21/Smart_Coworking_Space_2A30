#define SECURITY_WIN32
#include "mainwindow.h"
#include "ui_mainwindow.h"
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
#include<iostream>
#include<sstream>
#include<windows.h>
#include<wininet.h>
#include<winineti.h>
  #include "windows.h"
using namespace std;
#include "smtp.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    ui->tab_client->setModel(C.afficher());
    ui->lineEdit_id->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_numtel->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_prenom->setInputMask("AAAAAAAAAAAAAAAAAAAA");
    ui->lineEdit_nom->setInputMask("AAAAAAAAAAAAAAAAAAAA");


    chart();

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_3_clicked()//ajouter
{

    int id = ui->lineEdit_id->text().toInt();
    QString prenom=ui->lineEdit_prenom->text();
    QString nom=ui->lineEdit_nom->text();
    int numtel= ui->lineEdit_numtel->text().toInt();
    QString email=ui->lineEdit_email->text();
    QString type;
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
       mailREX.setCaseSensitivity(Qt::CaseInsensitive);
       mailREX.setPatternSyntax(QRegExp::RegExp);

       bool regMat = mailREX.exactMatch(ui->lineEdit_email->text());


    if(ui->comboBox->currentIndex()==0)

        type="Etudiant";


    else
        if(ui->comboBox->currentIndex()==1)
        {

    type="Eleve";
        }
    else {
        type="ely baadou";
    }

    Client C(id,prenom,nom,numtel,email,type);


    if(ui->lineEdit_id->text().isEmpty() || ui->lineEdit_prenom->text().isEmpty()|| ui->lineEdit_nom->text().isEmpty()|| ui->lineEdit_numtel->text().isEmpty()|| ui->lineEdit_email->text().isEmpty())
    {
            ui->tab_client->setModel(C.afficher());
            chart();
            QMessageBox::warning(nullptr, QObject::tr("Attention"),
                        QObject::tr("Veuillez remplir tout les champs.\n"), QMessageBox::Ok);
    }
    else if(!regMat)
    {
        ui->label_email_valid->setText("mail non verifiee");
    }
    else
    {

                   bool test=C.ajouter();
                   //ui->tableView->setModel(ajt.afficher());
                   QMessageBox msgBox;
                   if (test)
                   {
                       ui->label_email_valid->setText("mail verifiee");
                       //ui->tableView->setModel(ajt.afficher());
                       msgBox.setText("Ajout avec succés.");
                       msgBox.exec();
                       ui->tab_client->setModel(C.afficher());
                   }
                   else {
                       QMessageBox::critical(nullptr, QObject::tr("Ajouter un PRODUIT"),
                                                 QObject::tr("Erreur !.\n"
                                                             "Click Cancel to exit."), QMessageBox::Cancel);

                   }
      }




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

void MainWindow::on_pushButton_5_clicked()
{
    QString nom = ui->id_sup->text();
            Client C1;
            bool test=C1.supprimer(nom);
            ui->tab_client->setModel(C.afficher());//refresh
            if(test)
            {

                QMessageBox::information(nullptr, QObject::tr("Supprimer un client"),
                            QObject::tr("client supprimé.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                ui->tab_client->setModel(C.afficher());//refresh
                chart();
            }
}




void MainWindow::on_pushButton_9_clicked()
{
        ui->tab_client->setModel(C.afficher());
        ui->tab_client->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        int id=ui->lineEdit_id->text().toInt();
        QString nom=ui->lineEdit_nom->text();
        QString prenom=ui->lineEdit_prenom->text();
        int num_tel=ui->lineEdit_numtel->text().toInt();
        QString email=ui->lineEdit_email->text();
        QString type = ui->comboBox->currentText();
        Client C(id,nom,prenom,num_tel,email,type);
        bool test=C.modifier(id);
        QMessageBox msBox;
        if(test)
        {
            ui->tab_client->setModel(C.afficher());
            ui->tab_client->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            msBox.setText("modification reussite");
            msBox.exec();
        }
        else
        {
            msBox.setText("ERREUR");
            msBox.exec();
        }
}






void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{

    ui->tab_client->setModel(C.recherche(ui->lineEdit->text(),ui->lineEdit->text(),ui->lineEdit->text()));

}

void MainWindow::on_pushButton_7_clicked()
{
    ui->tab_client->setModel(C.afficher1());
}



void MainWindow::on_pushButton_2_clicked()
{
    QString strStream;
                        QTextStream out(&strStream);

                        const int rowCount = ui->tab_client->model()->rowCount();
                        const int columnCount = ui->tab_client->model()->columnCount();

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
                            if (!ui->tab_client->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tab_client->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";

                        // data table
                        for (int row = 0; row < rowCount; row++) {
                            out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                            for (int column = 0; column < columnCount; column++) {
                                if (!ui->tab_client->isColumnHidden(column)) {
                                    QString data = ui->tab_client->model()->data(ui->tab_client->model()->index(row, column)).toString().simplified();
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

void MainWindow::chart()
{

    QPieSeries *series = new QPieSeries();
    int nb_etudiant=C.calcul_type_stat("Etudiant");
    int nb_eleve=C.calcul_type_stat("Eleve");
    int nb_total=nb_etudiant+nb_eleve;
    series->append("Etudiant",nb_etudiant);

    series->append("Eleve",nb_eleve);
    series->setPieSize(nb_total);
    QChart *chart = new QChart();


    chart->addSeries(series);

    chart->setTitle("Qt5 Pie Chart Example");
    QChartView *chartView = new QChartView(chart);
    chartView->resize(580,300);
    chartView->setParent(ui->frame);

    //qDebug() << "hind";


}


void MainWindow::on_pushButton_4_clicked()
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

    ui->file_2->setText( fileListString );

}

void MainWindow::on_pushButton_clicked()
{
    qDebug()  <<  "hi";
    Smtp* smtp = new Smtp(ui->uname_2->text(), ui->paswd_2->text(), ui->server_2->text(), ui->port_2->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname_2->text(), ui->rcpt_2->text() , ui->subject_2->text(),ui->msg_2->toPlainText(), files );
    else
        smtp->sendMail(ui->uname_2->text(), ui->rcpt_2->text() , ui->subject_2->text(),ui->msg_2->toPlainText());
}
void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}



void MainWindow::on_pushButton_6_clicked()
{

    string encode(string url);

    // the SMS gateway's host
    // and port
    string host       = "localhost";
    int port          = 9502;

    // username
    // and password
    string username   = "admin";
    string password   = "abc123";

    // message
    string message    = "This is a test SMS.";

    // originator's phone number
    string originator = "+44555555555";

    // recipient's phone number.
    // to send the SMS to multiple recipients, separate them by using commas without spaces
    string recipient  = "+44333333333";

    // preparing the HTTPRequest URL
    stringstream url;
        url << "/api?action=sendmessage&username=" << encode(username);
        url << "&password=" << encode(password);
        url << "&recipient=" << encode(recipient);
        url << "&messagetype=SMS:TEXT&messagedata=" << encode(message);
        url << "&originator=" << encode(originator);
        url << "&responseformat=xml";

    // create socket
    HINTERNET inet = InternetOpen("Ozeki", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

    // open connection and bind it to the socket
    HINTERNET conn = InternetConnect(inet, host.c_str() , port, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);

    // open the HTTP request
    HINTERNET sess = HttpOpenRequest(conn, "GET", url.str().c_str(), "HTTP/1.1", NULL, NULL, INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_RELOAD, 0);

    // check errors
    int error = GetLastError();
    if(error == NO_ERROR)
    {
        // send HTTP request
        HttpSendRequest(sess, NULL, 0, NULL,0);

        // receive HTTP response

        int size = 1024;
        char *buffer = new char[size + 1];
        DWORD read;
        int rsize = InternetReadFile(sess, (void *)buffer, size, &read);
        string s = buffer;
        s = s.substr(0, read);

        // check status code
        int pos = s.find("<statuscode>0</statuscode>");

        // if statuscode is 0, write "Message sent." to output
        // else write "Error."
        if(pos > 0) cout << "Message sent." << endl;
        else cout << "Error." << endl;


}


// encoding converts characters that are not allowed in a URL into character-entity equivalent

}
string MainWindow::encode(string url)
{
    string hex = "0123456789abcdef";
    stringstream s;

    for(unsigned int i = 0; i < url.length(); i++)
    {
        byte c = (char)url.c_str()[i];
        if( ('a' <= c && c <= 'z')
        || ('A' <= c && c <= 'Z')
        || ('0' <= c && c <= '9') ){
            s << c;
        } else {
            if(c == ' ') s << "%20";
            else
            s << '%' << (hex[c >> 4]) << (hex[c & 15]);
        }
    }

    return s.str();
}
