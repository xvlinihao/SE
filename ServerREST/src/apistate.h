#ifndef APISTATE_H
#define APISTATE_H

#include <Cutelyst/Controller>

using namespace Cutelyst;

class ApiState : public Controller
{
    Q_OBJECT
public:
    explicit ApiState(QObject *parent = nullptr);
    ~ApiState();

    C_ATTR(index, :Path :AutoArgs )
    void index(Context *c);

    C_ATTR(RoomId, :Path :AutoArgs :ActionClass(REST))
    void RoomId(Context *c, const QString &roomid);

    C_ATTR(RoomId_GET, :Private)
    void RoomId_GET(Context *c,const QString &roomid);
};

#endif //APISTATE_H

