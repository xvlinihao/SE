#ifndef APIBILL_H
#define APIBILL_H

#include <Cutelyst/Controller>

using namespace Cutelyst;

class ApiBill : public Controller
{
    Q_OBJECT
public:
    explicit ApiBill(QObject *parent = nullptr);
    ~ApiBill();

    C_ATTR(index, :Path :AutoArgs)
    void index(Context *c);

    C_ATTR(RoomId, :Path :AutoArgs :ActionClass(REST))
    void RoomId(Context *c, const QString &roomid);

    C_ATTR(RoomId_GET, :Private)
    void RoomId_GET(Context *c,const QString &roomid);

};

#endif //APIBILL_H

