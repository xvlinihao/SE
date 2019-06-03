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
    scheduleTimer->start(30000);
}

/**
 * @brief 将room加入调度, 根据调度选择服务队列和等待队列
 * @param roomId
 */
void ScheduleObject::switchToServe(int roomId) {
    /* 临时策略*/
    if (serve_room.size()<3){
        roominfo_t s;
        s.roomID = roomId;
        //s.windSpeed = serve.getRoom(roomId)->fanspeed;
        s.serveTimePoint = s.time = 10;
        //s.time = 10;
        serve_room.push_back(s);
        qDebug()<<"现在有这么多个房间"<<serve_room.size();
        serve.getRoom(roomId)->state="ON";
        qDebug()<<"放入了服务队列"<<roomId;
    }
    else{
        roominfo_t w;
        w.roomID=roomId;
        w.serveTimePoint=w.time=2;
        wait_room.push_back(w);
        serve.getRoom(roomId)->state="WAIT";
        qDebug()<<"放入了等待队列"<<roomId;
    }
}

/**
 * @brief
 * @param roomId
 * @param fanSpeed
 */
void ScheduleObject::updateFanspeed(int roomId, int FanSpeed) {
    /*QVector<roominfo_t>::iterator iter;
    for (iter = serve_room.begin(); iter != serve_room.end(); iter++) {
        if (iter->roomID == roomId) {
            serve.getRoom(roomId)->updateFee(iter->serveTimePoint-iter->time);
            iter->serveTimePoint = iter->time;
        }
    }*/
    qDebug()<<Q_FUNC_INFO;
    serve.getRoom(roomId)->setFanSpeed(FanSpeed);
    int requestfan=FanSpeed;//请求的风速
    qDebug()<<requestfan<<"这是请求的风速";
    int roomid;
    int fanspeed[3];//服务队列的风速
    int maxfan=0;
    int maxroom;
    int minfan=4;
    int minroom;
    int longest=0;
    int replaceroomid;//要替换的房间的id
    int i,j;
    int flag=0;//用于判断房间是不是已经在服务队列里
    for(i=0;i<serve_room.size();i++){
        if(roomId==serve_room[i].roomID)
            flag=1;
    }
    if(flag==1){
        serve.getRoom(roomId)->setFanSpeed(FanSpeed);
    }
    else if(flag==0){//房间不在服务队列里
        qDebug()<<"房间不在服务队列里";
        for(i=0;i<3;i++){
            roomid=serve_room[i].roomID;
            fanspeed[i]=serve.getRoom(roomid)->fanspeed;
            if(maxfan<fanspeed[i]){
                maxfan=fanspeed[i];
                maxroom=i;
            }
            if(minfan>fanspeed[i]){
                minfan=fanspeed[i];
                minroom=i;
            }
        }
        qDebug()<<maxfan<<"这是max的风速";
        qDebug()<<minfan<<"这是min的风速";
        if(requestfan>=maxfan){//如果请求风速大于服务队列最大风速
             qDebug()<<"如果请求风速大于服务队列最大风速";
            if(fanspeed[1]!=fanspeed[2]&&fanspeed[1]!=fanspeed[3]&&fanspeed[2]!=fanspeed[3]){//服务队列风速不同
                replaceroomid=minroom;
                roominfo_t r = serve_room[replaceroomid];
                serve_room.remove(replaceroomid);
                r.serveTimePoint = 0;
                r.time = 2;
                wait_room.push_back(r);
                qDebug()<<"放入了wait队列"<<r.roomID;
                serve.getRoom(serve_room[replaceroomid].roomID)->state="WAIT";
                roominfo_t r1;
                r1.serveTimePoint=10;
                r1.time=10;
                r1.roomID=roomId;
                serve_room.push_back(r1);
                serve.getRoom(roomId)->state="ON";
                 qDebug()<<"放入了serve队列"<<roomId;
                for(i=0;i<wait_room.size();i++)
                    if(wait_room[i].roomID==roomId)
                        wait_room.remove(i);
            }
            else{
                for(i=0;i<3;i++){//服务队列风速有相同的
                    qDebug()<<"服务队列风速有相同的";
                    if(fanspeed[i]==minfan){
                        if(longest<(serve_room[i].serveTimePoint-serve_room[i].time))
                        {
                            longest=serve_room[i].time;
                            replaceroomid=i;
                        }
                    }
                }
                roominfo_t r = serve_room[replaceroomid];
                serve_room.remove(replaceroomid);
                r.serveTimePoint = 0;
                r.time = 2;
                wait_room.push_back(r);
                 qDebug()<<"放入了wait队列"<<r.roomID;
                serve.getRoom(serve_room[replaceroomid].roomID)->state="WAIT";
                roominfo_t r1;
                r1.serveTimePoint=10;
                r1.time=10;
                r1.roomID=roomId;
                serve_room.push_back(r1);
                serve.getRoom(roomId)->state="ON";
                for(i=0;i<wait_room.size();i++)
                    if(wait_room[i].roomID==roomId)
                        wait_room.remove(i);
                qDebug()<<"放入了服务队列"<<roomId;
            }
        }
        else if(requestfan>minfan){//大于服务队列某个对象的风速
            qDebug()<<"大于服务队列某个对象的风速";
            for(i=0;i<3;i++){
                if(fanspeed[i]<requestfan){
                    if(longest<(serve_room[i].serveTimePoint-serve_room[i].time))
                    {
                        longest=serve_room[i].time;
                        replaceroomid=i;
                    }
                }
            }
            roominfo_t r = serve_room[replaceroomid];
            serve_room.remove(replaceroomid);
            r.serveTimePoint = 0;
            r.time = 2;
            wait_room.push_back(r);
            qDebug()<<"放入了wait队列"<<roomId;
            serve.getRoom(serve_room[replaceroomid].roomID)->state="WAIT";
            roominfo_t r1;
            r1.serveTimePoint=10;
            r1.time=10;
            r1.roomID=roomId;
            serve_room.push_back(r1);
            for(i=0;i<wait_room.size();i++)
                if(wait_room[i].roomID==roomId)
                    wait_room.remove(i);
            serve.getRoom(roomId)->state="ON";

            qDebug()<<"放入了服务队列"<<roomId;
        }
        else if(requestfan==minfan){//时间片轮转
            qDebug()<<"//时间片轮转";
            roominfo_t r1;
            r1.serveTimePoint=0;
            r1.time=2;
            r1.roomID=roomId;
            wait_room.push_back(r1);
             qDebug()<<"放入了wait队列"<<roomId;
            serve.getRoom(roomId)->state="WAIT";
        }
        else if(requestfan<minfan){//等待释放对象
            qDebug()<<"//等待释放对象";
            roominfo_t r1;
            r1.serveTimePoint=0;
            r1.time=1000;
            r1.roomID=roomId;
            wait_room.push_back(r1);
             qDebug()<<"放入了wait队列"<<r1.roomID;
            serve.getRoom(roomId)->state="WAIT";
        }
    }
}

/**
 * @brief 关机时调离服务队列和等待队列,累计这段时间的
 * @param roomId
 */
void ScheduleObject::releaseRoom(int roomId) {
    qDebug()<<Q_FUNC_INFO;
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
    int i,j;
    int longest=0;
    int shortest=100;
    int sroom;
    int replaceroomid;
    for(i=0;i<serve_room.size()&&serve_room.size()>0;i++){//计算服务对象的服务时间
        serve_room[i].time--;
        qDebug()<<"服务时间--"<<serve_room[i].roomID<<serve_room[i].time;
        if(serve.getRoom(serve_room[i].roomID)->state=="SLEEP"||serve.getRoom(serve_room[i].roomID)->state=="OFF")
            serve_room.remove(i);
    }
    for(i=0;i<wait_room.size()&&wait_room.size()>0;i++){//计算等待队列的等待时间
        if(wait_room[i].time!=1000)
        {
            wait_room[i].time--;
            qDebug()<<"房间等待时间--"<<wait_room[i].roomID<<wait_room[i].time;
            if(wait_room[i].time<shortest){
                shortest=wait_room[i].time;
                sroom=i;
            }
            qDebug()<<"房间等待时间最小"<<wait_room[sroom].roomID<<shortest;
        }
    }
    for(i=0;i<wait_room.size()&&wait_room.size()>0;i++){//时间片轮转处理
         qDebug()<<"时间片轮转处理";
        if(wait_room[i].time==0){
            for(j=0;j<3&&serve_room.size()==3;j++){
                if(longest<(serve_room[j].serveTimePoint-serve_room[j].time))
                {
                    longest=serve_room[j].time;
                    replaceroomid=i;
                }
                 qDebug()<<"房间等待时间最大"<<wait_room[replaceroomid].roomID<<longest;
            }
            roominfo_t r = serve_room[replaceroomid];
            serve_room.remove(replaceroomid);
            r.serveTimePoint = 0;
            r.time = 2;
            wait_room.push_back(r);
            qDebug()<<"放入了wait队列"<<r.roomID;
            roominfo_t r1;
            r1.serveTimePoint=10;
            r1.time=10;
            r1.roomID=wait_room[i].roomID;
            serve_room.push_back(r1);
            serve.getRoom(r1.roomID)->state="ON";
            qDebug()<<"放入了服务队列"<<r1.roomID;
            for(j=0;j<wait_room.size();j++)
                if(wait_room[j].roomID==r1.roomID)
                    wait_room.remove(j);
        }
    }
    if(serve_room.size()<3&&wait_room.size()>0){
        roominfo_t r1;
        r1.serveTimePoint=10;
        r1.time=10;
        r1.roomID=wait_room[sroom].roomID;
        serve_room.push_back(r1);
        wait_room.remove(sroom);
        serve.getRoom(r1.roomID)->state="ON";
        qDebug()<<"放入了服务队列"<<r1.roomID;
    }
}
