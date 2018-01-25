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
    
    public:
        MessageHandler(MainWindow *mainWindow, WebSocketClient *wsc, QWidget *parent = 0);
        
	private:
		MainWindow *mainWindow;
		WebSocketClient *wsc;
        
};

#endif
