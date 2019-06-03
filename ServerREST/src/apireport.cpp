#include "apireport.h"
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

ApiReport::ApiReport(QObject *parent) : Controller(parent)
{
}

ApiReport::~ApiReport()
{
}

void ApiReport::index(Context *c)
{
    c->response()->body() = "Matched Controller::ApiReport in ApiReport.";
}
void ApiReport::RoomId(Context *c, const QString &roomid, const QString &TypeReport, const QString &date)
{
    qDebug()<<Q_FUNC_INFO<<roomid;
}
void ApiReport::RoomId_GET(Context *c, const QString &roomid, const QString &TypeReport, const QString &date)
{
    qDebug()<<"report_get:"<<c->request()->bodyData().toJsonDocument()<<endl;
    int roomId = roomid.toInt();
    int typeReport = TypeReport.toInt();
    int d = date.toInt();

    report_t r = serve.getRoomReport(roomId);

    QJsonObject res;
    res.insert(QStringLiteral("RoomId"), roomId);
    res.insert(QStringLiteral("TimesOfOnOff"), r.timesOnOff);
    res.insert(QStringLiteral("Duration"), r.duration);
    res.insert(QStringLiteral("TotalFee"), r.totalfee);
    res.insert(QStringLiteral("TimesOfDispatch"), r.timesDispatch);
    res.insert(QStringLiteral("NumberOfRDP"), r.timesRDP);
    res.insert(QStringLiteral("TimesOfChangeTemp"), r.timesChangeTemp);
    res.insert(QStringLiteral("TimesOfChangeFanSpeed"), r.timesChangeFanSpeed);

    c->response()->setJsonObjectBody(res);
}
