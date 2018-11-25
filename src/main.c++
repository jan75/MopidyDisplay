// main.c++
#include <iostream>
#include <QApplication>
#include <QLabel>
#include <QtWidgets>
//#include <unistd.h>

#include "mainwindow.h++"
#include "ws_client_qt.h++"
#include "messagehandler.h++"
#include <json.h++>

#ifdef WIN32
    #include <io.h>
#else
    #include <unistd.h>
#endif

using nlohmann::json;

/**
 * @brief main Main function, creates objects and starts up GUI
 * @param argv
 * @param args
 * @return QApplication
 */
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
