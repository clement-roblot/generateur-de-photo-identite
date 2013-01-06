#-------------------------------------------------
#
# Project created by QtCreator 2013-01-06T20:36:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Generateur_de_photo_identitee
TEMPLATE = app

unix:INCLUDEPATH += /usr/include/
unix:INCLUDEPATH += /usr/local/lib/
unix:CONFIG += link_pkgconfig
unix:PKGCONFIG += opencv

SOURCES += main.cpp\
        mainwindow.cpp \
    refait.cpp \
    clicableqgraphicsview.cpp

HEADERS  += mainwindow.h \
    refait.h \
    clicableqgraphicsview.h

FORMS    += mainwindow.ui
