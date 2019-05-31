#include "room.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include <QUuid>
#include <QDebug>
#include <QtSql>
#include "room.h"
#include <Cutelyst/Plugins/Utils/Sql>
Room::Room(QObject *parent) : QObject(parent)
{
    init();
}

void Room::init() {
    serveTime = 0;
    targetTemp = 26;
    feerate=0.08;
    mode=0;
    fee=0;
    requestList.clear();
}
