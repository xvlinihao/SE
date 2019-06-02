#include "serverrest.h"
#include"apiac.h"
#include"apipower.h"
#include"apidetail.h"
#include"apibill.h"
#include"apireport.h"
#include "root.h"
#include"apistate.h"
#include "serveobject.h"
#include "scheduleobject.h"
#include <QtSql>
#include <Cutelyst/Plugins/Utils/Sql>
using namespace Cutelyst;

ServeObject serve;
ScheduleObject schedule;

ServerREST::ServerREST(QObject *parent) : Application(parent)
{
}

ServerREST::~ServerREST()
{
}

bool ServerREST::init()
{
    new Root(this);
    new ApiAc(this);
    new ApiBill(this);
    new ApiDetail(this);
    new ApiPower(this);
    new ApiReport(this);
    new ApiState(this);
    return true;
}
bool ServerREST::postFork()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", Sql::databaseNameThread("MyDB"));
    db.setDatabaseName("myapp.db");
    db.setConnectOptions("foreign_keys = ON");
    if (!db.open()) {
        qCritical() << "Failed to open database:" << db.lastError().text();
        return false;
    }
    return true;
}

