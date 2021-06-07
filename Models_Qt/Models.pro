QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG +=sdk_no_version_check


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    choosecolor.cpp \
    main.cpp \
    mainwindow.cpp \
    sandpile.cpp \
    settings_dialog.cpp

HEADERS += \
    choosecolor.h \
    mainwindow.h \
    sandpile.h \
    settings_dialog.h

FORMS += \
    choosecolor.ui \
    mainwindow.ui \
    settings_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
