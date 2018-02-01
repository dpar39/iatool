#-------------------------------------------------
#
# Project created by QtCreator 2017-03-08T18:49:14
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = annotator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp\
    Common/utils.cpp \
    Model/annotatedimage.cpp \
    Model/singlepointannotation.cpp \
    Model/annotationbase.cpp \
    Model/imagecollectionmodel.cpp \
    Views/imagecollectionview.cpp \
    Views/mainview.cpp \
    Views/annotatedimageview.cpp \    
    editcoordinator.cpp

HEADERS  += \
    Common/utils.h \
    Common/common.h \
    Model/iannotation.h \
    Model/iannotatedimage.h \
    Model/annotatedimage.h \
    Model/annotationbase.h \
    Model/singlepointannotation.h \
    Model/imagecollectionmodel.h \
    Views/imagecollectionview.h \
    Views/annotatedimageview.h \
    Views/mainview.h \
    editcoordinator.h


FORMS += \
    Views/mainview.ui \
    Views/annotatedimageview.ui

tests {
    message(Running Tests build)
    QT += testlib
    TARGET = tests
    SOURCES -= main.cpp

    INCLUDEPATH += \
        Tests/gmock-1.7.0/include \
        Tests/gmock-1.7.0/gtest/include \
        Tests/gmock-1.7.0/ \
        Tests/gmock-1.7.0/gtest

    HEADERS += \
        Tests/testhelpers.h

    SOURCES += \
        Tests/*.cpp \
        Tests/gmock-1.7.0/src/gmock-all.cc \
        Tests/gmock-1.7.0/gtest/src/gtest-all.cc

} else {
    message(Running Normal build)
}
