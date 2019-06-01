#ifndef SCHEDULEOBJECT_H
#define SCHEDULEOBJECT_H

#include <QObject>
#include <QList>
#include <QVector>
#include <QMap>
#include <QTimer>
#include <QJsonObject>
#include "serveobject.h"

typedef struct _roominfo {
    int roomID;
    //int windSpeed;
    int serveTimePoint;
    int time;
    QJsonDocument r;
}roominfo_t;

//typedef struct _WaitRoom {
//    int roomID;
//    int windSpeed;
//    int waitTime;
//    QJsonDocument r;
//}WaitRoom;

class ScheduleObject : public QObject
{
    Q_OBJECT
public:
    explicit ScheduleObject(QObject *parent = nullptr);

    ~ScheduleObject(){}

    void schedule(QJsonObject r);//调度请求， 将请求加入wait或者serve队列

    void switchToServe(int roomId); // to do

    void updateFanspeed(int roomId, int fanSpeed); // to do

    void releaseRoom(int roomId);

    void deleteRoom(int roomId);
    //void dispatch(int rid, QJsonDocument r);//转给

    //void getbill();//not understand

    //void get_state_detail(int, state_info*);

    bool setReady(bool);

private:
    void init();

    QVector<roominfo_t> wait_room;

    QVector<roominfo_t> serve_room;
//    WaitRoom wait_rooms;

//    ServeRoom serve_rooms;

    bool isReady;

    QTimer* scheduleTimer;

signals:
    void requestDispatch();
public slots:
    void scheduleEvent();
};

#endif // SCHEDULEOBJECT_H
