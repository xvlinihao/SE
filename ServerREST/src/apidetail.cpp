#include "apidetail.h"
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

ApiDetail::ApiDetail(QObject *parent) : Controller(parent)
{
}

ApiDetail::~ApiDetail()
{
}

void ApiDetail::index(Context *c)
{
    c->response()->body() = "Matched Controller::ApiDetail in ApiDetail.";
}
void ApiDetail::RoomId(Context *c, const QString &roomid)
{
    qDebug()<<Q_FUNC_INFO<<roomid;
}
void ApiDetail::RoomId_GET(Context *c, const QString &roomid)
{
    int roomId=roomid.toInt();
    const QJsonDocument doc = c->request()->bodyData().toJsonDocument();
    const QJsonObject obj = doc.object();

    int datein = obj.value("DateIn").toInt();
    int dateout = obj.value("DateOut").toInt();
    Room* r = serve.getRoom(roomId);
    record_t record;
    int i = 0;
    QJsonArray res;
    while (r->getOneLineRecord(&record)) {
        QJsonObject t;
        t.insert(QStringLiteral("RoomId"), roomId);
        t.insert(QStringLiteral("RequestTime"), record.requestime);
        t.insert(QStringLiteral("RequestDuration"), record.servetime);
        t.insert(QStringLiteral("FanSpeed"), record.fanspeed);
        t.insert(QStringLiteral("FeeRate"), record.feerate);
        t.insert(QStringLiteral("Fee"), record.fee);
        res.insert(i, QJsonValue(t));
    }

    c->response()->setJsonArrayBody(res);



}

