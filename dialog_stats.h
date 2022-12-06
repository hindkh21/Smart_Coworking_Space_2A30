#ifndef DIALOG_STATS_H
#define DIALOG_STATS_H

#include <QWidget>
#include "QtPrintSupport"

namespace Ui {
class dialog_stats;
}

class dialog_stats : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_stats(QWidget *parent = nullptr);
    ~dialog_stats();

private:
    Ui::dialog_stats *ui;
    void MakeStat();
        void statistiques(QVector<double>* ticks,QVector<QString> *labels);
};

#endif // DIALOG_STATS_H
