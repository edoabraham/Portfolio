/****************************************************************************
** Meta object code from reading C++ file 'simulationplotgui.h'
**
** Created: Wed Oct 31 03:57:55 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../simulationplotgui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'simulationplotgui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SimulationPlotGUI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,
      41,   35,   18,   18, 0x08,
      60,   35,   18,   18, 0x08,
      88,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SimulationPlotGUI[] = {
    "SimulationPlotGUI\0\0RefreshGraphs()\0"
    "value\0RefreshGraphs(int)\0"
    "UpdateSnapshotLineEdit(int)\0"
    "StartPlayingGraphs()\0"
};

void SimulationPlotGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SimulationPlotGUI *_t = static_cast<SimulationPlotGUI *>(_o);
        switch (_id) {
        case 0: _t->RefreshGraphs(); break;
        case 1: _t->RefreshGraphs((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->UpdateSnapshotLineEdit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->StartPlayingGraphs(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SimulationPlotGUI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SimulationPlotGUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SimulationPlotGUI,
      qt_meta_data_SimulationPlotGUI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SimulationPlotGUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SimulationPlotGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SimulationPlotGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SimulationPlotGUI))
        return static_cast<void*>(const_cast< SimulationPlotGUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SimulationPlotGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
