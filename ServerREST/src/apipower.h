#ifndef APIPOWER_H
#define APIPOWER_H

#include <Cutelyst/Controller>

using namespace Cutelyst;

class ApiPower : public Controller
{
    Q_OBJECT
public:
    explicit ApiPower(QObject *parent = nullptr);
    ~ApiPower();

    C_ATTR(index, :Path :AutoArgs :ActionClass(REST))
    void index(Context *c);

    C_ATTR(index_PUT, :Private)
    void index_PUT(Context *c);//运行空调

    C_ATTR(index_POST, :Private)
    void index_POST(Context *c);//设置参数

    C_ATTR(index_GET, :Private)
    void index_GET(Context *c);//启动空调
};

#endif //APIPOWER_H

