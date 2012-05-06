#-------------------------------------------------
#
# Project created by QtCreator 2012-05-05T06:04:18
#
#-------------------------------------------------

QT       += core gui phonon

TARGET = EasyShot
TEMPLATE = app


SOURCES += main.cpp\
    EasyShot.cpp \
    ZException.cpp \
    PreferenceDialog.cpp \
    MainWindow.cpp \
    AppSettings.cpp \
    RegionSelectorDialog.cpp \
    ScreenShotter.cpp \
    AboutDialog.cpp

HEADERS  += \
    EasyShot.h \
    ZException.h \
    PreferenceDialog.h \
    MainWindow.h \
    AppSettings.h \
    RegionSelectorDialog.h \
    ScreenShotter.h \
    AboutDialog.h

FORMS    += \
    PreferenceDialog.ui \
    MainWindow.ui \
    AboutDialog.ui

RESOURCES += \
    icons.qrc

QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CFLAGS += -std=c++0x

OTHER_FILES +=
