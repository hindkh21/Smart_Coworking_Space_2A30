#ifndef GESTIONCLIENT_H
#define GESTIONCLIENT_H

#include <QMainWindow>

namespace Ui {
class gestionClient;
}

class gestionClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit gestionClient(QWidget *parent = nullptr);
    ~gestionClient();

private:
    Ui::gestionClient *ui;
};

#endif // GESTIONCLIENT_H
