QT       += core gui
CONFIG+=debug
CONFIG+=qml_debug
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ConvexHull
TEMPLATE = app
greaterThan(QT_MAJOR_VERSION, 4){
CONFIG += c++11
} else {
QMAKE_CXXFLAGS += -std=c++0x
}

SOURCES += main.cpp\
        mainwindow.cpp \
    drawwidget.cpp \
    algorithms/jarvis.cpp \
    algorithms/graham.cpp \
    algorithms/divideandconquer.cpp

HEADERS  += mainwindow.h \
    drawwidget.h \
    algorithms/jarvis.h \
    algorithms/graham.h \
    common.h \
    algorithms/divideandconquer.h

FORMS    += mainwindow.ui

RESOURCES += \
     images.qrc
