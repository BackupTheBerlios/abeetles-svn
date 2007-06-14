/****************************************************************************
** Meta object code from reading C++ file 'SlidComp.h'
**
** Created: Thu 14. Jun 21:37:27 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SlidComp.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SlidComp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_SlidComp[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      19,   10,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      37,   10,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SlidComp[] = {
    "SlidComp\0\0newValue\0valueChanged(int)\0"
    "setValue(int)\0"
};

const QMetaObject SlidComp::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SlidComp,
      qt_meta_data_SlidComp, 0 }
};

const QMetaObject *SlidComp::metaObject() const
{
    return &staticMetaObject;
}

void *SlidComp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SlidComp))
	return static_cast<void*>(const_cast< SlidComp*>(this));
    return QWidget::qt_metacast(_clname);
}

int SlidComp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void SlidComp::valueChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
