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
    QVector<roominfo_t>::iterator iter;
    bool isFind = false;
    for (iter = wait_room.begin(); iter != wait_room.end(); iter++) {
        if (iter->roomID == roomId) {
            serve.getRoom(roomId)->updateFee(iter->serveTimePoint - iter->time);
            wait_room.erase(iter);
            isFind = true;
        }
    }
    if (isFind) return;

    for (iter = serve_room.begin(); iter != serve_room.end(); iter ++) {
        if (iter->roomID == roomId) {
            serve.getRoom(roomId)->updateFee(iter->serveTimePoint - iter->time);
            serve_room.erase(iter);
        }
    }
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
