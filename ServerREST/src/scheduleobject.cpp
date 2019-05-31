#include "scheduleobject.h"

extern ServeObject serve;

ScheduleObject::ScheduleObject(QObject *parent) : QObject(parent)
{
    this->init();
}

void ScheduleObject::init() {
    isReady = false;
}

void ScheduleObject::get_state_detail(int roomID, state_info* state) {
    // to do
}
