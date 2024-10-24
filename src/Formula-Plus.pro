QT += core printsupport gui quick charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++21

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    forms\calculateForm.cpp \
    forms\errorForm.cpp \
    forms\mainWindow.cpp \
    forms\physicalCalculateForm.cpp \
    forms\plottingForm.cpp \
    forms\aboutWindow.cpp \
    forms\familiarizationForm.cpp \
    main.cpp \
    forms\parserForm.cpp \

HEADERS += \
    forms\calculateForm.h \
    forms\errorForm.h \
    forms\mainWindow.h \
    forms\physicalCalculateForm.h \
    forms\plottingForm.h \
    forms\aboutWindow.h \
    forms\familiarizationForm.h \
    library/equationInterpreter.h \
    library\interpreter.h \
    forms\parserForm.h \
    library\physicInterpreter.h \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource\images.qrc \
    resource\qml.qrc \


