#include "apibill.h"
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
    c->response()->body() = "Matched Controller::ApiBill in ApiBill.";
}
