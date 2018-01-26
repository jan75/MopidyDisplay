// messagehandler.cpp
#include "messagehandler.hpp"

using nlohmann::json;

MessageHandler::MessageHandler(QObject *parent) : QObject(parent) {
    std::cout << "MessageHandler object created with 1 param" << std::endl;
};

MessageHandler::MessageHandler(MainWindow *mainWindow, WebSocketClient *wsc, QObject *parent) : QObject(parent) {
    this->mainWindow = mainWindow;
    this->wsc = wsc;
    connect(wsc, &WebSocketClient::dispatch_message, this, &MessageHandler::handle_message);
    connect(this, &MessageHandler::track_change, mainWindow, &MainWindow::set_current_song);
    connect(wsc, &WebSocketClient::dispatch_message, mainWindow, &MainWindow::update_label_text);
};

void MessageHandler::handle_message(QString msg) {
    std::string msgStr = msg.toStdString();
    json msgJson = create_json_object(msgStr);
    std::cout << msgJson.dump(2) << std::endl;
    
    if(msgJson.find("event") != msgJson.end()) {
        handle_event(msgJson);
    }
}

void MessageHandler::handle_event(json msgJson) {
    //std::cout << msgJson["event"] << std::endl;
    std::string eventStr = msgJson["event"];
    if(eventStr == "track_playback_started") {
        std::string trackNameStr = msgJson["tl_track"]["track"]["name"];
        QString qText = QString::fromStdString(trackNameStr);
        emit track_change(qText);
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

void MessageHandler::send_json(json msgJson) {
    //
}
