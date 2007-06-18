/****************************************************************************
** Meta object code from reading C++ file 'field.h'
**
** Created: Mon 18. Jun 23:25:13 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../field.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'field.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_CField[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      14,    8,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,    8,    7,    7, 0x0a,
      46,    7,    7,    7, 0x0a,
      58,    7,    7,    7, 0x0a,
      74,   69,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CField[] = {
    "CField\0\0angle\0angleChanged(int)\0"
    "setAngle(int)\0startstop()\0moveRect()\0"
    "type\0setTypeView(QString)\0"
};

const QMetaObject CField::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CField,
      qt_meta_data_CField, 0 }
};

const QMetaObject *CField::metaObject() const
{
    return &staticMetaObject;
}

void *CField::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CField))
	return static_cast<void*>(const_cast< CField*>(this));
    return QWidget::qt_metacast(_clname);
}

int CField::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        case 4: setTypeView((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CField::angleChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
