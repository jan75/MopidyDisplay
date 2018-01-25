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
        MainWindow *mainWindow;
        bool connected;
    
	public:
        WebSocketClient();
        easywsclient::WebSocket::pointer get_ws();
        bool connect_ws(std::string url);
        void set_mainwindow(MainWindow *mainWin);
        void poll_ws();
        bool get_connected();
        
        void send_ws(std::string message);
        
    signals:
        void dispatch_message(QString msg);
        
    public slots:
        void test_print_slot(QString msg);
};

#endif
