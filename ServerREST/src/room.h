#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <QMap>
#include "serverrest.h"

#define hot "HOT"
#define cool "COOL"
#define ROOMCOUNT 6

typedef struct _record {
    int fanspeed;
    int servetime;
    double feerate;
    double fee;
    int requestime; //调度时更新
}record_t;

class Room : public QObject
{
    Q_OBJECT
public:
    //explicit Room(QObject *parent = nullptr);

    Room(int _roomid){roomid = _roomid; init();}

    void init(); // to do

    bool setRoomTemp(const double t);

    double setFanSpeed(int fanspeed); //to do

    void setCurTemp(double curtemp); // to do

    bool isNeedSleep();

    bool isNeedWake();

    double getFee(); // to do

    int getDuration(); // to do

    QString getState(); // to do

    QString getMode();

    bool getOneLineRecord(record_t* r); // to do

    void updateFee(int time); // to do

    void saveReport();

    int roomid;

    double fee;

    double currentTemp;

    QString mode;

    QString state;

    double feerate;

    double targetTemp;

    int serveTime;

    bool isWait;

    int fanspeed;

    QMap<int, record_t> serveRecord;

    int datein;

    int dateout;

signals:

public slots:
};

#endif // ROOM_H
