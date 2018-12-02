// messagehandler.h++
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
#include <set>

//#include "mainwindow.hpp"
#include "ws_client_qt.h++"
#include "models/artist.h++"
#include "models/album.h++"
#include "models/track.h++"
#include <json.h++>

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
        void parse_playlist_response(nlohmann::json msgJson);

        std::shared_ptr<Track> parse_mopidy_track_model(nlohmann::json json);
        
        void get_playlist();
    
    public:
        MessageHandler(WebSocketClientQt *wsc);

    public slots:
        void search_artists(QString artist);
        void handle_message(QString msg);
        void connect_ws();
        
    signals:
        void track_change(std::shared_ptr<Track> track);
        void playlist_change(std::vector<std::shared_ptr<Track>> playlist);
        void search_results(std::set<std::shared_ptr<Artist>> artists, std::set<std::shared_ptr<Album>> albums, std::vector<std::shared_ptr<Track>> tracks);
        void text_msg_received(nlohmann::json msg);
        void update_conn_label(QString msg);
        
};

#endif
