/****************************************************************************
** Meta object code from reading C++ file 'main_window.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "main_window.hpp"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[42];
    char stringdata0[218];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 11), // "openNewMenu"
QT_MOC_LITERAL(23, 0), // ""
QT_MOC_LITERAL(24, 8), // "saveFile"
QT_MOC_LITERAL(33, 10), // "saveFileAs"
QT_MOC_LITERAL(44, 8), // "loadFile"
QT_MOC_LITERAL(53, 13), // "cameraChanged"
QT_MOC_LITERAL(67, 5), // "value"
QT_MOC_LITERAL(73, 7), // "levelUp"
QT_MOC_LITERAL(81, 9), // "levelDown"
QT_MOC_LITERAL(91, 9), // "levelLeft"
QT_MOC_LITERAL(101, 10), // "levelRight"
QT_MOC_LITERAL(112, 9), // "updateMap"
QT_MOC_LITERAL(122, 11), // "runSettings"
QT_MOC_LITERAL(134, 7), // "runExec"
QT_MOC_LITERAL(142, 15), // "shutdownProgram"
QT_MOC_LITERAL(158, 11), // "procStopped"
QT_MOC_LITERAL(170, 8), // "exitcode"
QT_MOC_LITERAL(179, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(200, 6), // "status"
QT_MOC_LITERAL(207, 10) // "readStdout"

    },
    "MainWindow\0openNewMenu\0\0saveFile\0"
    "saveFileAs\0loadFile\0cameraChanged\0"
    "value\0levelUp\0levelDown\0levelLeft\0"
    "levelRight\0updateMap\0runSettings\0"
    "runExec\0shutdownProgram\0procStopped\0"
    "exitcode\0QProcess::ExitStatus\0status\0"
    "readStdout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  104,    2, 0x0a,    1 /* Public */,
       3,    0,  105,    2, 0x0a,    2 /* Public */,
       4,    0,  106,    2, 0x0a,    3 /* Public */,
       5,    0,  107,    2, 0x0a,    4 /* Public */,
       6,    1,  108,    2, 0x0a,    5 /* Public */,
       8,    0,  111,    2, 0x0a,    7 /* Public */,
       9,    0,  112,    2, 0x0a,    8 /* Public */,
      10,    0,  113,    2, 0x0a,    9 /* Public */,
      11,    0,  114,    2, 0x0a,   10 /* Public */,
      12,    1,  115,    2, 0x0a,   11 /* Public */,
      13,    0,  118,    2, 0x0a,   13 /* Public */,
      14,    0,  119,    2, 0x0a,   14 /* Public */,
      15,    0,  120,    2, 0x0a,   15 /* Public */,
      16,    2,  121,    2, 0x0a,   16 /* Public */,
      20,    0,  126,    2, 0x0a,   19 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 18,   17,   19,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->openNewMenu(); break;
        case 1: _t->saveFile(); break;
        case 2: _t->saveFileAs(); break;
        case 3: _t->loadFile(); break;
        case 4: _t->cameraChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->levelUp(); break;
        case 6: _t->levelDown(); break;
        case 7: _t->levelLeft(); break;
        case 8: _t->levelRight(); break;
        case 9: _t->updateMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->runSettings(); break;
        case 11: _t->runExec(); break;
        case 12: _t->shutdownProgram(); break;
        case 13: _t->procStopped((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 14: _t->readStdout(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t
, QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QProcess::ExitStatus, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
