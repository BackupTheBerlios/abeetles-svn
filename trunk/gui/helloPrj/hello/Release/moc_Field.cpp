/****************************************************************************
** Meta object code from reading C++ file 'Field.h'
**
** Created: Thu 14. Jun 16:08:51 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Field.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Field.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_Field[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      13,    7,    6,    6, 0x05,

 // slots: signature, parameters, type, tag, flags
      31,    7,    6,    6, 0x0a,
      45,    6,    6,    6, 0x0a,
      57,    6,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Field[] = {
    "Field\0\0angle\0angleChanged(int)\0"
    "setAngle(int)\0startstop()\0moveRect()\0"
};

const QMetaObject Field::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Field,
      qt_meta_data_Field, 0 }
};

const QMetaObject *Field::metaObject() const
{
    return &staticMetaObject;
}

void *Field::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Field))
	return static_cast<void*>(const_cast< Field*>(this));
    return QWidget::qt_metacast(_clname);
}

int Field::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: angleChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setAngle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: startstop(); break;
        case 3: moveRect(); break;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Field::angleChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
