/****************************************************************************
** Meta object code from reading C++ file 'mancala.h'
**
** Created: Thu Apr 29 23:57:39 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mancala.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mancala.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_mancala[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x08,
      50,    8,    8,    8, 0x08,
      82,    8,    8,    8, 0x08,
     110,    8,    8,    8, 0x08,
     149,    8,    8,    8, 0x08,
     193,    8,    8,    8, 0x08,
     210,    8,    8,    8, 0x08,
     227,    8,    8,    8, 0x08,
     244,    8,    8,    8, 0x08,
     261,    8,    8,    8, 0x08,
     278,    8,    8,    8, 0x08,
     295,    8,    8,    8, 0x08,
     312,    8,    8,    8, 0x08,
     329,    8,    8,    8, 0x08,
     346,    8,    8,    8, 0x08,
     364,    8,    8,    8, 0x08,
     382,    8,    8,    8, 0x08,
     400,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_mancala[] = {
    "mancala\0\0on_actionConnect_to_a_Server_triggered()\0"
    "on_actionTop_Scores_triggered()\0"
    "on_actionServer_triggered()\0"
    "on_actionAbout_LCD_Mancala_triggered()\0"
    "on_actionRules_and_Instructions_triggered()\0"
    "button1pressed()\0button2pressed()\0"
    "button3pressed()\0button4pressed()\0"
    "button5pressed()\0button6pressed()\0"
    "button7pressed()\0button8pressed()\0"
    "button9pressed()\0button10pressed()\0"
    "button11pressed()\0button12pressed()\0"
    "resetbutton()\0"
};

const QMetaObject mancala::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_mancala,
      qt_meta_data_mancala, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &mancala::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *mancala::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *mancala::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mancala))
        return static_cast<void*>(const_cast< mancala*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int mancala::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_actionConnect_to_a_Server_triggered(); break;
        case 1: on_actionTop_Scores_triggered(); break;
        case 2: on_actionServer_triggered(); break;
        case 3: on_actionAbout_LCD_Mancala_triggered(); break;
        case 4: on_actionRules_and_Instructions_triggered(); break;
        case 5: button1pressed(); break;
        case 6: button2pressed(); break;
        case 7: button3pressed(); break;
        case 8: button4pressed(); break;
        case 9: button5pressed(); break;
        case 10: button6pressed(); break;
        case 11: button7pressed(); break;
        case 12: button8pressed(); break;
        case 13: button9pressed(); break;
        case 14: button10pressed(); break;
        case 15: button11pressed(); break;
        case 16: button12pressed(); break;
        case 17: resetbutton(); break;
        default: ;
        }
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
