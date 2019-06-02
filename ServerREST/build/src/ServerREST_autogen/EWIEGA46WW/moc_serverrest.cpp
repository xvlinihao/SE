/****************************************************************************
** Meta object code from reading C++ file 'serverrest.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/serverrest.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serverrest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ServerREST_t {
    QByteArrayData data[3];
    char stringdata0[19];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ServerREST_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ServerREST_t qt_meta_stringdata_ServerREST = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ServerREST"
QT_MOC_LITERAL(1, 11, 0), // ""
QT_MOC_LITERAL(2, 12, 6) // "parent"

    },
    "ServerREST\0\0parent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ServerREST[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       2,   18, // constructors
       0,       // flags
       0,       // signalCount

 // constructors: parameters
    0x80000000 | 1, QMetaType::QObjectStar,    2,
    0x80000000 | 1,

 // constructors: name, argc, parameters, tag, flags
       0,    1,   14,    1, 0x0e /* Public */,
       0,    0,   17,    1, 0x2e /* Public | MethodCloned */,

       0        // eod
};

void ServerREST::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { ServerREST *_r = new ServerREST((*reinterpret_cast< QObject*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        case 1: { ServerREST *_r = new ServerREST();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    }
    Q_UNUSED(_o);
}

QT_INIT_METAOBJECT const QMetaObject ServerREST::staticMetaObject = { {
    &Application::staticMetaObject,
    qt_meta_stringdata_ServerREST.data,
    qt_meta_data_ServerREST,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ServerREST::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServerREST::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ServerREST.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "org.cutelyst.CutelystApplicationInterface"))
        return static_cast< Cutelyst::Application*>(this);
    return Application::qt_metacast(_clname);
}

int ServerREST::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Application::qt_metacall(_c, _id, _a);
    return _id;
}

QT_PLUGIN_METADATA_SECTION
static constexpr unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', '!',
    // metadata version, Qt version, architectural requirements
    0, QT_VERSION_MAJOR, QT_VERSION_MINOR, qPluginArchRequirements(),
    0xbf, 
    // "IID"
    0x02,  0x6a,  'S',  'e',  'r',  'v',  'e',  'r', 
    'R',  'E',  'S',  'T', 
    // "className"
    0x03,  0x6a,  'S',  'e',  'r',  'v',  'e',  'r', 
    'R',  'E',  'S',  'T', 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN(ServerREST, ServerREST)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
