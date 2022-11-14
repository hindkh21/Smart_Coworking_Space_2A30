#ifndef MYCHAT_EMPLOYE_H
#define MYCHAT_EMPLOYE_H

#include <QWidget>
#include <QAbstractSocket>

class ChatEmp;
class QStandardItemModel;
namespace Ui {class MyChat_employe;}

class MyChat_employe : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(MyChat_employe)
public:
    explicit MyChat_employe(QWidget *parent = nullptr);
    ~MyChat_employe();

private:
    Ui::MyChat_employe *ui;
    ChatEmp *m_chatEmploye;
    QStandardItemModel *m_chatModel;
    QString m_lastUserName;

private slots:
    void attemptConnection();
    void connectedToServer();
    void attemptLogin(const QString &userName);
    void loggedIn();
    void loginFailed(const QString &reason);
    void messageReceived(const QString &sender, const QString &text);
    void sendMessage();
    void disconnectedFromServer();
    void userJoined(const QString &username);
    void userLeft(const QString &username);
    void error(QAbstractSocket::SocketError socketError);
};

#endif // MYCHAT_EMPLOYE_H
