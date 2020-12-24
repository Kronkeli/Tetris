TEMPLATE = app
QT       += core widgets \
            virtualkeyboard

CONFIG += c++11
CONFIG -= app_bundle
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    View/enddialog.cpp \
    View/mainwindow.cpp \
    View/optionsdialog.cpp \
    View/nextblock.cpp \
    Model/gamearea.cpp \
    Model/blockmatrix.cpp \
    Model/tetromino.cpp

HEADERS += \
    View/enddialog.h \
    View/mainwindow.h \
    View/optionsdialog.h \
    View/nextblock.h \
    Model/blockmatrix.h \
    Model/gamearea.h \
    Model/tetromino.h
