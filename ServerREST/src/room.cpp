#include "room.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include <QUuid>
#include <QDebug>
#include <QtSql>
#include "room.h"
#include "serveobject.h"
#include <Cutelyst/Plugins/Utils/Sql>

extern ServeObject serve;

//Room::Room(QObject *parent) : QObject(parent)
//{
//}

void Room::init() {
    serveTime = 0;
    targetTemp = 26;
    feerate = 0.08;
    mode = "HOT";
    fee = 0;
    qDebug()<<this->roomid<<endl;
    //requestList.clear();
}

bool Room::setRoomTemp(const int t) {
    this->targetTemp = t;
    return true;
}



/**
 * @brief 设置风速
 * @param fanspeed
 * @return 费率
 */
float Room::setFanSpeed(int fanspeed) {
    this-> fanspeed = fanspeed;
    switch (fanspeed) {
    case 1 : this->feerate = serve.feeRate_L; break;
    case 2 : this->feerate = serve.feeRate_M; break;
    case 3 : this->feerate = serve.feeRate_H; break;
    }
    return this->feerate;
}

float Room::getFee() {
    return this->fee;
}


int Room::getDuration() {
    return this->serveTime;
}

QString Room::getState() {
    return this->state;
}

QString Room::getMode() {
    return this->mode;
}

void Room::setCurTemp(int curtemp) {
    this->currentTemp = curtemp;
    if (mode == "HOT") {
        if (currentTemp <= targetTemp) {
            state = "SLEEP";
        }
    }
    else if (mode == "COOL") {
        if (currentTemp >= targetTemp) {
            state = "SLEEP";
        }
    }
}

bool Room::isNeedSleep() {
    return state == "SLEEP";
}

/**
 * @brief 每次获得一条详单记录
 * @param r
 * @return 超出返回false, 每超出返回true
 */
bool Room::getOneLineRecord(record_t *r) {
    static int line = 0;
    *r = this->serveRecord[line];
    line ++;
    if (line < serveRecord.size()) {
        return true;
    }
    else {
        line = 0;
        return false;
    }
}

/**
 * @brief 根据间隔计算时间
 * @param time
 */
void Room::updateFee(int time) {
    serveTime += time;
    fee += time*feerate;
}

/**
 * @brief 将报表记录更新进数据库
 */
void Room::saveReport() {

}
