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
        int roomid;
        int fanspeed[3];//服务队列的风速
        int maxfan=0;
        int maxroom;
        int minfan=4;
        int minroom;
        int longest=0;
        int requestfan=serve.getRoom(roomId)->fanspeed;//请求的风速
        int replaceroomid;//要替换的房间的id
        int i,j;
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
        if(requestfan>maxfan){//如果请求风速大于服务队列最大风速
            if(fanspeed[1]!=fanspeed[2]&&fanspeed[1]!=fanspeed[3]&&fanspeed[2]!=fanspeed[3]){
                replaceroomid=minroom;
                roominfo_t r = serve_room[replaceroomid];
                serve_room.remove(replaceroomid);
                r.serveTimePoint = 0;
                r.time = 2;
                wait_room.push_back(r);
                roominfo_t r1;
                r1.serveTimePoint=10;
                r1.time=10;
                r1.roomID=roomId;
                serve_room.push_back(r1);
            }
            else{
                for(i=0;i<3;i++){
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
                roominfo_t r1;
                r1.serveTimePoint=10;
                r1.time=10;
                r1.roomID=roomId;
                serve_room.push_back(r1);
            }
        }
        else if(requestfan>minfan){
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
            roominfo_t r1;
            r1.serveTimePoint=10;
            r1.time=10;
            r1.roomID=roomId;
            serve_room.push_back(r1);
        }
        else if(requestfan==minfan){
            roominfo_t r1;
            r1.serveTimePoint=0;
            r1.time=2;
            r1.roomID=roomId;
            wait_room.push_back(r1);
        }
        else if(requestfan<minfan){
            roominfo_t r1;
            r1.serveTimePoint=0;
            r1.time=1000;
            r1.roomID=roomId;
            wait_room.push_back(r1);
        }
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
    int i = 0;
    bool isFind = false;
    for (i = 0; i < wait_room.size(); i++) {
        if (wait_room[i].roomID == roomId) {
            serve.getRoom(roomId)->updateFee(wait_room[i].serveTimePoint - wait_room[i].time);
            serve.deleteRoom(roomId);
            wait_room.remove(i);
            isFind = true;
        }
    }
    if (isFind) return;

    for (i = 0; i < serve_room.size(); i ++) {
        if (serve_room[i].roomID == roomId) {
            serve.getRoom(roomId)->updateFee(serve_room[i].serveTimePoint - serve_room[i].time);
            serve.deleteRoom(roomId);
            serve_room.remove(i);
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
    int i,j;
    int longest=0;
    int shortest=100;
    int sroom;
    int replaceroomid;
    for(i=0;i<serve_room.size()&&serve_room.size()>0;i++){
        serve_room[i].time--;
    }
    for(i=0;i<wait_room.size()&&wait_room.size()>0;i++){
        if(wait_room[i].time!=1000)
        {
            wait_room[i].time--;
            if(wait_room[i].time<shortest){
                shortest=wait_room[i].time;
                sroom=i;
            }
        }
    }
    for(i=0;i<wait_room.size()&&wait_room.size()>0;i++){
        if(wait_room[i].time==0){
            for(j=0;j<3&&serve_room.size()==3;j++){
                if(longest<(serve_room[j].serveTimePoint-serve_room[j].time))
                {
                    longest=serve_room[j].time;
                    replaceroomid=i;
                }
            }
            roominfo_t r = serve_room[replaceroomid];
            serve_room.remove(replaceroomid);
            r.serveTimePoint = 0;
            r.time = 2;
            wait_room.push_back(r);
            roominfo_t r1;
            r1.serveTimePoint=10;
            r1.time=10;
            r1.roomID=wait_room[i].roomID;
            serve_room.push_back(r1);
        }
    }
    if(serve_room.size()<3&&wait_room.size()>0){
        roominfo_t r1;
        r1.serveTimePoint=10;
        r1.time=10;
        r1.roomID=wait_room[sroom].roomID;
        serve_room.push_back(r1);
        wait_room.remove(sroom);
    }
}
