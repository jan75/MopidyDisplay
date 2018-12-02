// messagehandler.c++
#include "messagehandler.h++"

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
    // "{'jsonrpc': '2.0', 'id': 1, 'method': 'core.playback.get_state'}"
    QString msg = QString::fromStdString(msgJson.dump());
    wsc->send_msg(msg);
}

void MessageHandler::handle_message(QString msg) {
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
            parse_playlist_response(msgJson);
        }

        if(type == "search") {
            parse_search_results(msgJson);
        }

    }
}

void MessageHandler::handle_event(json msgJson) {
    std::string eventStr = msgJson["event"];
    // stream_title_changed

    if(eventStr == "track_playback_started") {
        QString title = QString::fromStdString(msgJson["tl_track"]["track"]["name"]);
        QString album = QString::fromStdString(msgJson["tl_track"]["track"]["album"]["name"]);
        QString artist = QString::fromStdString(msgJson["tl_track"]["track"]["album"]["artists"][0]["name"]);
        int length = msgJson["tl_track"]["track"]["length"];
        int track_number = msgJson["tl_track"]["track"]["track_no"];

        std::shared_ptr<Track> track = std::make_shared<Track>(title, album, artist, length, track_number);
        emit track_change(track);
    }

    if(eventStr == "tracklist_changed") {
        get_playlist();
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

    int id = get_id("search");
    json queryParams;
    queryParams["any"] = "";

    json queryJson;
    queryJson["jsonrpc"] = "2.0";
    queryJson["id"] = id;
    queryJson["method"] = "core.library.search";
    queryJson["params"] = queryParams;
    queryJson["params"]["any"] = artist.toStdString();


    send_json(queryJson);
}

void MessageHandler::get_playlist() {
    std::vector<Track> trackList;

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

void MessageHandler::parse_playlist_response(nlohmann::json msgJson) {
    std::vector<std::shared_ptr<Track>> playlistList;

    nlohmann::json tracks = msgJson["result"];
    for(nlohmann::json &element: tracks) {
        if(element["__model__"] == "Track") {
            std::shared_ptr<Track> tmpTrack = parse_mopidy_track_model(element);
            playlistList.push_back(tmpTrack);
        }
    }

    emit playlist_change(playlistList);
}

void MessageHandler::parse_search_results(nlohmann::json msgJson) {
    std::set<std::shared_ptr<Artist>> artistSet;
    std::set<std::shared_ptr<Album>> albumSet;
    std::vector<std::shared_ptr<Track>> trackList;

    emit search_results(artistSet, albumSet, trackList);
}

std::shared_ptr<Track> MessageHandler::parse_mopidy_track_model(nlohmann::json json) {
    std::string title = json["name"];
    std::string album = json["album"]["name"];
    std::string artist;
    nlohmann::json artists = json["artists"];
    if(artists.size() > 1) {
        std::cout << "Multiple artists, picking first: " << artists[0]["name"] << std::endl;
    } else if(artists.size() == 0) {
        std::cout << "No artists found" << std::endl;
    } else {
        artist = artists[0]["name"];
    }

    int length = json["length"];
    int track_number = json["track_no"];

    QString titleQ = QString::fromStdString(title);
    QString albumQ = QString::fromStdString(album);
    QString artistQ = QString::fromStdString(artist);

    return std::make_shared<Track>(titleQ, albumQ, artistQ, length, track_number);
}
