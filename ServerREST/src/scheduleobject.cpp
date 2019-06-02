#include "scheduleobject.h"

extern ServeObject serve;

ScheduleObject::ScheduleObject(QObject *parent) : QObject(parent)
{
    this->init();
}

void ScheduleObject::init() {
    isReady = false;
    scheduleTimer = new QTimer(this);
    connect(scheduleTimer, SIGNAL(timeout()), this, SLOT(scheduleEvent()));
    scheduleTimer->start(1000);
}

/**
 * @brief 将room加入调度, 根据调度选择服务队列和等待队列
 * @param roomId
 */
void ScheduleObject::switchToServe(int roomId) {
    /* 临时策略*/
    if (serve_room.size() <= 3 ) {
        roominfo_t s;
        s.roomID = roomId;
        //s.windSpeed = serve.getRoom(roomId)->fanspeed;
        s.serveTimePoint = s.time = 0;
        //s.time = 10;
        serve_room.push_back(s);
    }
    else {
        roominfo_t w;
        w.roomID = roomId;
        //w.windSpeed = serve.getRoom(roomId)->fanspeed;
        w.time = 0;
        wait_room.push_back(w);
    }
}

/**
 * @brief
 * @param roomId
 * @param fanSpeed
 */
void ScheduleObject::updateFanspeed(int roomId, int fanSpeed) {
    QVector<roominfo_t>::iterator iter;
    for (iter = serve_room.begin(); iter != serve_room.end(); iter++) {
        if (iter->roomID == roomId) {
            serve.getRoom(roomId)->updateFee(iter->serveTimePoint-iter->time);
            iter->serveTimePoint = iter->time;
        }
    }

    serve.getRoom(roomId)->setFanSpeed(fanSpeed);
}

/**
 * @brief 关机时调离服务队列和等待队列,累计这段时间的
 * @param roomId
 */
void ScheduleObject::releaseRoom(int roomId) {
    int i = 0;
    bool isFind = false;
    for (i = 0; i < wait_room.size(); i++) {
        if (wait_room[i].roomID == roomId) {
            serve.getRoom(roomId)->updateFee(wait_room[i].serveTimePoint - wait_room[i].time);
            wait_room.remove(i);
            isFind = true;
        }
    }
    if (isFind) return;
    qDebug()<<"1\n";
    for (i = 0; i < serve_room.size(); i++) {
        if (serve_room[i].roomID == roomId) {
            qDebug()<<serve.getRoom(roomId)<<endl;
            serve.getRoom(roomId)->updateFee(serve_room[i].serveTimePoint - serve_room[i].time);
            serve_room.remove(i);
            isFind = true;
        }
    }
    qDebug()<<"2\n";
}

void ScheduleObject::deleteRoom(int roomId) {
    QVector<roominfo_t>::iterator iter;
    bool isFind = false;
    for (iter = wait_room.begin(); iter != wait_room.end(); iter++) {
        if (iter->roomID == roomId) {
            serve.getRoom(roomId)->updateFee(iter->serveTimePoint - iter->time);
            serve.deleteRoom(roomId);
            wait_room.erase(iter);
            isFind = true;
        }
    }
    if (isFind) return;

    for (iter = serve_room.begin(); iter != serve_room.end(); iter ++) {
        if (iter->roomID == roomId) {
            serve.getRoom(roomId)->updateFee(iter->serveTimePoint - iter->time);
            serve.deleteRoom(roomId);
            serve_room.erase(iter);
        }
    }
}

/**
 * @brief 更新房间温度
 * @param roomId
 * @param curTemp
 * @return
 */
QString ScheduleObject::updateCurTemp(int roomId, double curTemp) {
    /*还有问题*/
    serve.getRoom(roomId)->setCurTemp(curTemp);
    if (serve.getRoom(roomId)->isNeedSleep()) {
        releaseRoom(roomId);
        return QString("SLEEP");
    }
    if (serve.getRoom(roomId)->isNeedWake()) {
        switchToServe(roomId);
    }
    return serve.getRoom(roomId)->getState();
}

/**
 * @brief 调度函数 未确定
 * @param r
 */
void ScheduleObject::schedule(QJsonObject r) {

}

/**
 * @brief 定时器调用函数
 */
void ScheduleObject::scheduleEvent() {
    /*
     * 每分钟调度, 更新两个队列的time, 另外servetimepoint只上次风速调整时间.
     * 在等待队列里面, time 为负表示挂起状态,不更新,但检查当前温度和设定温度,来决定调度
     */
}
