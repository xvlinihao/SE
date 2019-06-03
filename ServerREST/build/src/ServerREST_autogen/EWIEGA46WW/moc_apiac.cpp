/****************************************************************************
** Meta object code from reading C++ file 'apiac.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/apiac.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'apiac.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ApiAc_t {
    QByteArrayData data[20];
    char stringdata0[224];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ApiAc_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ApiAc_t qt_meta_stringdata_ApiAc = {
    {
QT_MOC_LITERAL(0, 0, 5), // "ApiAc"
QT_MOC_LITERAL(1, 6, 5), // "index"
QT_MOC_LITERAL(2, 12, 32), // ":Path:AutoArgs:ActionClass(REST)"
QT_MOC_LITERAL(3, 45, 9), // "index_PUT"
QT_MOC_LITERAL(4, 55, 8), // ":Private"
QT_MOC_LITERAL(5, 64, 10), // "index_POST"
QT_MOC_LITERAL(6, 75, 9), // "index_GET"
QT_MOC_LITERAL(7, 85, 12), // "index_DELETE"
QT_MOC_LITERAL(8, 98, 6), // "RoomId"
QT_MOC_LITERAL(9, 105, 10), // "RoomId_GET"
QT_MOC_LITERAL(10, 116, 13), // "RoomId_DELETE"
QT_MOC_LITERAL(11, 130, 10), // "RoomId_PUT"
QT_MOC_LITERAL(12, 141, 11), // "RoomId_POST"
QT_MOC_LITERAL(13, 153, 6), // "notify"
QT_MOC_LITERAL(14, 160, 33), // ":Local:AutoArgs:ActionClass(R..."
QT_MOC_LITERAL(15, 194, 10), // "notify_PUT"
QT_MOC_LITERAL(16, 205, 0), // ""
QT_MOC_LITERAL(17, 206, 8), // "Context*"
QT_MOC_LITERAL(18, 215, 1), // "c"
QT_MOC_LITERAL(19, 217, 6) // "roomid"

    },
    "ApiAc\0index\0:Path:AutoArgs:ActionClass(REST)\0"
    "index_PUT\0:Private\0index_POST\0index_GET\0"
    "index_DELETE\0RoomId\0RoomId_GET\0"
    "RoomId_DELETE\0RoomId_PUT\0RoomId_POST\0"
    "notify\0:Local:AutoArgs:ActionClass(REST)\0"
    "notify_PUT\0\0Context*\0c\0roomid"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ApiAc[] = {

 // content:
       8,       // revision
       0,       // classname
      12,   14, // classinfo
      12,   38, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,
       5,    4,
       6,    4,
       7,    4,
       8,    2,
       9,    4,
      10,    4,
      11,    4,
      12,    4,
      13,   14,
      15,    4,

 // methods: name, argc, parameters, tag, flags
       1,    1,   98,   16, 0x02 /* Public */,
       3,    1,  101,   16, 0x02 /* Public */,
       5,    1,  104,   16, 0x02 /* Public */,
       6,    1,  107,   16, 0x02 /* Public */,
       7,    1,  110,   16, 0x02 /* Public */,
       8,    2,  113,   16, 0x02 /* Public */,
       9,    2,  118,   16, 0x02 /* Public */,
      10,    2,  123,   16, 0x02 /* Public */,
      11,    2,  128,   16, 0x02 /* Public */,
      12,    2,  133,   16, 0x02 /* Public */,
      13,    1,  138,   16, 0x02 /* Public */,
      15,    1,  141,   16, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 17, QMetaType::QString,   18,   19,
    QMetaType::Void, 0x80000000 | 17, QMetaType::QString,   18,   19,
    QMetaType::Void, 0x80000000 | 17, QMetaType::QString,   18,   19,
    QMetaType::Void, 0x80000000 | 17, QMetaType::QString,   18,   19,
    QMetaType::Void, 0x80000000 | 17, QMetaType::QString,   18,   19,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 17,   18,

       0        // eod
};

void ApiAc::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ApiAc *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->index((*reinterpret_cast< Context*(*)>(_a[1]))); break;
        case 1: _t->index_PUT((*reinterpret_cast< Context*(*)>(_a[1]))); break;
        case 2: _t->index_POST((*reinterpret_cast< Context*(*)>(_a[1]))); break;
        case 3: _t->index_GET((*reinterpret_cast< Context*(*)>(_a[1]))); break;
        case 4: _t->index_DELETE((*reinterpret_cast< Context*(*)>(_a[1]))); break;
        case 5: _t->RoomId((*reinterpret_cast< Context*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->RoomId_GET((*reinterpret_cast< Context*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: _t->RoomId_DELETE((*reinterpret_cast< Context*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 8: _t->RoomId_PUT((*reinterpret_cast< Context*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 9: _t->RoomId_POST((*reinterpret_cast< Context*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 10: _t->notify((*reinterpret_cast< Context*(*)>(_a[1]))); break;
        case 11: _t->notify_PUT((*reinterpret_cast< Context*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Context* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Context* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Context* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Context* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Context* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Context* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Context* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Context* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Context* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Context* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Context* >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Context* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ApiAc::staticMetaObject = { {
    &Controller::staticMetaObject,
    qt_meta_stringdata_ApiAc.data,
    qt_meta_data_ApiAc,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ApiAc::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ApiAc::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ApiAc.stringdata0))
        return static_cast<void*>(this);
    return Controller::qt_metacast(_clname);
}

int ApiAc::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Controller::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
