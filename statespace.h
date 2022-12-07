#ifndef STATESPACE_H
#define STATESPACE_H
#include <QDialog>
#include <QWidget>
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


namespace Ui {
class Statespace;
}

class Statespace : public QWidget
{
    Q_OBJECT

public:
    explicit Statespace(QWidget *parent = nullptr);
    ~Statespace();

    QChartView *chartView ;
    void choix_bar();

private:
    Ui::Statespace *ui;
};

#endif // STATESPACE_H
