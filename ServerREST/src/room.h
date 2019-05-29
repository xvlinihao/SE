#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <QVector>
class Room : public QObject
{
    Q_OBJECT
public:
    explicit Room(QObject *parent = nullptr);
    int roomid;

    void init();
    void setID(int ROOMID);
    int fee;

    int currentTemp;

    int mode;

    float feerate;

    int targetTemp;

    int serveTime;

    QVector<QString> requestList;

signals:

public slots:
};

#endif // ROOM_H
