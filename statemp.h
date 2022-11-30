#ifndef STATEMP_H
#define STATEMP_H

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

#include "todolist.h"
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class statEmp;
}

class statEmp : public QDialog
{
    Q_OBJECT

public:
    explicit statEmp(QWidget *parent = nullptr);
    ~statEmp();

    QChartView *chartView ;
    void choix_pie();

private:
    Ui::statEmp *ui;
    ToDoList Tmp;
};

#endif // STATEMP_H
