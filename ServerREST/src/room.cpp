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

#define TEMPSUB 5

extern ServeObject serve;

void Room::init() {
    serveTime = 0;
    targetTemp = 26;
    feerate = 0;
    fanspeed = 1;
    mode = "HOT";
    fee = 0;
    fanspeed=1;
    qDebug()<<this->roomid<<endl;
    //requestList.clear();
    isHavePerson = true;
    datein = QDateTime::currentDateTime().toSecsSinceEpoch();

    /*初始化具体房间的报表信息*/
    report.roomId = roomid;
    report.timesOnOff = 0;
    report.duration = 0;
    report.totalfee = 0;
    report.timesDispatch = 0;
    report.timesChangeTemp = 0;
    report.timesChangeFanSpeed = 0;
}

bool Room::setRoomTemp(const double t) {
    report.updateTimesChangeTemp();
    this->targetTemp = t;
    return true;
}


/**
 * @brief 设置风速
 * @param fanspeed
 * @return 费率
 */
double Room::setFanSpeed(int fanspeed) {
    report.updateTimesChangeFanSpeed();
    this-> fanspeed = fanspeed;
    switch (fanspeed) {
    case 1 : this->feerate = serve.feeRate_L; break;
    case 2 : this->feerate = serve.feeRate_M; break;
    case 3 : this->feerate = serve.feeRate_H; break;
    }
    return this->feerate;
}

double Room::getFee() {
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

void Room::setCurTemp(double curtemp) {
    int tmp  = currentTemp;
    this->currentTemp = curtemp;
    if (mode == "HOT") {
        if (tmp > currentTemp) {fee += (tmp - currentTemp);}
        if (currentTemp >= targetTemp) {
            state = "SLEEP";
        }
    }
    else if (mode == "COOL") {
        if (tmp < currentTemp) {fee += (currentTemp - tmp);}
        if (currentTemp <= targetTemp) {
            state = "SLEEP";
        }
    }
}

bool Room::isNeedSleep() {
    return state == "SLEEP";
}

bool Room::isNeedWake() {
    if (state != "SLEEP") return false;
    if (mode == "HOT" && currentTemp <= targetTemp - TEMPSUB) {
        return true;
    }
    else if (mode == "COOL" && currentTemp >= targetTemp - TEMPSUB) {
        return true;
    }
    return false;
}

/**
 * @brief 添加一条请求记录
 */
void Room::addRequestRecord() {
    int date = QDateTime::currentDateTime().toSecsSinceEpoch();
    record_t r;
    r.requestime = date;
    r.fee = fee;
    r.feerate = feerate;
    r.fanspeed = fanspeed;
    r.servetime = serveTime;
    serveRecord.insert(date, r);
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
//    report.updateTotalFee(fee);
//    report.updateDuration(time);
}


/**
 * @brief 将报表记录更新进数据库
 */
void Room::saveReport() {
    report.updateDuration(serveTime);
    report.updateTotalFee(fee);
    QSqlQuery query = CPreparedSqlQueryThreadForDB("INSERT INTO report VALUES(:datein,:RoomId,:TimesOfOnOff,:Duration,:TotalFee,:TimesOfDispatch,:NumberOfRDR,:TimesOfChangeTemp,:TimesOfChangeFanSpeed)", "MyDB");
    query.bindValue(":datein",datein);
    query.bindValue(":RoomId",report.roomId);
    query.bindValue(":TimesOfOnOff",report.timesOnOff);
    query.bindValue(":Duration",report.duration);
    query.bindValue(":TotalFee",report.totalfee);
    query.bindValue(":TimesOfDispatch",report.timesDispatch);
    query.bindValue(":NumberOfRDR",report.timesRDP);
    query.bindValue(":TimesOfChangeTemp",report.timesChangeTemp);
    query.bindValue(":TimesOfChangeFanSpeed",report.timesChangeFanSpeed);
    if (query.exec()) {
            query.first();
             qDebug()<<"datein:"<<query.value(0).toInt()<<query.value(1).toInt()<<query.value(2).toInt()<<query.value(3).toInt()
                    <<query.value(4).toFloat()<<query.value(5).toInt()<<query.value(6).toInt()<<query.value(7).toInt()<<query.value(8).toInt();
         }
}

/**
 * @brief 返回报表
 * @return
 */
report_t* Room::getReport() {
    return &report;
}
