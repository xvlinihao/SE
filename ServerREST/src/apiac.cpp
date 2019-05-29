#include "apiac.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include <QUuid>
#include <QDebug>
#include <QtSql>
#include "room.h"
#include <Cutelyst/Plugins/Utils/Sql>
using namespace Cutelyst;

ApiAc::ApiAc(QObject *parent) : Controller(parent)
{
}

ApiAc::~ApiAc()
{
}

void ApiAc::index(Context *c)
{
    c->response()->body() = "Matched Controller::API in API.";
}
void ApiAc::index_PUT(Context *c)
{
    qDebug()<<Q_FUNC_INFO;
    const QJsonDocument doc = c->request()->bodyData().toJsonDocument();
    const QJsonObject obj = doc.object();
    QString b=doc.toJson();
    qDebug()<<"nmsl"+b;
    QSqlQuery query = CPreparedSqlQueryThreadForDB("SELECT * FROM book", "MyDB");
    if (query.exec()) {
        query.first();
        qDebug()<<"sql output"<<endl;
        qDebug()<<query.value(0).toString()<<endl;
        qDebug()<<query.value(1).toString()<<endl;
        qDebug()<<query.value(2).toString()<<endl;
        c->setStash("books", Sql::queryToHashList(query));
    }
    int roomid=obj.value(QStringLiteral("RoomId")).toInt();
    qDebug()<<roomid;
    const QString str=QString::number(roomid);
    RoomId_PUT(c,str);
}
void ApiAc::RoomId_PUT(Context *c,const QString &roomid)
{
    qDebug()<<Q_FUNC_INFO<<roomid;
    int roomId=roomid.toInt();
    const QJsonDocument doc = c->request()->bodyData().toJsonDocument();
    const QJsonObject obj = doc.object();
    QSettings s;
    s.beginGroup(roomid);
    s.setValue(QStringLiteral("RoomId"),obj.value(QStringLiteral("RoomId")).toInt());
    s.setValue(QStringLiteral("CurrentTemp"),obj.value(QStringLiteral("currentRoomTemp")).toInt());
    s.endGroup();
    s.sync();
    Room *room;
    room=new Room();
    room->setID(roomId);
    room->currentTemp=obj.value(QStringLiteral("currentRoomTemp")).toInt();
    c->response()->setJsonObjectBody({
                                         {QStringLiteral("State"),QStringLiteral("wait")},
                                         {QStringLiteral("Mode"),QStringLiteral("COOL")},
                                         {QStringLiteral("TargetTemp"),room->targetTemp},
                                         {QStringLiteral("Feerate"),room->feerate},
                                         {QStringLiteral("Fee"),room->fee}
                                     });
    /*const QStringList uuids = s.childGroups();
    c->response()->setJsonArrayBody(QJsonArray::fromStringList(uuids));*/
}
void ApiAc::RoomId(Context *c, const QString &roomid)
{
    qDebug()<<Q_FUNC_INFO<<roomid;
}
void ApiAc::RoomId_GET(Context *c, const QString &roomid)
{
    qDebug()<<Q_FUNC_INFO<<roomid;
    c->response()->body()="this is a room";
}
void ApiAc::RoomId_DELETE(Context *c, const QString &roomid)
{
    qDebug()<<Q_FUNC_INFO<<roomid;
}
void ApiAc::RoomId_POST(Context *c, const QString &roomid)
{
    qDebug()<<Q_FUNC_INFO<<roomid;
}
