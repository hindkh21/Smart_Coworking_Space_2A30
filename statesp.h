#ifndef STATESP_H
#define STATESP_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE
namespace Ui {
class statEsp;
}

class statEsp : public QDialog
{
    Q_OBJECT

public:
    explicit statEsp(QWidget *parent = nullptr);
    ~statEsp();

    QChartView *chartView ;
    void choix_bar();

private:
    Ui::statEsp *ui;
};

#endif // STATESP_H



