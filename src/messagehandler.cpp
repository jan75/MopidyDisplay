// messagehandler.cpp
#include "messagehandler.hpp"

using nlohmann::json;

MessageHandler::MessageHandler(WebSocketClientQt *wsc) {
    this->wsc = wsc;

    connect(wsc, &WebSocketClientQt::textMessageReceived, this, &MessageHandler::handle_message);
}

void MessageHandler::connect_ws() {
    QSettings settings("metasoft", "mopidydisplay");
    settings.beginGroup("mopidy");
    QString url = settings.value("url", "ws://localhost:6680/mopidy/ws").toString();
    settings.endGroup();

    std::cout << "Initiating connection to " << url.toStdString() << std::endl;
    wsc->connect_to_ws(url);
}

void MessageHandler::send_json(json msgJson) {
    //std::cout << msgJson << std::endl;
    // "{'jsonrpc': '2.0', 'id': 1, 'method': 'core.playback.get_state'}"
    QString msg = QString::fromStdString(msgJson.dump());
    wsc->send_msg(msg);
}

void MessageHandler::handle_message(QString msg) {
    //std::cout << msg.toStdString() << std::endl;
    std::string msgStr = msg.toStdString();
    json msgJson = create_json_object(msgStr);

    emit text_msg_received(msgJson);
    
    if(msgJson.find("event") != msgJson.end()) {
        handle_event(msgJson);
    }

    if(msgJson.find("id") != msgJson.end()) {
        int id = msgJson["id"];
        std::string type = get_result_type(id);

        if(type == "tracklist") {
            std::cout << "tracklist result received, id: " << id << std::endl;
        }

        if(type == "search") {
            std::cout << "search result received, id: " << id << std::endl;
        }

    }
}

void MessageHandler::handle_event(json msgJson) {
    std::string eventStr = msgJson["event"];
    std::cout << "Handling event: " << eventStr << std::endl;

    // stream_title_changed

    if(eventStr == "track_playback_started") {
        std::string title = msgJson["tl_track"]["track"]["name"];
        std::string album = msgJson["tl_track"]["track"]["album"]["name"];
        std::string artist = msgJson["tl_track"]["track"]["album"]["artists"][0]["name"];

        std::shared_ptr<Track> track(new Track(title, album, artist));
        emit track_change(track);
    }

    if(eventStr == "tracklist_changed") {
        get_playlist();

        //emit playlist_change(trackList);
    }
}

json MessageHandler::create_json_object(std::string msg) {
    json msgJson;
    try {
        msgJson = json::parse(msg);
    } catch (json::parse_error &e) {
        std::cerr << e.what() << std::endl;
    }
    return msgJson;
}

void MessageHandler::search_artists(QString artist) {
    std::cout << "Searching for artist " << artist.toStdString() << std::endl;

    int id = get_id("search");
    json queryParams;
    queryParams["artist"] = "";

    json queryJson;
    queryJson["jsonrpc"] = "2.0";
    queryJson["id"] = id;
    queryJson["method"] = "core.library.find_exact";
    queryJson["params"] = queryParams;
    queryJson["params"]["artist"] = artist.toStdString();

    send_json(queryJson);
}

void MessageHandler::get_playlist() {
    std::vector<Track> trackList;
    std::cout << "Querying current playlist" << std::endl;

    int id = get_id("tracklist");
    json queryJson;
    queryJson["jsonrpc"] = "2.0";
    queryJson["id"] = id;
    queryJson["method"] = "core.tracklist.get_tracks";

    send_json(queryJson);
}

std::string MessageHandler::get_result_type(int id) {
    std::string type;

    QMutex mutex;
    mutex.lock();
    if(mapping_table.contains(id)) {
        type = mapping_table[id];
        mapping_table.remove(id);
    }
    mutex.unlock();

    return type;
}

int MessageHandler::get_id(std::string type) {
    QMutex mutex;
    mutex.lock();
    last_request_id = last_request_id + 1;
    mapping_table.insert(last_request_id, type);
    mutex.unlock();

    return last_request_id;
}
