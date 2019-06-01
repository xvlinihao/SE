#include "apiac.h"
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

ApiAc::ApiAc(QObject *parent) : Controller(parent)
{
}

ApiAc::~ApiAc()
{
}

void ApiAc::index(Context *c)
{
    c->response()->body() = "Matched Controller::API in API.";
}


/*开机有疑问, datein 和dateout*/
/**
 * @brief 开机, 新建room,,根据room是否创建进行下一步操作
 * @param c
 * @param roomid
 */

void ApiAc::index_PUT(Context *c)
{
    if (!serve.isReady) return;
    qDebug()<<Q_FUNC_INFO;
    const QJsonDocument doc = c->request()->bodyData().toJsonDocument();
    const QJsonObject obj = doc.object();
    QString b=doc.toJson();
    QString roomid = obj.value(QStringLiteral("RoomId")).toString();
    RoomId_PUT(c,roomid);
}

void ApiAc::RoomId_PUT(Context *c,const QString &roomid)
{
    qDebug()<<Q_FUNC_INFO<<roomid;
    if (!serve.isReady) return;
    int roomId=roomid.toInt();
    const QJsonDocument doc = c->request()->bodyData().toJsonDocument();
    const QJsonObject obj = doc.object();

    if (!serve.isValid(roomId)) {
        /* roomid 不存在, 添加新的room, 并放入调度队列*/
        Room* newroom = new Room(roomId);
        serve.addNewRoom(newroom);
    }

    schedule.switchToServe(roomId); //执行调度

    bool isWait = serve.getRoom(roomId)->isWait;
    QJsonObject res;
    res.insert(QStringLiteral("State"), isWait ? QStringLiteral("wait") : QStringLiteral("ok"));
    res.insert(QStringLiteral("Mode"), serve.mode);
    res.insert(QStringLiteral("TargetTmp"), serve.default_targetTemp);
    res.insert(QStringLiteral("FeeRate"), serve.getRoom(roomId)->feerate);
    res.insert(QStringLiteral("Fee"), serve.getRoom(roomId)->fee);
    c->response()->setJsonObjectBody(res);

//    c->response()->setJsonObjectBody({
//                                         {QStringLiteral("State"),QStringLiteral("wait")},
//                                         {QStringLiteral("Mode"),QStringLiteral("COOL")},
//                                         {QStringLiteral("TargetTemp"),room->targetTemp},
//                                         {QStringLiteral("Feerate"),room->feerate},
//                                         {QStringLiteral("Fee"),room->fee}
//                                     });
    /*const QStringList uuids = s.childGroups();
    c->response()->setJsonArrayBody(QJsonArray::fromStringList(uuids));*/
}

/**
 * @brief 调整房间号温度
 * @param c
 */
void ApiAc::index_POST(Context *c) {
    if (!serve.isReady) return;
    const QJsonDocument doc = c->request()->bodyData().toJsonDocument();
    const QJsonObject obj = doc.object();
    QString b=doc.toJson();
    int roomId = obj.value(QStringLiteral("RoomId")).toInt();
    if (!serve.isValid(roomId)) {
        // warning to do
        return;
    }
    if (obj.contains(QStringLiteral("TargetTemp"))) {
        int setTemp = obj.value(QStringLiteral("TargetTemp")).toInt();
        bool isOk = serve.getRoom(roomId)->setRoomTemp(setTemp);
        QJsonObject res;
        res.insert(QStringLiteral("isOK"), isOk);
        c->response()->setJsonObjectBody(res);
    }
    else if (obj.contains(QStringLiteral("FanSpeed"))){
        int fanspeed = obj.value(QStringLiteral("FanSpeed")).toInt();
        schedule.updateFanspeed(roomId, fanspeed);
        //serve.getRoom(roomId)->setFanSpeed(fanspeed);
        float feerate = serve.getRoom(roomId)->feerate;
        //float feerate = serve.getRoom(roomId)->fanspeed = fanspeed;
        QJsonObject res;
        res.insert(QStringLiteral("FeeRate"), feerate);
        c->response()->setJsonObjectBody(res);
    }
}

/**
 * @brief 用户关机
 * @param c
 */
void ApiAc::index_DELETE(Context *c) {
    if (!serve.isReady) return;
    qDebug()<<Q_FUNC_INFO;
    const QJsonDocument doc = c->request()->bodyData().toJsonDocument();
    const QJsonObject obj = doc.object();
    QString b=doc.toJson();
    QString roomid = obj.value(QStringLiteral("RoomId")).toString();
    RoomId_DELETE(c,roomid);
}

void ApiAc::RoomId_DELETE(Context *c, const QString &roomid)
{
    qDebug()<<Q_FUNC_INFO<<roomid;
    if (!serve.isReady) return;

    const QJsonDocument doc = c->request()->bodyData().toJsonDocument();
    const QJsonObject obj = doc.object();
    QString b=doc.toJson();
    int roomId = obj.value(QStringLiteral("RoomId")).toInt();

    float fee = serve.getRoom(roomId)->getFee();
    int dur = serve.getRoom(roomId)->getDuration();

    schedule.releaseRoom(roomId);

    QJsonObject res;
    res.insert(QStringLiteral("Fee"), fee);
    res.insert(QStringLiteral("Duration"), dur);
    c->response()->setJsonObjectBody(res);
}

/**
 * @brief 查看费用, 返回费率和费用
 * @param c
 */
void ApiAc::index_GET(Context *c) {
    if (!serve.isReady) return;
    qDebug()<<Q_FUNC_INFO;
    const QJsonDocument doc = c->request()->bodyData().toJsonDocument();
    const QJsonObject obj = doc.object();
    QString b=doc.toJson();
    QString roomid = obj.value(QStringLiteral("RoomId")).toString();
    RoomId_GET(c,roomid);
}

void ApiAc::RoomId_GET(Context *c,const QString &roomid) {
    if (!serve.isReady) return;
    const QJsonDocument doc = c->request()->bodyData().toJsonDocument();
    const QJsonObject obj = doc.object();
    QString b=doc.toJson();
    int roomId = obj.value(QStringLiteral("RoomId")).toInt();

    float feerate = serve.getRoom(roomId)->feerate;
    float fee = serve.getRoom(roomId)->fee;

    QJsonObject res;
    res.insert(QStringLiteral("Fee"), fee);
    res.insert(QStringLiteral("FeeRate"), feerate);
    c->response()->setJsonObjectBody(res);
}

void ApiAc::RoomId(Context *c, const QString &roomid)
{
    qDebug()<<Q_FUNC_INFO<<roomid;
}

void ApiAc::RoomId_POST(Context *c, const QString &roomid)
{
    qDebug()<<Q_FUNC_INFO<<roomid;
}

