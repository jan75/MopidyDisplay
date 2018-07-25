// ws_client.hpp
#ifndef H_WS_CLIENT
#define H_WS_CLIENT

#include <memory>
#include <iostream>
#include <thread>
#include <functional>
#include <QObject>
#include <QMetaType>
#include <QReadWriteLock>
#include <QQueue>

#include <easywsclient.hpp>
//#include "mainwindow.hpp"

#ifdef WIN32
    #include <io.h>
#else
    #include <unistd.h>
#endif

class MainWindow;

class WebSocketClient : public QObject {
    Q_OBJECT
    
    private:
        QQueue<std::string> message_send_queue;
        QReadWriteLock lock;
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
