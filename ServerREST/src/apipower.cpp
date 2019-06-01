#include "apipower.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include <QUuid>
#include <QDebug>
#include <QtSql>
#include <QString>
#include "room.h"
#include "serveobject.h"
#include "scheduleobject.h"
#include <Cutelyst/Plugins/Utils/Sql>
using namespace Cutelyst;

extern ServeObject serve;
extern ScheduleObject schedule;

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

/**
 * @brief 正式启动空调
 * @param c
 */
void ApiPower::index_GET(Context *c)
{
    serve.setReady(true);

    QJsonObject res;
    res.insert(QStringLiteral("state"), QStringLiteral("ready"));
}

/**
 * @brief 进入设置模式
 * @param c
 */
void ApiPower::index_PUT(Context *c)
{
    serve.setReady(false);

    QJsonObject res;
    res.insert(QStringLiteral("state"), QStringLiteral("SetMode"));
    c->response()->setJsonObjectBody(res);
}


/**
 * @brief 设置参数
 * @param c
 */
void ApiPower::index_POST(Context *c)
{
    bool isOk = false;
    if (serve.isReady) isOk = false;
    else {
        const QJsonDocument doc = c->request()->bodyData().toJsonDocument();
        const QJsonObject obj = doc.object();

        QString mode = obj.value("Mode").toString();
        int tempHighLimit = obj.value("TempHighLimit").toInt();
        int tempLowLimit = obj.value("TempLowLimit").toInt();
        int defaultTemp = obj.value("DefaultTargetTemp").toInt();
        float feerate_h = obj.value("FeeRateH").toDouble();
        float feerate_m = obj.value("FeeRateM").toDouble();
        float feerate_l = obj.value("FeeRateL").toDouble();

        isOk = serve.init(mode, tempHighLimit, tempLowLimit, defaultTemp, feerate_h, feerate_m, feerate_l);
    }

    QJsonObject res;
    res.insert(QStringLiteral("isOK"), isOk);
}
