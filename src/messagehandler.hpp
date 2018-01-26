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
        
        nlohmann::json create_json_object(std::string msg);
        void handle_event(nlohmann::json msgJson);
        void send_json(nlohmann::json msgJson);
    
    public:
        MessageHandler(QObject *parent = 0);
        MessageHandler(MainWindow *mainWindow, WebSocketClient *wsc, QObject *parent = 0);
        
    private slots:
        void handle_message(QString msg);
        
    signals:
        void track_change(QString msg);
        
};

#endif
