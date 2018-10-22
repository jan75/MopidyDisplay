// ws_client_qt.hpp
#ifndef H_WS_CLIENT_QT
#define H_WS_CLIENT_QT

#include <memory>
#include <iostream>
#include <thread>
#include <functional>
#include <QObject>
#include <QMetaType>
#include <QReadWriteLock>
#include <QQueue>
#include <QtWebSockets/QtWebSockets>
#include <QWebSocket>
//#include "mainwindow.hpp"

#ifdef WIN32
    #include <io.h>
#else
    #include <unistd.h>
#endif

class MainWindow;

class WebSocketClientQt : public QWebSocket {
    Q_OBJECT
    
    private:
        //QWebSocket qWebSocket;
        QUrl url;
        QQueue<std::string> message_send_queue;
        QReadWriteLock lock;
        bool connected;
    
	public:
        WebSocketClientQt();
        
    signals:
        void dispatch_message(QString msg);
        
    public slots:
        void connect_to_ws(QString qStrUrl);
        void disconnected_state();
        void changed_state(QAbstractSocket::SocketState);
        void text_msg_received(QString);
        void send_msg(QString);

        
};

#endif
