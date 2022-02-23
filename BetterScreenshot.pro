QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    PaintWidget/graphicsscene.cpp \
    PaintWidget/paintwidget.cpp \
    PaintWidget/stylepicker.cpp \
    misc/lock.cpp \
    misc/msgbox.cpp \
    areaselector.cpp \
    keyhandler.cpp \
    main.cpp \
    mainwindow.cpp \
    screenhandler.cpp \
    settings.cpp \
    tray.cpp

HEADERS += \
    PaintWidget/graphicsscene.h \
    PaintWidget/paintwidget.h \
    PaintWidget/stylepicker.h \
    misc/lock.h \
    misc/msgbox.h \
    misc/os.h \
    misc/log.h \
    areaselector.h \
    keyhandler.h \
    mainwindow.h \
    screenhandler.h \
    settings.h \
    tray.h

FORMS += \
    PaintWidget/paintwidget.ui \
    PaintWidget/stylepicker.ui \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -luser32
win32: RC_ICONS += icon/BS_256x256.ico

RESOURCES += \
    PaintWidget/resources.qrc \
    resource_file.qrc

DISTFILES += \
    PaintWidget/resources/cap.png \
    PaintWidget/resources/cat.jpg \
    PaintWidget/resources/join.png \
    PaintWidget/resources/style.png

SUBDIRS += \
    PaintWidget/PaintWidget.pro
