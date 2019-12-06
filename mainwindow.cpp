#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    networkManager = new NetworkManager;
    networkManager->getData();
    connect(networkManager, &NetworkManager::onReady,
            this, &MainWindow::updateUserList);
    connect(networkManager, &NetworkManager::onReady,
            this, &MainWindow::updateMessegesList);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//отправка соббщения на сервер и запись в историю сообщений
void MainWindow::sendMessege(QString messege)
{
    ui->messegeLine->clear();
    networkManager->sendMessage(clickedUserId, messege);

    QFile file(messegesList);
    file.open(QIODevice::Append);
    QTextStream stream(&file);
    stream << "me: " << messege << endl;
    file.close();
    MainWindow::updateMessegesList();
}

//обновление списка друзей
void MainWindow::updateUserList()
{
    users = networkManager->getUsers();
    ui->userList->clear();
    for(QMap<QString, int>::iterator itr = users.begin(); itr != users.end(); ++itr)
    {
        QListWidgetItem* listItem = new QListWidgetItem;
        listItem->setText(itr.key());
        listItem->setData(Qt::UserRole, itr.value());
        qDebug() << listItem;
        ui->userList->addItem(listItem);
    }
}

//обновление отображаемых сообщений
void MainWindow::updateMessegesList()
{
    QFile file(messegesList);
    file.open(QIODevice::ReadOnly);
    ui->listMesseges->clear();
    while(!file.atEnd())
    {
        QString str = file.readLine();
        ui->listMesseges->addItem(str);
        ui->listMesseges->scrollToBottom();
    }

}

//обработка нажатий на лист контактов
void MainWindow::on_userList_itemClicked(QListWidgetItem *item)
{
    clickedUser = item->text();
    clickedUserId = item->data(Qt::UserRole).toString();
    messegesList = clickedUserId;
    messegesList.append(".txt");

    qDebug()<< clickedUser;
    qDebug()<< clickedUserId;


    MainWindow::updateMessegesList();
}

//обработка нажатий на кнопку отправить/обновить
void MainWindow::on_sendButton_clicked()
{
    QString messege = ui->messegeLine->text();
    if (!messege.isEmpty() && !clickedUserId.isEmpty())
    {
        MainWindow::sendMessege(messege);
    }
    else
    {
        networkManager->getData();
    }
}

