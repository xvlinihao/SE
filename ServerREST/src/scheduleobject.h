#ifndef SCHEDULEOBJECT_H
#define SCHEDULEOBJECT_H

#include <QObject>
#include <QList>
#include <QVector>
#include <QMap>
#include "serveobject.h"

typedef struct _ServeRoom {
    int roomID;
    int windSpeed;
    int serveTime;
    QJsonDocument r;
}ServeRoom;

typedef struct _WaitRoom {
    int roomID;
    int windSpeed;
    int waitTime;
    QJsonDocument r;
}WaitRoom;

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

    void getbill();//not understand

    void get_state_detail(int, state_info*);

    bool setReady(bool);

private:
    void init();

    QVector<WaitRoom> wait_room;

    QVector<ServeRoom> serve_room;
//    WaitRoom wait_rooms;

//    ServeRoom serve_rooms;

    bool isReady;

signals:
    void requestDispatch();
public slots:
};

#endif // SCHEDULEOBJECT_H
