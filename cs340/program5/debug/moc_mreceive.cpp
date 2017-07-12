/****************************************************************************
** Meta object code from reading C++ file 'mreceive.h'
**
** Created: Thu Apr 29 23:55:57 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mreceive.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mreceive.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MReceive[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MReceive[] = {
    "MReceive\0\0MListen()\0"
};

const QMetaObject MReceive::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MReceive,
      qt_meta_data_MReceive, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MReceive::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MReceive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MReceive::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MReceive))
        return static_cast<void*>(const_cast< MReceive*>(this));
    return QDialog::qt_metacast(_clname);
}

int MReceive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: MListen(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
