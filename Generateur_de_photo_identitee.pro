#-------------------------------------------------
#Copyright (c) 2013 Clement Roblot
#
#
#This file is part of Generateur de photo d'identite.
#
#Generateur de photo d'identite is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#Generateur de photo d'identite is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with Generateur de photo d'identite.  If not, see <http://www.gnu.org/licenses/>.
#-------------------------------------------------


#-------------------------------------------------
#
# Project created by QtCreator 2013-01-06T20:36:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = generateur-de-photo-identite
TEMPLATE = app

unix:INCLUDEPATH += /usr/include/
unix:INCLUDEPATH += /usr/local/lib/
unix:CONFIG += link_pkgconfig
unix:PKGCONFIG += opencv

SOURCES += main.cpp\
        mainwindow.cpp \
    refait.cpp \
    clicableqgraphicsview.cpp \
    conceptionplanche.cpp \
    recadragephoto.cpp

HEADERS  += mainwindow.h \
    refait.h \
    clicableqgraphicsview.h \
    conceptionplanche.h \
    recadragephoto.h

FORMS    += mainwindow.ui \
    conceptionplanche.ui \
    recadragephoto.ui
