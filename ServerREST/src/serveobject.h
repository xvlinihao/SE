#ifndef SERVEOBJECT_H
#define SERVEOBJECT_H

#include <QObject>
#include <QVector>
#include <QJsonDocument>
#include <QDebug>
#include <QMap>
#include "room.h"

typedef struct _state_info {
    int state;
    int current_temp;
    int target_temp;
    double fan;
    double feeRate;
    double fee;
    int Duration;
}state_info;

class ServeObject : public QObject
{
    Q_OBJECT
public:
    explicit ServeObject(QObject *parent = nullptr);

    ~ServeObject(){}

    bool init(QString, int, int, int, double, double, double);

    bool setReady(bool);

    report_t getRoomReport(const int roomId,int time,int type); // to do

    bool isValid(const int roomid); // to do

    Room* getRoom(const int roomid); // to do

    bool addNewRoom(Room* newroom);//to do

    bool deleteRoom(int roomId); //to do

    int temp_lowLimit;

    int temp_highLimit;

    int default_targetTemp;

    QString mode;

    double feeRate_L;

    double feeRate_M;

    double feeRate_H;

    bool isReady;

signals:

public slots:
    void doRequest();
};

#endif // SERVEOBJECT_H
