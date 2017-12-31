#include <iostream>

#include <QApplication>
#include <QLabel>
#include <QtWidgets>

#include "ws_client.hpp"
#include "mainwindow.hpp"

using easywsclient::WebSocket;


int main(int argv, char **args) {
    QApplication application(argv, args);
    
    MainWindow mainWindow;
    
    WebSocketClient wsc;
    wsc.connect_ws("ws://192.168.178.26:6680/mopidy/ws");
    
    WebSocket::pointer ws = wsc.get_ws();
    std::thread thread_poll(&WebSocketClient::poll_ws, ws, mainWindow);
    thread_poll.detach();
    
    mainWindow.show();
	return application.exec();
}

