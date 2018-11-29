TEMPLATE = app
TARGET = MopidyDisplay

CONFIG += qt
CONFIG += debug
CONFIG += c++14

QT += widgets
QT += websockets

win32: LIBS += -lws2_32

INCLUDEPATH += .
INCLUDEPATH += lib/json/

HEADERS += lib/json/json.h++
HEADERS += src/mainwindow.h++
HEADERS += src/messagehandler.h++
HEADERS += src/ws_client_qt.h++
HEADERS += src/models/album.h++
HEADERS += src/models/artist.h++
HEADERS += src/models/track.h++
HEADERS += src/models/playlist.h++
HEADERS += src/models/searchresults.h++
HEADERS += src/widgets/resulttableview.h++

SOURCES += src/main.c++
SOURCES += src/mainwindow.c++
SOURCES += src/messagehandler.c++
SOURCES += src/ws_client_qt.c++
SOURCES += src/models/album.c++
SOURCES += src/models/artist.c++
SOURCES += src/models/track.c++
SOURCES += src/models/playlist.c++
SOURCES += src/models/searchresults.c++
SOURCES += src/widgets/resulttableview.c++
