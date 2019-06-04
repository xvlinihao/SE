#include "serveobject.h"
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
QMap<int, Room*> roomlist;

ServeObject::ServeObject(QObject *parent) : QObject(parent) {
    isReady = false;
}

/**
 * @brief 初始化配置信息
 * @param m 模式
 * @param t_hL 设定温度上限
 * @param t_lL 设定温度下限
 * @param d_tT  默认温度
 * @param fr_H  三阶费率
 * @param fr_M  二阶费率
 * @param fr_L  一阶费率
 */
bool ServeObject::init(QString m, int t_hL, int t_lL, int d_tT,
                  double fr_H, double fr_M, double fr_L)
{
    temp_highLimit = t_hL;
    temp_lowLimit = t_lL;
    default_targetTemp = d_tT;
    mode = m;
    feeRate_H = fr_H;
    feeRate_M = fr_M;
    feeRate_L = fr_L;
    if (d_tT > temp_highLimit || d_tT < temp_lowLimit) return false;
    return true;
}

bool ServeObject::setReady(bool isReady) {
    this->isReady = isReady;
    return this->isReady;
}

/**
 * @brief 获得房间的报表信息
 * @param roomId
 * @return
 */
report_t ServeObject::getRoomReport(const int roomId,int time,int type) {
    /*应该从数据库获得数据*/
    report_t t={0,0,0,0,0,0,0};
    t.roomId=roomId;
   QSqlQuery query = CPreparedSqlQueryThreadForDB("SELECT * FROM report WHERE datein>:time AND RoomId=:roomId", "MyDB");
   query.bindValue(":time",time);
   query.bindValue(":roomId",roomId);
   if (query.exec()) {
       while(query.next()){
           t.timesOnOff+=query.value(2).toInt();
           t.duration+=query.value(3).toInt();
           t.totalfee+=query.value(4).toFloat();
           t.timesDispatch+=query.value(5).toInt();
           t.timesRDP+=query.value(5).toInt();
           t.timesChangeTemp+=query.value(6).toInt();
           t.timesChangeFanSpeed+=query.value(7).toInt();
           qDebug()<<"datein:"<<query.value(0).toInt()<<query.value(1).toInt()<<query.value(2).toInt()<<query.value(3).toInt()
                  <<query.value(4).toFloat()<<query.value(5).toInt()<<query.value(6).toInt()<<query.value(7).toInt()<<query.value(8).toInt();
       }
   }

    return t;
}

bool ServeObject::isValid(const int roomid) {
    return roomlist.contains(roomid) && roomlist[roomid]->isHavePerson;
}

Room* ServeObject::getRoom(const int roomid) {
    if (!isValid(roomid)) return  nullptr;
    return roomlist[roomid];
}

bool ServeObject::addNewRoom(Room *newroom) {
    if (!newroom) return false;
    if (roomlist.contains(newroom->roomid)) delete roomlist[newroom->roomid];
    roomlist[newroom->roomid] = newroom;
    return true;
}

/**
 * @brief 删除一个房间,删除前保存report信息到数据库
 * @param roomId
 * @return
 */
bool ServeObject::deleteRoom(int roomId) {
    if (!isValid(roomId)) return false;
    roomlist[roomId]->saveReport();
    roomlist[roomId]->isHavePerson = false;
    //delete  roomlist[roomId];
    //roomlist.remove(roomId);
    return true;
}

/**
 * @brief 当服务对象满的时候进行调度的时候， 使用新的id顶替旧id
 *          并且转发请求，并且将服务时长保存
 * @param newRID 新请求的房间号
 * @param oldnewRID 旧请求的房间号
 * @param r 请求
 * @param serveTime 旧房间的服务时长
 * @return
 */
//bool ServeObject::dispatchRoom(int newRID, int oldRID, QJsonDocument r, int serveTime)
//{
//    if (newRID >= 0 && newRID <ROOMCOUNT)
//        servedMap[newRID] = true;
//    else
//        qDebug()<<"wrong newRID"<<endl;

//    if (oldRID >= 0 && oldRID < ROOMCOUNT)
//        servedMap[oldRID] = false;
//    else
//        qDebug()<<"wrong oldRID"<<endl;

//    rooms[oldRID].serveTime += serveTime;
//    do_request(newRID, r);
//    return true;
//}

/**
 * @brief 当服务对象未到上限时，直接为新房间分配
 * @param newRID
 * @param r
 * @return
 */
//bool ServeObject::dispatchRoom(int newRID, QJsonDocument r) {
//    if (newRID >= 0 && newRID <ROOMCOUNT)
//        servedMap[newRID] = true;
//    else
//        qDebug()<<"wrong newRID"<<endl;

//    servedCount ++;
//    do_request(newRID, r);
//    return true;
//}
