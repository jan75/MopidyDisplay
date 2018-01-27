// ws_client.hpp
#ifndef H_WS_CLIENT
#define H_WS_CLIENT

#include <memory>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <functional>
#include <QObject>
#include <QMetaType>

#include <easywsclient.hpp>
//#include "mainwindow.hpp"

class MainWindow;

class WebSocketClient : public QObject {
    Q_OBJECT
    
    private:
        easywsclient::WebSocket::pointer ws;
        bool connected;
    
	public:
        WebSocketClient();
        
        void poll_ws();
        bool connect_ws(std::string url);
        
        bool get_connected();
        easywsclient::WebSocket::pointer get_ws();
        
    signals:
        void dispatch_message(QString msg);
        
    public slots:
        void send_ws(std::string message);
};

#endif
