// messagehandler.cpp
#include "messagehandler.hpp"

using nlohmann::json;

MessageHandler::MessageHandler(WebSocketClientQt *wsc) {
    this->wsc = wsc;

    connect(wsc, &WebSocketClientQt::dispatch_message, this, &MessageHandler::handle_message);
}

void MessageHandler::connect_ws() {
    QString url = QString("ws://htpc-jan:6680/mopidy/ws");
    wsc->connect_to_ws(url);
}

void MessageHandler::send_json(json msgJson) {
    std::cout << msgJson << std::endl;
    // "{'jsonrpc': '2.0', 'id': 1, 'method': 'core.playback.get_state'}"
    QString msg = QString::fromStdString(msgJson.dump());
    wsc->send_msg(msg);
}

void MessageHandler::handle_message(QString msg) {
    std::string msgStr = msg.toStdString();
    json msgJson = create_json_object(msgStr);
    //std::cout << msgJson.dump(2) << std::endl;
    emit text_msg_received(msgJson);

    //std::cout << msgJson.dump(2) << std::endl;
    
    if(msgJson.find("event") != msgJson.end()) {
        handle_event(msgJson);
    }
}

void MessageHandler::handle_event(json msgJson) {
    //std::cout << "handle event" << std::endl;
    std::string eventStr = msgJson["event"];

    /*
    if(eventStr == "track_playback_started") {
        std::string title = msgJson["tl_track"]["track"]["name"];
        std::string album = msgJson["tl_track"]["track"]["album"]["name"];
        std::string artist = msgJson["tl_track"]["track"]["album"]["artists"][0]["name"];
        
        std::shared_ptr<Track> track(new Track(title, album, artist));
        
        std::string uri = msgJson["tl_track"]["track"]["uri"];
        //QString cover_path = search_local_coverfile(uri);
        //track->set_cover_path(cover_path);
    
        emit track_change(track);
    }
    */
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
