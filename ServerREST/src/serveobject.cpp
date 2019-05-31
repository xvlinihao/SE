#include "serveobject.h"

static QMap<int, Room*> roomlist;

ServeObject::ServeObject(QObject *parent) : QObject(parent)
{
    servedCount = 0;
    isReady = false;
    for (int i = 0; i <ROOMCOUNT; i++) {
        servedMap[i] = false;
    }
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
void ServeObject::init(int m, int t_hL, int t_lL, int d_tT,
                  double fr_H, double fr_M, double fr_L)
{
    temp_highLimit = t_hL;
    temp_lowLimit = t_lL;
    default_targetTemp = d_tT;
    mode = m;
    feeRate_H = fr_H;
    feeRate_M = fr_M;
    feeRate_L = fr_L;
}

bool ServeObject::setReady(bool isReady) {
    this->isReady = isReady;
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
bool ServeObject::dispatchRoom(int newRID, int oldRID, QJsonDocument r, int serveTime)
{
    if (newRID >= 0 && newRID <ROOMCOUNT)
        servedMap[newRID] = true;
    else
        qDebug()<<"wrong newRID"<<endl;

    if (oldRID >= 0 && oldRID < ROOMCOUNT)
        servedMap[oldRID] = false;
    else
        qDebug()<<"wrong oldRID"<<endl;

    rooms[oldRID].serveTime += serveTime;
    do_request(newRID, r);
    return true;
}

/**
 * @brief 当服务对象未到上限时，直接为新房间分配
 * @param newRID
 * @param r
 * @return
 */
bool ServeObject::dispatchRoom(int newRID, QJsonDocument r) {
    if (newRID >= 0 && newRID <ROOMCOUNT)
        servedMap[newRID] = true;
    else
        qDebug()<<"wrong newRID"<<endl;

    servedCount ++;
    do_request(newRID, r);
    return true;
}

/**
 * @brief 旧房间和服务对象断开连接
 * @param oldRID
 */
void ServeObject::releaseRoom(int oldRID, int serveTime) {
    rooms[oldRID].serveTime += serveTime;
    servedCount --;
}

/**
 * @brief 根据Qjson的内容处理rid房间
 * @param rid
 * @param r
 */
void ServeObject::do_request(int rid, QJsonDocument r) {
    // to do
}

/**
 * @brief 获取给定rid房间号的房间信息
 * @param rid
 * @param s
 */
bool ServeObject::get_fee_and_feerate(int rid, state_info *s) {
    // to do
}
