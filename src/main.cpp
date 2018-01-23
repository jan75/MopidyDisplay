// main.cpp
#include <iostream>

#include <QApplication>
#include <QLabel>
#include <QtWidgets>
#include <unistd.h>

#include "mainwindow.hpp"
#include "ws_client.hpp"
#include <json.hpp>

using easywsclient::WebSocket;
using nlohmann::json;

int main(int argv, char **args) {
    QApplication application(argv, args);
    
    MainWindow mainWindow;
    
    WebSocketClient wsc;
    wsc.set_mainwindow(&mainWindow);
    //wsc.connect_ws("ws://127.0.0.1:6680/mopidy/ws");
    
    mainWindow.set_wsc(&wsc);
   
    //std::thread thread_poll(&WebSocketClient::poll_ws, &wsc);
    //thread_poll.detach();
    
    json json_test;
    
    mainWindow.show();
	return application.exec();
}
