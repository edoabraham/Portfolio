/****************************************************************************
** Meta object code from reading C++ file 'simulationgui.h'
**
** Created: Fri Jan 18 14:20:03 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "simulationgui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'simulationgui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SimulationGUI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      33,   14,   14,   14, 0x08,
      50,   14,   14,   14, 0x08,
      75,   14,   14,   14, 0x08,
      95,   14,   14,   14, 0x08,
     113,   14,   14,   14, 0x08,
     130,   14,   14,   14, 0x08,
     146,   14,   14,   14, 0x08,
     165,   14,   14,   14, 0x08,
     182,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SimulationGUI[] = {
    "SimulationGUI\0\0StartSimulation()\0"
    "StopSimulation()\0SetSimulationDirectory()\0"
    "LoadParamFromFile()\0SaveParamToFile()\0"
    "UpdateGasBoxes()\0UpdateGasComp()\0"
    "UpdateParameters()\0UpdateGUITimer()\0"
    "UpdateTime()\0"
};

void SimulationGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SimulationGUI *_t = static_cast<SimulationGUI *>(_o);
        switch (_id) {
        case 0: _t->StartSimulation(); break;
        case 1: _t->StopSimulation(); break;
        case 2: _t->SetSimulationDirectory(); break;
        case 3: _t->LoadParamFromFile(); break;
        case 4: _t->SaveParamToFile(); break;
        case 5: _t->UpdateGasBoxes(); break;
        case 6: _t->UpdateGasComp(); break;
        case 7: _t->UpdateParameters(); break;
        case 8: _t->UpdateGUITimer(); break;
        case 9: _t->UpdateTime(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SimulationGUI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SimulationGUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SimulationGUI,
      qt_meta_data_SimulationGUI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SimulationGUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SimulationGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SimulationGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SimulationGUI))
        return static_cast<void*>(const_cast< SimulationGUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SimulationGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
