#ifndef DIALOG_MAP_H
#define DIALOG_MAP_H

#include <QDialog>
#include <QSettings>
#include <QDataStream>
namespace Ui {
class dialog_map;
}

class dialog_map : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_map(QWidget *parent = nullptr);
    ~dialog_map();
private slots:
    void on_pushButton_Fermer_clicked();

private:
    Ui::dialog_map *ui;
};

#endif // DIALOG_MAP_H
