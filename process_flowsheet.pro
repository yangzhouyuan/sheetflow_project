#-------------------------------------------------
#
# Project created by QtCreator 2017-02-28T10:49:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

TARGET = process_flowsheet
TEMPLATE = app


SOURCES += main.cc\
	sheetflow_main.cc \
    drag_widget.cc \
    drag_pixmap.cc \
    canvas.cc \
    canvas_scene.cc

HEADERS  += sheetflow_main.h \
    drag_widget.h \
    drag_pixmap.h \
    canvas.h \
    canvas_scene.h

FORMS    +=

RESOURCES +=

DISTFILES +=
