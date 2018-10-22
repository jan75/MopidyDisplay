// main.cpp
#include <iostream>
#include <QApplication>
#include <QLabel>
#include <QtWidgets>
//#include <unistd.h>

#include "mainwindow.hpp"
#include "ws_client_qt.hpp"
#include "messagehandler.hpp"
#include <json.hpp>

#ifdef WIN32
    #include <io.h>
#else
    #include <unistd.h>
#endif

using nlohmann::json;

int main(int argv, char **args) {
    QApplication application(argv, args);

    QSettings settings("metasoft", "mopidydisplay");
    settings.beginGroup("mopidy");
    settings.endGroup();


    WebSocketClientQt wsc;
    MessageHandler messageHandler(&wsc);
    MainWindow mainWindow(&messageHandler);

    mainWindow.show();
	return application.exec();
}
