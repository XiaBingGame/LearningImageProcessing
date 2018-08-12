QT += core gui
# QT -= gui

CONFIG += c++11

TARGET = compute_pi
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += F:/Dependency/Include/opencv
LIBS += -LF:/Dependency/Lib/opencv
Release:LIBS +=opencv_core341.lib opencv_highgui341.lib opencv_imgproc341.lib opencv_imgcodecs341.lib opencv_video341.lib opencv_videoio341.lib
Debug:LIBS +=opencv_core341d.lib opencv_highgui341d.lib opencv_imgproc341d.lib opencv_imgcodecs341d.lib opencv_video341d.lib opencv_videoio341d.lib
