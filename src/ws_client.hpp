// ws_client.hpp
#ifndef H_WS_CLIENT
#define H_WS_CLIENT

#include <memory>
#include <iostream>
#include <thread>

#include "mainwindow.hpp"
#include <easywsclient.hpp>

class WebSocketClient {
    private:
        easywsclient::WebSocket::pointer ws;
    
	public:
        easywsclient::WebSocket::pointer get_ws();
        bool connect_ws(std::string url);
        
        static void poll_ws(easywsclient::WebSocket::pointer ws, MainWindow mainWindow);
};

#endif
