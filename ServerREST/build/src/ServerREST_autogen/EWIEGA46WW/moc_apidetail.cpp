/****************************************************************************
** Meta object code from reading C++ file 'apidetail.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/apidetail.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'apidetail.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ApiDetail_t {
    QByteArrayData data[11];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ApiDetail_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ApiDetail_t qt_meta_stringdata_ApiDetail = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ApiDetail"
QT_MOC_LITERAL(1, 10, 5), // "index"
QT_MOC_LITERAL(2, 16, 14), // ":Path:AutoArgs"
QT_MOC_LITERAL(3, 31, 6), // "RoomId"
QT_MOC_LITERAL(4, 38, 32), // ":Path:AutoArgs:ActionClass(REST)"
QT_MOC_LITERAL(5, 71, 10), // "RoomId_GET"
QT_MOC_LITERAL(6, 82, 8), // ":Private"
QT_MOC_LITERAL(7, 91, 0), // ""
QT_MOC_LITERAL(8, 92, 8), // "Context*"
QT_MOC_LITERAL(9, 101, 1), // "c"
QT_MOC_LITERAL(10, 103, 6) // "roomid"

    },
    "ApiDetail\0index\0:Path:AutoArgs\0RoomId\0"
    ":Path:AutoArgs:ActionClass(REST)\0"
    "RoomId_GET\0:Private\0\0Context*\0c\0roomid"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ApiDetail[] = {

 // content:
       8,       // revision
       0,       // classname
       3,   14, // classinfo
       3,   20, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,
       5,    6,

 // methods: name, argc, parameters, tag, flags
       1,    1,   35,    7, 0x02 /* Public */,
       3,    2,   38,    7, 0x02 /* Public */,
       5,    2,   43,    7, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8, QMetaType::QString,    9,   10,
    QMetaType::Void, 0x80000000 | 8, QMetaType::QString,    9,   10,

       0        // eod
};

void ApiDetail::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ApiDetail *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->index((*reinterpret_cast< Context*(*)>(_a[1]))); break;
        case 1: _t->RoomId((*reinterpret_cast< Context*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->RoomId_GET((*reinterpret_cast< Context*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
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
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ApiDetail::staticMetaObject = { {
    &Controller::staticMetaObject,
    qt_meta_stringdata_ApiDetail.data,
    qt_meta_data_ApiDetail,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ApiDetail::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ApiDetail::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ApiDetail.stringdata0))
        return static_cast<void*>(this);
    return Controller::qt_metacast(_clname);
}

int ApiDetail::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Controller::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
