#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <QMap>

#define hot "HOT"
#define cool "COOL"
#define ROOMCOUNT 6

typedef struct _record {
    int fanspeed;
    int servetime;
}record_t;

class Room : public QObject
{
    Q_OBJECT
public:
    explicit Room(QObject *parent = nullptr);
    Room(int _roomid){roomid = _roomid; init();}
    void init(); // to do

    bool setRoomTemp(const int t);

    float setFanSpeed(int fanspeed); //to do

    float getFee(); // to do

    int getDuration(); // to do

    QString getState(); // to do

    int roomid;

    int fee;

    int currentTemp;

    QString mode;

    float feerate;
    /*what*/
    int targetTemp;

    int serveTime;

    bool isWait;

    int fanspeed;

    QMap<int, record_t> serveRecord;

signals:

public slots:
};

#endif // ROOM_H
