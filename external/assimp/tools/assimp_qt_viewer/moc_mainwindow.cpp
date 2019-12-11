/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata0[336];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "Paint_Finished"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 6), // "size_t"
QT_MOC_LITERAL(4, 34, 13), // "pPaintTime_ms"
QT_MOC_LITERAL(5, 48, 7), // "GLfloat"
QT_MOC_LITERAL(6, 56, 9), // "pDistance"
QT_MOC_LITERAL(7, 66, 18), // "SceneObject_Camera"
QT_MOC_LITERAL(8, 85, 5), // "pName"
QT_MOC_LITERAL(9, 91, 23), // "SceneObject_LightSource"
QT_MOC_LITERAL(10, 115, 22), // "on_butOpenFile_clicked"
QT_MOC_LITERAL(11, 138, 20), // "on_butExport_clicked"
QT_MOC_LITERAL(12, 159, 22), // "on_cbxLighting_clicked"
QT_MOC_LITERAL(13, 182, 8), // "pChecked"
QT_MOC_LITERAL(14, 191, 32), // "on_lstLight_itemSelectionChanged"
QT_MOC_LITERAL(15, 224, 20), // "on_lstCamera_clicked"
QT_MOC_LITERAL(16, 245, 11), // "QModelIndex"
QT_MOC_LITERAL(17, 257, 5), // "index"
QT_MOC_LITERAL(18, 263, 18), // "on_cbxBBox_clicked"
QT_MOC_LITERAL(19, 282, 7), // "checked"
QT_MOC_LITERAL(20, 290, 22), // "on_cbxTextures_clicked"
QT_MOC_LITERAL(21, 313, 22) // "on_cbxDrawAxes_clicked"

    },
    "MainWindow\0Paint_Finished\0\0size_t\0"
    "pPaintTime_ms\0GLfloat\0pDistance\0"
    "SceneObject_Camera\0pName\0"
    "SceneObject_LightSource\0on_butOpenFile_clicked\0"
    "on_butExport_clicked\0on_cbxLighting_clicked\0"
    "pChecked\0on_lstLight_itemSelectionChanged\0"
    "on_lstCamera_clicked\0QModelIndex\0index\0"
    "on_cbxBBox_clicked\0checked\0"
    "on_cbxTextures_clicked\0on_cbxDrawAxes_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x08 /* Private */,
       7,    1,   74,    2, 0x08 /* Private */,
       9,    1,   77,    2, 0x08 /* Private */,
      10,    0,   80,    2, 0x08 /* Private */,
      11,    0,   81,    2, 0x08 /* Private */,
      12,    1,   82,    2, 0x08 /* Private */,
      14,    0,   85,    2, 0x08 /* Private */,
      15,    1,   86,    2, 0x08 /* Private */,
      18,    1,   89,    2, 0x08 /* Private */,
      20,    1,   92,    2, 0x08 /* Private */,
      21,    1,   95,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Bool,   19,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Paint_Finished((*reinterpret_cast< const size_t(*)>(_a[1])),(*reinterpret_cast< const GLfloat(*)>(_a[2]))); break;
        case 1: _t->SceneObject_Camera((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->SceneObject_LightSource((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_butOpenFile_clicked(); break;
        case 4: _t->on_butExport_clicked(); break;
        case 5: _t->on_cbxLighting_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_lstLight_itemSelectionChanged(); break;
        case 7: _t->on_lstCamera_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 8: _t->on_cbxBBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_cbxTextures_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_cbxDrawAxes_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
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
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
