#ifndef APIAC_H
#define APIAC_H

#include <Cutelyst/Controller>
using namespace Cutelyst;

class ApiAc : public Controller
{
    Q_OBJECT
public:
    explicit ApiAc(QObject *parent = nullptr);
    ~ApiAc();

    C_ATTR(index, :Path :AutoArgs :ActionClass(REST))
    void index(Context *c);
    
    C_ATTR(index_PUT, :Private)
    void index_PUT(Context *c);//开机

    C_ATTR(index_POST, :Private)
    void index_POST(Context *c);//调温和调风

    C_ATTR(index_GET, :Private)
    void index_GET(Context *c);//查看费用

    C_ATTR(index_DELETE, :Private)//关机
    void index_DELETE(Context *c);

    C_ATTR(RoomId, :Path :AutoArgs :ActionClass(REST))
    void RoomId(Context *c,const QString &roomid);

    C_ATTR(RoomId_GET, :Private)//房间的get信息
    void RoomId_GET(Context *c,const QString &roomid);

    C_ATTR(RoomId_DELETE, :Private)//房间信息清空
    void RoomId_DELETE(Context *c,const QString &roomid);

    C_ATTR(RoomId_PUT, :Private)//房间信息
    void RoomId_PUT(Context *c,const QString &roomid);

    C_ATTR(RoomId_POST, :Private)//
    void RoomId_POST(Context *c,const QString &roomid);

    C_ATTR(notify, :Local :AutoArgs :ActionClass(REST))
    void notify(Context *c);

    C_ATTR(notify_PUT, :Private)
    void notify_PUT(Context *c);
};

#endif //APIAC_H

