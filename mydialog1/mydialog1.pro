#-------------------------------------------------
#
# Project created by QtCreator 2019-11-09T19:42:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mydialog1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        fivewidget.cpp \
        fourwidget.cpp \
        main.cpp \
        mywidget.cpp \
        subwidget.cpp \
        threewidget.cpp \
        twowidget.cpp

HEADERS += \
        fivewidget.h \
        fourwidget.h \
        mywidget.h \
        subwidget.h \
        threewidget.h \
        twowidget.h

FORMS += \
        mywidget.ui

win32 {
INCLUDEPATH += D:\opencv3\opencvqt\OpenCV_MinGW\include
CONFIG(debug, debug|release): {
LIBS += D:\opencv3\OpenCV-MinGW-Build-OpenCV-3.4.7\x86\mingw\bin\
    -llibopencv_core347 \
    -llibopencv_highgui347 \
    -llibopencv_imgcodecs347 \
    -llibopencv_imgproc347 \
    -llibopencv_features2d347 \
    -llibopencv_calib3d347\
    -llibopencv_videoio347\
    -llibopencv_video347\



} else:CONFIG(release, debug|release): {
LIBS += -LD:\opencv3\OpenCV-MinGW-Build-OpenCV-3.4.7\x86\mingw\bin \
    -llibopencv_core347 \
    -llibopencv_highgui347 \
    -llibopencv_imgcodecs347 \
    -llibopencv_imgproc347 \
    -llibopencv_features2d347 \
    -llibopencv_calib3d347 \
    -llibopencv_videoio347 \
    -llibopencv_video347


}
}


