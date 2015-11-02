#------------------------------------------------------------------------
#
# Project generated by The Emerger from emergent.io
#
# Sun Nov 1 19:50:55 2015
#
# Conner Lacy <conner@emergent.io>
#
#------------------------------------------------------------------------
#
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sketch_000
TEMPLATE = app

QMAKE_MAC_SDK = macosx10.11

SOURCES += main.cpp\
mainwindow.cpp \
sketch_000_Canvas.cpp

HEADERS  += mainwindow.h \
sketch_000_Canvas.h

FORMS    += mainwindow.ui

OTHER_FILES += \
sketch_000_Shader.frag \
sketch_000_Shader.vert

EIO_SDK_QT_PATH =/Users/connerlacy/Documents/emergent.io/Repositories/eio_qte/sdk
include($$EIO_SDK_QT_PATH/eio_qte.pri)
