// messagehandler.hpp
#ifndef H_MESSAGEHANDLER
#define H_MESSAGEHANDLER
#include <QObject>
#include <QMetaType>
#include <unistd.h>

#include "mainwindow.hpp"
#include "ws_client.hpp"
#include <json.hpp>

class MessageHandler : public QObject {
    Q_OBJECT
    
    private:
		MainWindow *mainWindow;
		WebSocketClient *wsc;
    
    public:
        //MessageHandler(QWidget *parent = 0);
        //MessageHandler(MainWindow *mainWindowParm, WebSocketClient *wscParam, QWidget *parent = 0);
        
};

#endif
