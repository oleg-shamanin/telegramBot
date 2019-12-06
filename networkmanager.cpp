#include "networkmanager.h"

NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
    NetworkManager::getUserList();
    connect(manager, &QNetworkAccessManager::finished,
            this, &NetworkManager::onResult);
    qDebug() << "start network manager";

}

//отправка запроса в api.telegram.org на получние информаци о необработанных сообщениях
void NetworkManager::getData()
{
    QUrl url("https://api.telegram.org/bot992251985:AAGv505wMQCqFDNJwZuOLnXooahqK8OnWdU/getUpdates");
    QUrlQuery query(url.query());
    query.addQueryItem("offset", update_id);
    url.setQuery(query);
    QNetworkRequest request;
    request.setUrl(url);
    manager->get(request);
    qDebug() << "getData" << update_id;
}

//отправка сообщения
void NetworkManager::sendMessage(QString chat_id, QString text)
{
    QUrl url("https://api.telegram.org/bot992251985:AAGv505wMQCqFDNJwZuOLnXooahqK8OnWdU/sendMessage");
    QUrlQuery query(url.query());
    query.addQueryItem("chat_id", chat_id);
    query.addQueryItem("text", text);
    url.setQuery(query);

    QNetworkRequest request;
    request.setUrl(url);
    manager->get(request);
    qDebug() << "sendMessage";
}

//загрузка из файла всех контактов, которые писали боту
void NetworkManager::getUserList()
{
    QFile file("user.txt");
    file.open(QIODevice::ReadOnly);
    while (!file.atEnd())
    {
        QString str = file.readLine().trimmed();
        QStringList lst = str.split("=");
        lst.removeAll("");
        qDebug() << lst;
        if (!lst.isEmpty())
        {
            QString stringId = lst.at(1);
            int id = stringId.toInt();
            users.insert(lst.at(0), id);
        }
    }
    emit getUser();
}

//запись контактов, которые писали боту
void NetworkManager::setUserList()
{
    QFile file("user.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&file);
    for(QMap<QString, int>::iterator itr = users.begin(); itr != users.end(); ++itr)
    {
        stream << itr.key() << "=" << itr.value() << endl;
    }
    file.close();
}

//парсинг ответа на url запрос
void NetworkManager::onResult(QNetworkReply *reply)
{
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject core = document.object();
    QJsonArray result = core.value("result").toArray();
    qDebug() << result;
    for(int i = 0; i < result.count() ; ++i){
        QJsonObject inResult = result.at(i).toObject();
        int up_id = inResult.value("update_id").toInt();
        up_id++;
        update_id = QString::number(up_id);

        QJsonObject message = inResult.value("message").toObject();
        QString text = message.value("text").toString();

        QJsonObject chat = message.value("chat").toObject();
        QString username = chat.value("username").toString();
        int id = chat.value("id").toInt();

        users.insert(username, id);

        QString fileName;
        QTextStream(&fileName) << id << ".txt";
        QFile file(fileName);
        file.open(QIODevice::Append | QIODevice::Text);
        QTextStream stream(&file);
        stream << username << ": " << text<< endl;
        file.close();

        qDebug() << username;
        qDebug() << id;
        qDebug() << text;
        qDebug() << update_id;
    }
    NetworkManager::setUserList();
    emit onReady();
    qDebug() << "onResult";
}

//возвращение списка контактов
QMap<QString, int> NetworkManager::getUsers()
{
    return users;
    qDebug() << "getUsers";
}
