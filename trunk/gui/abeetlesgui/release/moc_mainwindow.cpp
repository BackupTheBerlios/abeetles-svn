/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Wed 20. Jun 23:01:36 2007
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
       9,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      16,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      45,   11,   11,   11, 0x08,
      54,   11,   11,   11, 0x08,
      64,   11,   11,   11, 0x08,
      74,   11,   11,   11, 0x08,
      93,   86,   11,   11, 0x08,
     103,   86,   11,   11, 0x08,
     119,   11,   11,   11, 0x08,
     131,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0env\0envRefChanged(CEnvironment*)\0"
    "newEnv()\0openEnv()\0saveEnv()\0saveEnvAs()\0"
    "bStart\0run(bool)\0runNSteps(bool)\0"
    "make1Step()\0about()\0"
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
        case 1: newEnv(); break;
        case 2: openEnv(); break;
        case 3: saveEnv(); break;
        case 4: saveEnvAs(); break;
        case 5: run((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: runNSteps((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: make1Step(); break;
        case 8: about(); break;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::envRefChanged(CEnvironment * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
