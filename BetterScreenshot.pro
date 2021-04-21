QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    PaintKEK_Widget/graphicsscene.cpp \
    PaintKEK_Widget/paintkek.cpp \
    PaintKEK_Widget/stylepicker.cpp \
    drawdialog.cpp \
    drawlabel.cpp \
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
    PaintKEK_Widget/graphicsscene.h \
    PaintKEK_Widget/paintkek.h \
    PaintKEK_Widget/stylepicker.h \
    drawdialog.h \
    drawlabel.h \
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
    PaintKEK_Widget/paintkek.ui \
    PaintKEK_Widget/stylepicker.ui \
    mainwindow.ui

LIBS += -luser32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    PaintKEK_Widget/resources.qrc \
    resource_file.qrc

win32:RC_ICONS += icon/BS_256x256.ico

DISTFILES += \
    PaintKEK_Widget/resources/cap.png \
    PaintKEK_Widget/resources/cat.jpg \
    PaintKEK_Widget/resources/join.png \
    PaintKEK_Widget/resources/style.png

SUBDIRS += \
    PaintKEK_Widget/PaintKEK_Widget.pro

