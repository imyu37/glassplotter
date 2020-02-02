/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata0[284];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "on_cellChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 12), // "catalogIndex"
QT_MOC_LITERAL(4, 40, 11), // "PlotOrLabel"
QT_MOC_LITERAL(5, 52, 15), // "on_comboChanged"
QT_MOC_LITERAL(6, 68, 5), // "index"
QT_MOC_LITERAL(7, 74, 23), // "on_checkBoxCurveChanged"
QT_MOC_LITERAL(8, 98, 10), // "checkState"
QT_MOC_LITERAL(9, 109, 22), // "on_lineEdit_textEdited"
QT_MOC_LITERAL(10, 132, 8), // "linetext"
QT_MOC_LITERAL(11, 141, 25), // "on_buttonResetViewClicked"
QT_MOC_LITERAL(12, 167, 30), // "on_menu_File_LoadAGF_Triggered"
QT_MOC_LITERAL(13, 198, 27), // "on_menu_Help_Abou_Triggered"
QT_MOC_LITERAL(14, 226, 18), // "contextMenuRequest"
QT_MOC_LITERAL(15, 245, 3), // "pos"
QT_MOC_LITERAL(16, 249, 17), // "showGlassProperty"
QT_MOC_LITERAL(17, 267, 16) // "createGlassTable"

    },
    "MainWindow\0on_cellChanged\0\0catalogIndex\0"
    "PlotOrLabel\0on_comboChanged\0index\0"
    "on_checkBoxCurveChanged\0checkState\0"
    "on_lineEdit_textEdited\0linetext\0"
    "on_buttonResetViewClicked\0"
    "on_menu_File_LoadAGF_Triggered\0"
    "on_menu_Help_Abou_Triggered\0"
    "contextMenuRequest\0pos\0showGlassProperty\0"
    "createGlassTable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x08 /* Private */,
       5,    1,   69,    2, 0x08 /* Private */,
       7,    1,   72,    2, 0x08 /* Private */,
       9,    1,   75,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    0,   79,    2, 0x08 /* Private */,
      13,    0,   80,    2, 0x08 /* Private */,
      14,    1,   81,    2, 0x08 /* Private */,
      16,    0,   84,    2, 0x08 /* Private */,
      17,    1,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_cellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->on_comboChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_checkBoxCurveChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_lineEdit_textEdited((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->on_buttonResetViewClicked(); break;
        case 5: _t->on_menu_File_LoadAGF_Triggered(); break;
        case 6: _t->on_menu_Help_Abou_Triggered(); break;
        case 7: _t->contextMenuRequest((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 8: _t->showGlassProperty(); break;
        case 9: _t->createGlassTable((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
