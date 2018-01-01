#include <iostream>

#include <QApplication>
#include <QLabel>
#include <QtWidgets>
#include <unistd.h>

#include "mainwindow.hpp"
#include "ws_client.hpp"

using easywsclient::WebSocket;

void update_view() {
    int x = 0;
    while(x < 1000) {
        printf("%i\n", x);
        std::string x_str = std::to_string(x);
        //MainWindow::update_label_text(x_str, mainWindow);
        x++;
        usleep(50000);
    }
}

int main(int argv, char **args) {
    QApplication application(argv, args);
    
    MainWindow mainWindow;
    
    WebSocketClient wsc;
    wsc.set_mainwindow(&mainWindow);
    wsc.connect_ws("ws://192.168.178.26:6680/mopidy/ws");
    
    std::thread thread_poll(&WebSocketClient::poll_ws, &wsc);
    thread_poll.detach();
    
    mainWindow.show();
	return application.exec();
}
