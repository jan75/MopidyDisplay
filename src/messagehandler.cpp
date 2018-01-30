// messagehandler.cpp
#include "messagehandler.hpp"

using nlohmann::json;

MessageHandler::MessageHandler(QObject *parent) : QObject(parent) {
    //std::cout << "MessageHandler object created with 1 param" << std::endl;
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
    //std::cout << msgJson.dump(2) << std::endl;
    
    if(msgJson.find("event") != msgJson.end()) {
        handle_event(msgJson);
    }
}

void MessageHandler::handle_event(json msgJson) {
    //std::cout << "handle event" << std::endl;
    std::string eventStr = msgJson["event"];
    if(eventStr == "track_playback_started") {
        std::string uri = msgJson["tl_track"]["track"]["uri"];
        scan_for_file(uri);
        
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
    auto x = msgJson["tl_track"];
}

void MessageHandler::scan_for_file(std::string path_file) {
    //std::cout << path_file << std::endl;
    
    QString base_dir("/home/jan/mnt/Musik/");
    
    path_file = path_file.erase(0, 12);
    QString q_path_file = QString::fromStdString(path_file);
        
    //q_path_file = base_dir_encoded + q_path_file;
    //std::cout << q_path_file.toStdString() << std::endl;
    
    /*
    QFile qFile(qPath_file);
    
    if(qFile.exists() == true) {
        std::cout << "exists!" << std::endl;
    } else {
        std::cout << "doesn't exist!" << std::endl;   
    }
    
    std::cout << qFile.fileName().toStdString() << std::endl;
    */
}
