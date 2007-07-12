/****************************************************************************
** Meta object code from reading C++ file 'zoomslider.h'
**
** Created: Thu 12. Jul 16:31:55 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../zoomslider.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zoomslider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_ZoomSlider[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      21,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      39,   12,   11,   11, 0x0a,
      59,   53,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ZoomSlider[] = {
    "ZoomSlider\0\0newValue\0valueChanged(int)\0"
    "setValue(int)\0isDis\0setDisabled(bool)\0"
};

const QMetaObject ZoomSlider::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ZoomSlider,
      qt_meta_data_ZoomSlider, 0 }
};

const QMetaObject *ZoomSlider::metaObject() const
{
    return &staticMetaObject;
}

void *ZoomSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ZoomSlider))
	return static_cast<void*>(const_cast< ZoomSlider*>(this));
    return QWidget::qt_metacast(_clname);
}

int ZoomSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: setDisabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ZoomSlider::valueChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
