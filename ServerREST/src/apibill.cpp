#include "apibill.h"
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

ApiBill::ApiBill(QObject *parent) : Controller(parent)
{
}

ApiBill::~ApiBill()
{
}

void ApiBill::index(Context *c)
{
    c->response()->body() = "Matched Controller::ApiBill in ApiBill.";
}
void ApiBill::RoomId(Context *c, const QString &roomid)
{
    qDebug()<<Q_FUNC_INFO<<roomid;
}
void ApiBill::RoomId_GET(Context *c, const QString &roomid)
{
    int roomId=roomid.toInt();
    const QJsonDocument doc = c->request()->bodyData().toJsonDocument();
    const QJsonObject obj = doc.object();

    int datein = serve.getRoom(roomId)->datein;
    int dateout = QDateTime::currentDateTime().toSecsSinceEpoch();
    int totalfee = serve.getRoom(roomId)->getFee();

    schedule.deleteRoom(roomId);

    QJsonObject res;
    res.insert(QStringLiteral("RoomId"), roomId);
    res.insert(QStringLiteral("TotalFee"), totalfee);
    res.insert(QStringLiteral("DateIn"), datein);
    res.insert(QStringLiteral("DateOut"), dateout);

    c->response()->setJsonObjectBody(res);
}
