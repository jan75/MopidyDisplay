// messagehandler.hpp
#ifndef H_MESSAGEHANDLER
#define H_MESSAGEHANDLER
#include <QObject>
#include <QMetaType>
#include <QDir>
#include <QUrl>
#include <QMutex>
#include <QHash>
#include <memory>
#include <map>

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
        QHash<int, std::string> mapping_table;
        int last_request_id = 0;
        
        nlohmann::json create_json_object(std::string msg);
        void handle_event(nlohmann::json msgJson);
        void send_json(nlohmann::json msgJson);
        int get_id(std::string type);
        std::string get_result_type(int id);
        void parse_search_results(nlohmann::json msgJson);
        
        void get_playlist();
    
    public:
        MessageHandler(WebSocketClientQt *wsc);

    public slots:
        void search_artists(QString artist);
        void handle_message(QString msg);
        void connect_ws();
        
    signals:
        void track_change(std::shared_ptr<Track> track);
        void playlist_change(std::vector<Track> playlist);
        void text_msg_received(nlohmann::json msg);
        void update_conn_label(QString msg);
        
};

#endif
