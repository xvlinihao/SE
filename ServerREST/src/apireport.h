#ifndef APIREPORT_H
#define APIREPORT_H

#include <Cutelyst/Controller>

using namespace Cutelyst;

class ApiReport : public Controller
{
    Q_OBJECT
public:
    explicit ApiReport(QObject *parent = nullptr);
    ~ApiReport();

    C_ATTR(index, :Path :AutoArgs)
    void index(Context *c);
    C_ATTR(RoomId,:Path :AutoArgs :ActionClass(REST))
    void RoomId(Context *c,const QString &roomid, const QString &TypeReport, const QString &date);
    C_ATTR(RoomId_GET,:Private)
    void RoomId_GET(Context *c,const QString &roomid, const QString &TypeReport, const QString &date);
};

#endif //APIREPORT_H

