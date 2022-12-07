#include "cancel.h"
#include "ui_cancel.h"

cancel::cancel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cancel)
{
    ui->setupUi(this);
}

cancel::~cancel()
{
    delete ui;
}

void cancel::updateUI()
{
    ui->cmbSeats->clear();
    //ui->lblInfo->setText("");

    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("select Seat from cppbuzz_movie_ticket_booking where Available='N'");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->lblInfo->setText(query.lastError().text());
    }
    else{
        qDebug() << "read was successful "<< query.lastQuery();
       }

    while(query.next())
    {
        ui->cmbSeats->addItem(query.value(0).toString());
    }

    if(ui->cmbSeats->count()<=0)
        ui->btnCancel->setEnabled(true);

}

void cancel::on_btnCancel_clicked()
{
    QString sSeat = ui->cmbSeats->currentText();

    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("update cppbuzz_movie_ticket_booking set Available='Y' where Seat= '" + sSeat +"'");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->lblInfo->setText(query.lastError().text());
    }
    else{
        if(query.numRowsAffected() > 0)
        {
            ui->lblInfo->setText("Success!");
            qDebug() << "read was successful "<< query.lastQuery();
        }
        else
        {
            ui->lblInfo->setText("Unable to update data");
        }
       }

    updateUI();
    emit mysignal1();
}
