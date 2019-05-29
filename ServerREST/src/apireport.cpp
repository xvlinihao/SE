#include "apireport.h"
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
    c->response()->body() ="wdnmd";
}
