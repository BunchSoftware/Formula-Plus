/****************************************************************************
** Meta object code from reading C++ file 'mainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../forms/mainWindow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "onReportProblemTriggered",
    "",
    "onSuggestFeatureTriggered",
    "onGetReviewTriggered",
    "onAboutDocumentationTriggered",
    "onAboutProgramTriggered",
    "onLastProjectTriggered",
    "onOpenProjectTriggered",
    "onSaveProjectTriggered",
    "onCloseProjectTriggered",
    "onCreateProjectTriggered"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x02,    1 /* Public */,
       3,    0,   75,    2, 0x02,    2 /* Public */,
       4,    0,   76,    2, 0x02,    3 /* Public */,
       5,    0,   77,    2, 0x02,    4 /* Public */,
       6,    0,   78,    2, 0x02,    5 /* Public */,
       7,    0,   79,    2, 0x02,    6 /* Public */,
       8,    0,   80,    2, 0x02,    7 /* Public */,
       9,    0,   81,    2, 0x02,    8 /* Public */,
      10,    0,   82,    2, 0x02,    9 /* Public */,
      11,    0,   83,    2, 0x02,   10 /* Public */,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'onReportProblemTriggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSuggestFeatureTriggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onGetReviewTriggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onAboutDocumentationTriggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onAboutProgramTriggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onLastProjectTriggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onOpenProjectTriggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSaveProjectTriggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCloseProjectTriggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCreateProjectTriggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onReportProblemTriggered(); break;
        case 1: _t->onSuggestFeatureTriggered(); break;
        case 2: _t->onGetReviewTriggered(); break;
        case 3: _t->onAboutDocumentationTriggered(); break;
        case 4: _t->onAboutProgramTriggered(); break;
        case 5: _t->onLastProjectTriggered(); break;
        case 6: _t->onOpenProjectTriggered(); break;
        case 7: _t->onSaveProjectTriggered(); break;
        case 8: _t->onCloseProjectTriggered(); break;
        case 9: _t->onCreateProjectTriggered(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
