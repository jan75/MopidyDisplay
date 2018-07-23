// main.cpp
#include <iostream>
#include <QApplication>
#include <QLabel>
#include <QtWidgets>
//#include <unistd.h>

#include "mainwindow.hpp"
#include "ws_client.hpp"
#include "messagehandler.hpp"
#include <json.hpp>

#ifdef WIN32
    #include <io.h>
#else
    #include <unistd.h>
#endif



using easywsclient::WebSocket;
using nlohmann::json;

int main(int argv, char **args) {
    QApplication application(argv, args);
    
    MainWindow mainWindow;
    
    WebSocketClient wsc;
    mainWindow.set_wsc(&wsc);
    
    MessageHandler messageHandler(&mainWindow, &wsc);
    
    mainWindow.show();
	return application.exec();
}
