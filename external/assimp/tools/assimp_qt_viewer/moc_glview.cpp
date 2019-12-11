/****************************************************************************
** Meta object code from reading C++ file 'glview.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "glview.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glview.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CGLView_t {
    QByteArrayData data[10];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CGLView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CGLView_t qt_meta_stringdata_CGLView = {
    {
QT_MOC_LITERAL(0, 0, 7), // "CGLView"
QT_MOC_LITERAL(1, 8, 14), // "Paint_Finished"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 6), // "size_t"
QT_MOC_LITERAL(4, 31, 13), // "pPaintTime_ms"
QT_MOC_LITERAL(5, 45, 7), // "GLfloat"
QT_MOC_LITERAL(6, 53, 9), // "pDistance"
QT_MOC_LITERAL(7, 63, 18), // "SceneObject_Camera"
QT_MOC_LITERAL(8, 82, 5), // "pName"
QT_MOC_LITERAL(9, 88, 23) // "SceneObject_LightSource"

    },
    "CGLView\0Paint_Finished\0\0size_t\0"
    "pPaintTime_ms\0GLfloat\0pDistance\0"
    "SceneObject_Camera\0pName\0"
    "SceneObject_LightSource"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CGLView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,
       7,    1,   34,    2, 0x06 /* Public */,
       9,    1,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,

       0        // eod
};

void CGLView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CGLView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Paint_Finished((*reinterpret_cast< const size_t(*)>(_a[1])),(*reinterpret_cast< const GLfloat(*)>(_a[2]))); break;
        case 1: _t->SceneObject_Camera((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->SceneObject_LightSource((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CGLView::*)(const size_t , const GLfloat );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CGLView::Paint_Finished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CGLView::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CGLView::SceneObject_Camera)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CGLView::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CGLView::SceneObject_LightSource)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CGLView::staticMetaObject = { {
    &QOpenGLWidget::staticMetaObject,
    qt_meta_stringdata_CGLView.data,
    qt_meta_data_CGLView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CGLView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CGLView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CGLView.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int CGLView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CGLView::Paint_Finished(const size_t _t1, const GLfloat _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CGLView::SceneObject_Camera(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CGLView::SceneObject_LightSource(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
