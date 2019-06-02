#include "apistate.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include <QUuid>
#include <QDebug>
#include <QtSql>
#include "room.h"
#include "serveobject.h"
#include "scheduleobject.h"
#include <Cutelyst/Plugins/Utils/Sql>
using namespace Cutelyst;

extern ServeObject serve;
extern ScheduleObject schedule;

ApiState::ApiState(QObject *parent) : Controller(parent)
{
}

ApiState::~ApiState()
{
}

void ApiState::index(Context *c)
{
    c->response()->body() = "Matched Controller::ApiState in ApiState.";
}
void ApiState::RoomId(Context *c, const QString &roomid)
{
    c->response()->body() = "Matched Controller::ApiState in ApiState.";
}
void ApiState::RoomId_GET(Context *c, const QString &roomid)
{
    if (!serve.isReady) return;
    const QJsonDocument doc = c->request()->bodyData().toJsonDocument(); qDebug()<<"state_get:"<<doc<<endl;
    const QJsonObject obj = doc.object();
    QString b=doc.toJson();
    qDebug()<<"room:"<<roomid<<endl;
    int roomId = roomid.toInt();
    qDebug()<<"roomid:"<<roomId<<endl;
    if (!serve.isValid(roomId)) return;
    Room* r = serve.getRoom(roomId);
    QString state = r->getState();
    double currentTemp = r->currentTemp;
    double targetTemp = r->targetTemp;
    double fee = r->fee;
    double feerate = r->feerate;
    int fanspeed = r->fanspeed;
    int dur = r->serveTime;

    QJsonObject res;
    res.insert(QStringLiteral("state"), state);
    res.insert(QStringLiteral("CurrentTemp"), currentTemp);
    res.insert(QStringLiteral("TargetTemp"), targetTemp);
    res.insert(QStringLiteral("fan"), fanspeed);
    res.insert(QStringLiteral("FeeRate"), feerate);
    res.insert(QStringLiteral("Fee"), fee);
    res.insert(QStringLiteral("Duration"), dur);
    c->response()->setJsonObjectBody(res);
}
