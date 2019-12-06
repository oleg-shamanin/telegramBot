#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrlQuery>
#include <QFile>
#include <QListWidgetItem>
#include <QVariant>

#include <networkmanager.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_sendButton_clicked();
    void updateUserList();
    void updateMessegesList();
    void on_userList_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    NetworkManager* networkManager;


    void sendMessege(QString messege);

    QMap<QString, int> users;
    QString clickedUser;
    QString clickedUserId;
    QString messegesList;

};

#endif // MAINWINDOW_H
