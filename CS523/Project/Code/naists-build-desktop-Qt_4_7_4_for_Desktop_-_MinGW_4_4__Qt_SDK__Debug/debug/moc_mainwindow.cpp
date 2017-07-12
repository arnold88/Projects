/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Thu Dec 8 22:31:19 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../NAISTS/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      28,   11,   11,   11, 0x08,
      43,   11,   11,   11, 0x08,
      59,   11,   11,   11, 0x08,
      73,   11,   11,   11, 0x08,
      87,   11,   11,   11, 0x08,
     104,   11,   11,   11, 0x08,
     119,   11,   11,   11, 0x08,
     136,   11,   11,   11, 0x08,
     157,   11,   11,   11, 0x08,
     172,   11,   11,   11, 0x08,
     188,   11,   11,   11, 0x08,
     205,   11,   11,   11, 0x08,
     217,   11,   11,   11, 0x08,
     229,   11,   11,   11, 0x08,
     240,   11,   11,   11, 0x08,
     252,   11,   11,   11, 0x08,
     264,   11,   11,   11, 0x08,
     274,   11,   11,   11, 0x08,
     285,   11,   11,   11, 0x08,
     297,   11,   11,   11, 0x08,
     313,   11,   11,   11, 0x08,
     324,   11,   11,   11, 0x08,
     336,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0program_start()\0program_stop()\0"
    "program_pause()\0program_sub()\0"
    "fourfourtwo()\0fourthreethree()\0"
    "threefivetwo()\0threefourthree()\0"
    "fourfourtwodiamond()\0fivethreetwo()\0"
    "fourtwotwotwo()\0fourfouroneone()\0"
    "ballchase()\0zonalmark()\0wingplay()\0"
    "allattack()\0alldefend()\0counter()\0"
    "flatback()\0zonepress()\0totalfootball()\0"
    "dumpnrun()\0showclock()\0action()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
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
        case 0: program_start(); break;
        case 1: program_stop(); break;
        case 2: program_pause(); break;
        case 3: program_sub(); break;
        case 4: fourfourtwo(); break;
        case 5: fourthreethree(); break;
        case 6: threefivetwo(); break;
        case 7: threefourthree(); break;
        case 8: fourfourtwodiamond(); break;
        case 9: fivethreetwo(); break;
        case 10: fourtwotwotwo(); break;
        case 11: fourfouroneone(); break;
        case 12: ballchase(); break;
        case 13: zonalmark(); break;
        case 14: wingplay(); break;
        case 15: allattack(); break;
        case 16: alldefend(); break;
        case 17: counter(); break;
        case 18: flatback(); break;
        case 19: zonepress(); break;
        case 20: totalfootball(); break;
        case 21: dumpnrun(); break;
        case 22: showclock(); break;
        case 23: action(); break;
        default: ;
        }
        _id -= 24;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
