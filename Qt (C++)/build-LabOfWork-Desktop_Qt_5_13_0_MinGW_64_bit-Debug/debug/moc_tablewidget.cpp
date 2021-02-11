/****************************************************************************
** Meta object code from reading C++ file 'tablewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../LabOfWork/tablewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tablewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TableWidget_t {
    QByteArrayData data[10];
    char stringdata0[184];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TableWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TableWidget_t qt_meta_stringdata_TableWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TableWidget"
QT_MOC_LITERAL(1, 12, 24), // "WindowTable_InMainWindow"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 27), // "WindowTable_InPictureWindow"
QT_MOC_LITERAL(4, 66, 20), // "ClickedPictureWindow"
QT_MOC_LITERAL(5, 87, 17), // "ClickedMainWindow"
QT_MOC_LITERAL(6, 105, 15), // "OpenTableWindow"
QT_MOC_LITERAL(7, 121, 18), // "ClickedTableButton"
QT_MOC_LITERAL(8, 140, 19), // "ClickedDeleteButton"
QT_MOC_LITERAL(9, 160, 23) // "ClickedCalculatorButton"

    },
    "TableWidget\0WindowTable_InMainWindow\0"
    "\0WindowTable_InPictureWindow\0"
    "ClickedPictureWindow\0ClickedMainWindow\0"
    "OpenTableWindow\0ClickedTableButton\0"
    "ClickedDeleteButton\0ClickedCalculatorButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TableWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TableWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->WindowTable_InMainWindow(); break;
        case 1: _t->WindowTable_InPictureWindow(); break;
        case 2: _t->ClickedPictureWindow(); break;
        case 3: _t->ClickedMainWindow(); break;
        case 4: _t->OpenTableWindow(); break;
        case 5: _t->ClickedTableButton(); break;
        case 6: _t->ClickedDeleteButton(); break;
        case 7: _t->ClickedCalculatorButton(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TableWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TableWidget::WindowTable_InMainWindow)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TableWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TableWidget::WindowTable_InPictureWindow)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TableWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_TableWidget.data,
    qt_meta_data_TableWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TableWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TableWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int TableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void TableWidget::WindowTable_InMainWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TableWidget::WindowTable_InPictureWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
