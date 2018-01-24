// ws_client.hpp
#ifndef H_WS_CLIENT
#define H_WS_CLIENT

#include <memory>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <functional>

#include <easywsclient.hpp>
//#include "mainwindow.hpp"

class MainWindow;

class WebSocketClient {
    private:
        easywsclient::WebSocket::pointer ws;
        MainWindow *mainWindow;
    
	public:
        easywsclient::WebSocket::pointer get_ws();
        bool connect_ws(std::string url);
        void set_mainwindow(MainWindow *mainWin);
        void poll_ws();
        
        void send_ws();
};

#endif
