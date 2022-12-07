#ifndef CANCEL_H
#define CANCEL_H

#include <QDialog>
#include <QWidget>
#include "mydb.h"

namespace Ui {
class cancel;
}

class cancel : public QDialog
{
    Q_OBJECT

public:
    explicit cancel(QWidget *parent = nullptr);
    ~cancel();
    void updateUI();

private slots:
    void on_btnCancel_clicked();

private:
    Ui::cancel *ui
    ;
signals:
 void mysignal1();
};

#endif // CANCEL_H

