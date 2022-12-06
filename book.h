#ifndef BOOK_H
#define BOOK_H

#include <QDialog>
#include "mydb.h"


namespace Ui {
class book;
}

class book : public QDialog
{
    Q_OBJECT

public:
    explicit book(QWidget *parent = nullptr);
    ~book();
    void updateUI();

private slots:
    void on_btnBook_clicked();

private:
    Ui::book *ui;

signals:
 void mysignal();

};

#endif // BOOK_H
