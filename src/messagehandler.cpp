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
        std::string title = msgJson["tl_track"]["track"]["name"];
        std::string album = msgJson["tl_track"]["track"]["album"]["name"];
        std::string artist = msgJson["tl_track"]["track"]["album"]["artists"][0]["name"];
        
        std::shared_ptr<Track> track(new Track(title, album, artist));
        
        std::string uri = msgJson["tl_track"]["track"]["uri"];
        QString cover_path = search_local_coverfile(uri);
        track->set_cover_path(cover_path);
    
        emit track_change(track);
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

QString MessageHandler::search_local_coverfile(std::string path_file) {
    bool found = false;
    
    QString base_dir("/home/jan/data/Musik/");
    QByteArray qByteArray_base_dir = QUrl::toPercentEncoding(base_dir);
    
    if(path_file.rfind("local:", 0) == 0) {
        path_file = path_file.erase(0, 12);
    } else {
        std::cout << "Not local media: " << path_file << std::endl;
        QString placeholder = QString("/home/jan/git/MopidyDisplay/media/images/placeholder_small.jpg");
        return placeholder;
    }
    
    QByteArray qByteArray_path_file = QByteArray::fromStdString(path_file);
    qByteArray_base_dir.append(qByteArray_path_file);
    
    QUrl file_url = QUrl::fromPercentEncoding(qByteArray_base_dir);
    
    QDir dir(file_url.toString(QUrl::None));
    
    // Built file path and created QDir object which points there 
    // Moving one level up and checking if Cover.jpg, Cover.png, cover.jpg, cover.png, Front.jpg, Front.png, front.jpg, front.png exists
    std::vector<std::string> cover_names = {"Cover.jpg", "Cover.png", "cover.jpg", "cover.png", "Front.jpg", "Front.png", "front.jpg", "front.png"};
    dir.cdUp();
    
    // to do:
    // check if folder is CD01 or CD02 or CD1 / CD2 etc. and if the file is anywhere in the album dir (also to do: find the album dir...) to check if i can do it dynamically. Something with: dir.dirName() etc. 
    
    unsigned i;
    QString cover_name;
    for(i = 0; i < cover_names.size(); i++) {
        cover_name = QString::fromStdString(cover_names[i]);
        if(dir.exists(cover_name) == true) {
            found = true;
            break;
        }
    }
    
    if(found == true) {
        QString cover_name = QString::fromStdString(cover_names[i]);
        QDir dir_complete = QDir::cleanPath(dir.path() + QDir::separator() + cover_name);
        std::cout << "Found " << dir_complete.path().toStdString() << std::endl;
        return dir_complete.path();
        //return QDir::cleanPath(dir + QDir::separator() + cover_name);
    } else {
        std::cout << "No cover found in " << dir.path().toStdString() << std::endl;
        QString placeholder = QString("/home/jan/git/MopidyDisplay/media/images/placeholder_small.jpg");
        return placeholder;
    }
}
