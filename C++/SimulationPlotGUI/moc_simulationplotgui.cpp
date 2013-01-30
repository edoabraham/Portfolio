/****************************************************************************
** Meta object code from reading C++ file 'simulationplotgui.h'
**
** Created: Mon Jan 28 01:32:13 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "simulationplotgui.h"
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
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   19,   18,   18, 0x05,
      51,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      70,   18,   18,   18, 0x08,
      88,   18,   18,   18, 0x08,
     109,   18,   18,   18, 0x08,
     125,   19,   18,   18, 0x08,
     144,   19,   18,   18, 0x08,
     172,   18,   18,   18, 0x08,
     193,   18,   18,   18, 0x08,
     220,  214,   18,   18, 0x08,
     251,   19,   18,   18, 0x08,
     278,   18,   18,   18, 0x08,
     294,   18,   18,   18, 0x08,
     309,   19,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SimulationPlotGUI[] = {
    "SimulationPlotGUI\0\0value\0"
    "ChangedDirectory(QString)\0ChangedDirectory()\0"
    "UpdateDirectory()\0SearchForDirectory()\0"
    "RefreshGraphs()\0RefreshGraphs(int)\0"
    "UpdateSnapshotLineEdit(int)\0"
    "StartPlayingGraphs()\0UpdateLineEditData()\0"
    "width\0UpdateGraphResolution(QString)\0"
    "UpdateRefreshInterval(int)\0EnlargeGraphs()\0"
    "ShrinkGraphs()\0SetDirectory(QString)\0"
};

void SimulationPlotGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SimulationPlotGUI *_t = static_cast<SimulationPlotGUI *>(_o);
        switch (_id) {
        case 0: _t->ChangedDirectory((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->ChangedDirectory(); break;
        case 2: _t->UpdateDirectory(); break;
        case 3: _t->SearchForDirectory(); break;
        case 4: _t->RefreshGraphs(); break;
        case 5: _t->RefreshGraphs((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->UpdateSnapshotLineEdit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->StartPlayingGraphs(); break;
        case 8: _t->UpdateLineEditData(); break;
        case 9: _t->UpdateGraphResolution((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->UpdateRefreshInterval((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->EnlargeGraphs(); break;
        case 12: _t->ShrinkGraphs(); break;
        case 13: _t->SetDirectory((*reinterpret_cast< QString(*)>(_a[1]))); break;
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
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void SimulationPlotGUI::ChangedDirectory(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SimulationPlotGUI::ChangedDirectory()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
