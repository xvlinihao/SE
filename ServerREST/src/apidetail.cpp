#include "apidetail.h"
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
    c->response()->body() = "Matched Controller::ApiDetail in ApiDetail.";
}

