/****************************************************************************
** Meta object code from reading C++ file 'DockCollimator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../example/DockCollimator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DockCollimator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DockCollimator_t {
    QByteArrayData data[10];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DockCollimator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DockCollimator_t qt_meta_stringdata_DockCollimator = {
    {
QT_MOC_LITERAL(0, 0, 14), // "DockCollimator"
QT_MOC_LITERAL(1, 15, 10), // "updateSize"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 16), // "updateParameters"
QT_MOC_LITERAL(4, 44, 13), // "updateSection"
QT_MOC_LITERAL(5, 58, 11), // "sizeUpdated"
QT_MOC_LITERAL(6, 70, 16), // "parameterUpdated"
QT_MOC_LITERAL(7, 87, 14), // "sectionUpdated"
QT_MOC_LITERAL(8, 102, 17), // "convergentClicked"
QT_MOC_LITERAL(9, 120, 16) // "divergentClicked"

    },
    "DockCollimator\0updateSize\0\0updateParameters\0"
    "updateSection\0sizeUpdated\0parameterUpdated\0"
    "sectionUpdated\0convergentClicked\0"
    "divergentClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DockCollimator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    1,   60,    2, 0x08 /* Private */,
       9,    1,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void DockCollimator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DockCollimator *_t = static_cast<DockCollimator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateSize(); break;
        case 1: _t->updateParameters(); break;
        case 2: _t->updateSection(); break;
        case 3: _t->sizeUpdated(); break;
        case 4: _t->parameterUpdated(); break;
        case 5: _t->sectionUpdated(); break;
        case 6: _t->convergentClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->divergentClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DockCollimator::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DockCollimator::updateSize)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DockCollimator::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DockCollimator::updateParameters)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (DockCollimator::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DockCollimator::updateSection)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject DockCollimator::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_DockCollimator.data,
      qt_meta_data_DockCollimator,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DockCollimator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DockCollimator::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DockCollimator.stringdata0))
        return static_cast<void*>(const_cast< DockCollimator*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int DockCollimator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void DockCollimator::updateSize()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void DockCollimator::updateParameters()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void DockCollimator::updateSection()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
