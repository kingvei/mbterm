#-------------------------------------------------
#
# Project created by QtCreator 2016-03-16T15:28:24
#
#-------------------------------------------------

QT += core gui
QT += serialport
QT += qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MbTerm
TEMPLATE = app

SOURCES += main.cpp\
    mainwindow.cpp \
    serial/serialmodel.cpp \
    serial/serialview.cpp \
    terminal/view/widgets/radiogroup.cpp \
    terminal/view/consoleview.cpp \
    terminal/view/display/displaydelegate.cpp \
    terminal/view/consoledisplayview.cpp \
    terminal/view/senderview.cpp \
    terminal/view/serialstatusview.cpp \
    terminal/view/sendereofview.cpp \
    terminal/model/terminalsettings.cpp \
    terminal/terminal.cpp \
    terminal/crc/crc16.cpp

HEADERS  += mainwindow.h \
    serial/serialmodel.h \
    serial/serialview.h \
    terminal/view/widgets/radiogroup.h \
    terminal/view/consoleview.h \
    terminal/view/display/displaydelegate.h \
    terminal/view/consoledisplayview.h \
    terminal/view/senderview.h \
    terminal/view/serialstatusview.h \
    terminal/view/sendereofview.h \
    terminal/model/terminalsettings.h \
    terminal/terminal.h \
    terminal/crc/crc16.h

DISTFILES +=

DESTDIR=bin #Target file directory
OBJECTS_DIR=src #Intermediate object files directory
MOC_DIR=src_moc #Intermediate moc files directory
