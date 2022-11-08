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
    //ui->setupUi(this);
    QBarSet *set0 = new QBarSet("A FAIRE");
              QBarSet *set1 = new QBarSet("EN COURS");
              QBarSet *set2 = new QBarSet("FAIT");


              *set0 <<  Tmp.nbr_tache("A FAIRE")<< 0 << 0;
              *set1 << 0 << Tmp.nbr_tache("EN COURS") << 0;
              *set2 << 0 << 0 << Tmp.nbr_tache("FAIT");

              QBarSeries *series = new QBarSeries();
              series->append(set0);
              series->append(set1);
              series->append(set2);

              QChart *chart = new QChart();
              chart->addSeries(series);
              chart->setTitle("Productivité des employés ");
              chart->setAnimationOptions(QChart::SeriesAnimations);

              QStringList categories;
              categories << "A FAIRE"
                         << "EN COURS"
                         << "FAIT";

              QBarCategoryAxis *axis = new QBarCategoryAxis();
              axis->append(categories);
              chart->createDefaultAxes();
              chart->setAxisX(axis, series);

              chart->legend()->setVisible(true);
              chart->legend()->setAlignment(Qt::AlignBottom);

              QChartView *chartview = new QChartView(chart);
              chartview->setRenderHint(QPainter::Antialiasing);
              QGridLayout *mainLayout = new QGridLayout;
              mainLayout->addWidget(chartview, 1, 1);
              setLayout(mainLayout);
}

statistiques::~statistiques()
{
    delete ui;
}
