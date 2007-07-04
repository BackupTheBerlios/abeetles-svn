/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Wed 4. Jul 17:31:40 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_MainWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      16,   12,   11,   11, 0x05,
      52,   45,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      69,   11,   11,   11, 0x08,
      78,   11,   11,   11, 0x08,
      88,   11,   11,   11, 0x08,
      98,   11,   11,   11, 0x08,
     117,  110,   11,   11, 0x08,
     127,  110,   11,   11, 0x08,
     143,   11,   11,   11, 0x08,
     161,  155,   11,   11, 0x08,
     181,   11,   11,   11, 0x08,
     197,   11,   11,   11, 0x08,
     213,   11,   11,   11, 0x08,
     233,  229,   11,   11, 0x08,
     258,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0env\0envRefChanged(CEnvironment*)\0"
    "isNull\0envIsEmpty(bool)\0newEnv()\0"
    "openEnv()\0saveEnv()\0saveEnvAs()\0bStart\0"
    "run(bool)\0runNSteps(bool)\0make1Step()\0"
    "value\0DisplayChanged(int)\0saveAggrStats()\0"
    "saveTimeStats()\0saveHistStats()\0x,y\0"
    "showCellDetails(int,int)\0about()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

const QMetaObject *MainWindow::metaObject() const
{
    return &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
	return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: envRefChanged((*reinterpret_cast< CEnvironment*(*)>(_a[1]))); break;
        case 1: envIsEmpty((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: newEnv(); break;
        case 3: openEnv(); break;
        case 4: saveEnv(); break;
        case 5: saveEnvAs(); break;
        case 6: run((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: runNSteps((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: make1Step(); break;
        case 9: DisplayChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: saveAggrStats(); break;
        case 11: saveTimeStats(); break;
        case 12: saveHistStats(); break;
        case 13: showCellDetails((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: about(); break;
        }
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::envRefChanged(CEnvironment * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::envIsEmpty(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
