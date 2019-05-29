#ifndef APIDETAIL_H
#define APIDETAIL_H

#include <Cutelyst/Controller>

using namespace Cutelyst;

class ApiDetail : public Controller
{
    Q_OBJECT
public:
    explicit ApiDetail(QObject *parent = nullptr);
    ~ApiDetail();

    C_ATTR(index, :Path :AutoArgs)
    void index(Context *c);

    C_ATTR(RoomId, :Path :AutoArgs :ActionClass(REST))
    void RoomId(Context *c, const QString &roomid);

    C_ATTR(RoomId_GET, :Private)
    void RoomId_GET(Context *c,const QString &roomid);
};

#endif //APIDETAIL_H

