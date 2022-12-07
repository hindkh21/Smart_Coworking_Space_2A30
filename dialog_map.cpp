#include "dialog_map.h"
#include "ui_dialog_map.h"

dialog_map::dialog_map(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_map)
{
    ui->setupUi(this);
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QCoreApplication::organizationName(), QCoreApplication::applicationName());

    ui->WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");
}

dialog_map::~dialog_map()
{
    delete ui;
}

void dialog_map::on_pushButton_Fermer_clicked()
{
        close();
}
