/****************************************************************************
** Meta object code from reading C++ file 'field.h'
**
** Created: Thu 9. Aug 11:36:12 2007
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
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      12,    8,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      38,   33,    7,    7, 0x0a,
      59,    7,    7,    7, 0x0a,
      72,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CField[] = {
    "CField\0\0x,y\0cellDetails(int,int)\0type\0"
    "setTypeView(QString)\0renewField()\0"
    "setZoom(int)\0"
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
        case 0: cellDetails((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: setTypeView((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: renewField(); break;
        case 3: setZoom((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CField::cellDetails(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
