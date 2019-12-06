#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>
#include <QFile>
#include <QUrl>
#include <QDebug>
#include <QTextStream>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>
#include <QJsonArray>
#include <QMap>
#include <QTextStream>
#include <QTime>



class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);

signals:
    void onReady();
    void getUser();

public slots:
    void getData();
    void sendMessage(QString chat_id, QString text);
    QMap<QString, int> getUsers();

private:
    QNetworkAccessManager* manager;
    void onResult(QNetworkReply *reply);
    void setUserList();
    void getUserList();

private:
    QMap<QString, int> users;
    QString update_id;
};

#endif // NETWORKMANAGER_H
