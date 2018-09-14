// messagehandler.hpp
#ifndef H_MESSAGEHANDLER
#define H_MESSAGEHANDLER
#include <QObject>
#include <QMetaType>
#include <QDir>
#include <QUrl>
#include <memory>

//#include "mainwindow.hpp"
#include "ws_client_qt.hpp"
#include "models/track.hpp"
#include <json.hpp>

#ifdef WIN32
    #include <io.h>
#else
    #include <unistd.h>
#endif

class MessageHandler : public QObject {
    Q_OBJECT
    
    private:
        WebSocketClientQt *wsc;
        
        nlohmann::json create_json_object(std::string msg);
        void handle_event(nlohmann::json msgJson);
        void send_json(nlohmann::json msgJson);
        
        QString search_local_coverfile(std::string path_file);
    
    public:
        MessageHandler(WebSocketClientQt *wsc);

    public slots:
        void handle_message(QString msg);
        void connect_ws();
        
    signals:
        void track_change(std::shared_ptr<Track> track);
        void text_msg_received(nlohmann::json msg);
        void update_conn_label(QString msg);
        
};

#endif
