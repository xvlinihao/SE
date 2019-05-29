#include "apistate.h"
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
    c->response()->body() = "Matched Controller::ApiState in ApiState.";
}
