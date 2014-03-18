#-------------------------------------------------
#
# Project created by QtCreator 2014-03-18T13:48:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = filetransfer
TEMPLATE = app


SOURCES += main.cpp\
        filetransfer.cpp \
    mylineedit.cpp \
    fileitemdelegate.cpp

HEADERS  += filetransfer.hpp \
    mylineedit.hpp \
    fileitemdelegate.hpp

FORMS    += filetransfer.ui

RESOURCES += \
    resources.qrc
