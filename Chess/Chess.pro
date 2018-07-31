#-------------------------------------------------
#
# Project created by QtCreator 2018-07-09T22:13:44
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = Chess
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
        main.cpp \
    viewClasses/gpiece.cpp \
    viewClasses/gsquare.cpp \
    viewClasses/gdialogexit.cpp \
    modelClasses/mbishop.cpp \
    modelClasses/mgame.cpp \
    modelClasses/mking.cpp \
    modelClasses/mknight.cpp \
    modelClasses/mpawn.cpp \
    modelClasses/mpiece.cpp \
    modelClasses/mqueen.cpp \
    modelClasses/mrook.cpp \
    viewClasses/ggame.cpp \
    viewClasses/gwindow.cpp \
    viewClasses/dialog_mate.cpp \
    viewClasses/dialog_draw.cpp \
    modelClasses/mcountdown.cpp \
    modelClasses/mtimer.cpp \
    viewClasses/dialog_time.cpp \
    viewClasses/dialog_promote.cpp \
    viewClasses/gnotation.cpp \
    modelClasses/mstate.cpp \
    viewClasses/dialog_new_game.cpp \
    viewClasses/dialog_about.cpp

HEADERS += \
    viewClasses/gpiece.h \
    viewClasses/gsquare.h \
    viewClasses/gdialogexit.h \
    modelClasses/mbishop.h \
    modelClasses/mconstants.h \
    modelClasses/mgame.h \
    modelClasses/mking.h \
    modelClasses/mknight.h \
    modelClasses/mpawn.h \
    modelClasses/mpiece.h \
    modelClasses/mpiece_types.h \
    modelClasses/mqueen.h \
    modelClasses/mrook.h \
    viewClasses/ggame.h \
    viewClasses/gwindow.h \
    viewClasses/gconstants.h \
    viewClasses/dialog_mate.h \
    viewClasses/dialog_draw.h \
    modelClasses/mcountdown.h \
    modelClasses/mtimer.h \
    viewClasses/dialog_time.h \
    viewClasses/dialog_promote.h \
    viewClasses/gnotation.h \
    modelClasses/mstate.h \
    viewClasses/dialog_new_game.h \
    viewClasses/dialog_about.h

FORMS += \
    viewClasses/ggame.ui \
    viewClasses/dialogexit.ui \
    viewClasses/dialog_mate.ui \
    viewClasses/dialogdraw.ui \
    viewClasses/dialogtime.ui \
    viewClasses/dialogpromote.ui \
    viewClasses/dialognewgame.ui \
    viewClasses/dialogabout.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

RC_FILE = chess.rc
