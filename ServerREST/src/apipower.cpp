#include "apipower.h"
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

ApiPower::ApiPower(QObject *parent) : Controller(parent)
{
}

ApiPower::~ApiPower()
{
}

void ApiPower::index(Context *c)
{
    c->response()->body() = "Matched Controller::ApiPower in ApiPower.";
}
void ApiPower::index_GET(Context *c)
{
    c->response()->body()="nmsl";
}
void ApiPower::index_PUT(Context *c)
{
    c->response()->body()="nmsl";
}
void ApiPower::index_POST(Context *c)
{
     c->response()->body()="nmsl";
}
