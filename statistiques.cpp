#include "statistiques.h"
#include "ui_statistiques.h"
#include <qvariant.h>
#include <QGridLayout>
#include <QWidget>
#include <QtCore>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include <qwindow.h>

statistiques::statistiques(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistiques)
{
    ui->setupUi(this);
}

statistiques::~statistiques()
{
    delete ui;
}

void statistiques::choix_pie()
{
    QSqlQuery q1,q2,q3,q4;
    qreal tot=0,c1=0,c2=0,c3=0;

    q1.prepare("SELECT * FROM TACHES");
    q1.exec();

    q2.prepare("SELECT * FROM TACHES WHERE ETAT='A FAIRE'");
    q2.exec();

    q3.prepare("SELECT * FROM TACHES WHERE ETAT='EN COURS'");
    q3.exec();

    q4.prepare("SELECT * FROM TACHES WHERE ETAT='FAIT'");
    q4.exec();

    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}

    c1=c1/tot;
    c2=c2/tot;
    c3=c3/tot;

    // Define slices and percentage of whole they take up
    QPieSeries *series = new QPieSeries();
    series->append("A FAIRE",c1);
    series->append("EN COURS",c2);
    series->append("FAIT",c3);

    // Create the chart widget
    QChart *chart = new QChart();

    // Add data to chart with title and show legend
    chart->addSeries(series);
    chart->legend()->show();


    // Used to display the chart
    chartView = new QChartView(chart,ui->label_stat);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(400,400);
    chartView->show();

    float p_aFaire=c1*100;
    float p_enCours=c2*100;
    float p_fait=c3*100;

    QString afaire= QString::number(p_aFaire);
    QString enCours= QString::number(p_enCours);
    QString fait= QString::number(p_fait);

    ui->le_aFaire->setText(afaire+'%');
    ui->le_enCours->setText(enCours+'%');
    ui->le_Fait->setText(fait+'%');
}

