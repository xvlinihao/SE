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
    QString roomid = QString::number(obj.value(QStringLiteral("RoomId")).toInt());
    RoomId_PUT(c,roomid);
}

void ApiAc::RoomId_PUT(Context *c,const QString &roomid)
{
    qDebug()<<Q_FUNC_INFO<<roomid;
    if (!serve.isReady) {
        QJsonObject res;
        res.insert(QStringLiteral("State"), QStringLiteral("OFF"));
        c->response()->setJsonObjectBody(res);
        return;
    }
    int roomId=roomid.toInt();
    const QJsonDocument doc = c->request()->bodyData().toJsonDocument(); qDebug()<<"ac_put:"<<doc<<endl;
    const QJsonObject obj = doc.object();

    if (!serve.isValid(roomId)) {
        /* roomid 不存在, 添加新的room, 并放入调度队列*/
        Room* newroom = new Room(roomId);
        newroom->mode = serve.mode;
        newroom->setRoomTemp(serve.default_targetTemp);
        newroom->setFanSpeed(1);
        serve.addNewRoom(newroom);
    }

    serve.getRoom(roomId)->getReport()->updateTimesOnOff();
    serve.getRoom(roomId)->addRequestRecord();
    schedule.switchToServe(roomId); //执行调度


    QJsonObject res;
    res.insert(QStringLiteral("State"), serve.getRoom(roomId)->getState());
    res.insert(QStringLiteral("Mode"), serve.mode);
    res.insert(QStringLiteral("TargetTmp"), serve.default_targetTemp);
    res.insert(QStringLiteral("FeeRate"), serve.getRoom(roomId)->feerate);
    res.insert(QStringLiteral("Fee"), serve.getRoom(roomId)->fee);
    c->response()->setJsonObjectBody(res);
}

/**
 * @brief 调整房间号温度
 * @param c
 */
void ApiAc::index_POST(Context *c) {
    if (!serve.isReady) {
        QJsonObject res;
        res.insert(QStringLiteral("state"), QStringLiteral("OFF"));
        c->response()->setJsonObjectBody(res);
        return;
    }

    const QJsonDocument doc = c->request()->bodyData().toJsonDocument(); qDebug()<<"ac_post:"<<doc<<endl;
    const QJsonObject obj = doc.object();
    QString b=doc.toJson();
    int roomId = obj.value(QStringLiteral("RoomId")).toInt();

    serve.getRoom(roomId)->addRequestRecord();

    if (!serve.isValid(roomId)) {
        // warning to do
        qDebug()<<"no room "<<roomId<<endl;
        return;
    }
    if (obj.contains(QStringLiteral("TargetTemp"))) {
        double setTemp = obj.value(QStringLiteral("TargetTemp")).toInt();
        bool isOk = serve.getRoom(roomId)->setRoomTemp(setTemp);

        QJsonObject res;
        res.insert(QStringLiteral("isOK"), isOk);
        c->response()->setJsonObjectBody(res);
    }
    else if (obj.contains(QStringLiteral("FanSpeed"))){
        int fanspeed = obj.value(QStringLiteral("FanSpeed")).toInt();
        schedule.updateFanspeed(roomId, fanspeed);
        double feerate = serve.getRoom(roomId)->feerate;

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
    QString roomid = QString::number(obj.value(QStringLiteral("RoomId")).toInt());
    RoomId_DELETE(c,roomid);
}

void ApiAc::RoomId_DELETE(Context *c, const QString &roomid)
{
    qDebug()<<Q_FUNC_INFO<<roomid;
    qDebug()<<"ac_delete:"<<c->request()->bodyData().toJsonDocument()<<endl;
    if (!serve.isReady) return;

    int roomId = roomid.toInt();
    serve.getRoom(roomId)->addRequestRecord();
    double fee = serve.getRoom(roomId)->getFee();
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
    if (!serve.isReady) {
        QJsonObject res;
        res.insert(QStringLiteral("state"), QStringLiteral("OFF"));
        c->response()->setJsonObjectBody(res);
        return;
    }
    qDebug()<<Q_FUNC_INFO;
    const QJsonDocument doc = c->request()->bodyData().toJsonDocument();
    const QJsonObject obj = doc.object();
    QString b=doc.toJson();
    QString roomid = QString::number(obj.value(QStringLiteral("RoomId")).toInt());
    RoomId_GET(c,roomid);
}

void ApiAc::RoomId_GET(Context *c,const QString &roomid) {
    if (!serve.isReady) {
        QJsonObject res;
        res.insert(QStringLiteral("state"), QStringLiteral("OFF"));
        c->response()->setJsonObjectBody(res);
        return;
    }
    const QJsonDocument doc = c->request()->bodyData().toJsonDocument(); qDebug()<<"ac_get:"<<doc<<endl;
    const QJsonObject obj = doc.object();
    QString b=doc.toJson();
    int roomId = obj.value(QStringLiteral("RoomId")).toInt();
    serve.getRoom(roomId)->addRequestRecord();
    double feerate = serve.getRoom(roomId)->feerate;
    double fee = serve.getRoom(roomId)->fee;

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

void ApiAc::notify(Context *c)
{
    qDebug()<<Q_FUNC_INFO;
}

void ApiAc::notify_PUT(Context *c)
{
    const QJsonDocument doc = c->request()->bodyData().toJsonDocument(); qDebug()<<"ac_notify_put:"<<doc<<endl;
    const QJsonObject obj = doc.object();
    int roomId = obj.value(QStringLiteral("RoomId")).toInt();
    serve.getRoom(roomId)->addRequestRecord();

    double CurrentRoomTemp=obj.value(QStringLiteral("CurrentRoomTemp")).toDouble();

    Room* r = serve.getRoom(roomId);
    r->setCurTemp(CurrentRoomTemp);

    QJsonObject res;
    res.insert(QStringLiteral("state"), r->getState());
    c->response()->setJsonObjectBody(res);
}
