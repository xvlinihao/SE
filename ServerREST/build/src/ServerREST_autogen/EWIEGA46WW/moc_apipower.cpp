/****************************************************************************
** Meta object code from reading C++ file 'apipower.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/apipower.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'apipower.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ApiPower_t {
    QByteArrayData data[10];
    char stringdata0[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ApiPower_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ApiPower_t qt_meta_stringdata_ApiPower = {
    {
QT_MOC_LITERAL(0, 0, 8), // "ApiPower"
QT_MOC_LITERAL(1, 9, 5), // "index"
QT_MOC_LITERAL(2, 15, 32), // ":Path:AutoArgs:ActionClass(REST)"
QT_MOC_LITERAL(3, 48, 9), // "index_PUT"
QT_MOC_LITERAL(4, 58, 8), // ":Private"
QT_MOC_LITERAL(5, 67, 10), // "index_POST"
QT_MOC_LITERAL(6, 78, 9), // "index_GET"
QT_MOC_LITERAL(7, 88, 0), // ""
QT_MOC_LITERAL(8, 89, 8), // "Context*"
QT_MOC_LITERAL(9, 98, 1) // "c"

    },
    "ApiPower\0index\0:Path:AutoArgs:ActionClass(REST)\0"
    "index_PUT\0:Private\0index_POST\0index_GET\0"
    "\0Context*\0c"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ApiPower[] = {

 // content:
       7,       // revision
       0,       // classname
       4,   14, // classinfo
       4,   22, // methods
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

 // methods: name, argc, parameters, tag, flags
       1,    1,   42,    7, 0x02 /* Public */,
       3,    1,   45,    7, 0x02 /* Public */,
       5,    1,   48,    7, 0x02 /* Public */,
       6,    1,   51,    7, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void ApiPower::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ApiPower *_t = static_cast<ApiPower *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->index((*reinterpret_cast< Context*(*)>(_a[1]))); break;
        case 1: _t->index_PUT((*reinterpret_cast< Context*(*)>(_a[1]))); break;
        case 2: _t->index_POST((*reinterpret_cast< Context*(*)>(_a[1]))); break;
        case 3: _t->index_GET((*reinterpret_cast< Context*(*)>(_a[1]))); break;
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
        }
    }
}

const QMetaObject ApiPower::staticMetaObject = {
    { &Controller::staticMetaObject, qt_meta_stringdata_ApiPower.data,
      qt_meta_data_ApiPower,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ApiPower::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ApiPower::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ApiPower.stringdata0))
        return static_cast<void*>(this);
    return Controller::qt_metacast(_clname);
}

int ApiPower::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Controller::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
