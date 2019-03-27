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
        /*
        QString titleStr = QString::fromStdString(msgJson["tl_track"]["track"]["name"]);
        QString albumStr = QString::fromStdString(msgJson["tl_track"]["track"]["album"]["name"]);
        QString artistStr = QString::fromStdString(msgJson["tl_track"]["track"]["album"]["artists"][0]["name"]);
        int length = msgJson["tl_track"]["track"]["length"];
        int track_number = msgJson["tl_track"]["track"]["track_no"];

        std::shared_ptr<Artist> artist = std::make_shared<Artist>(artistStr);
        std::shared_ptr<Album> album = std::make_shared<Album>(albumStr, artist);
        std::shared_ptr<Track> track = std::make_shared<Track>(titleStr, album, artist, length, track_number);
        emit track_change(track);
        */
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
    //std::set<std::shared_ptr<Artist>, decltype(&Artist::artist_compare)> artistSet(&Artist::artist_compare);
    std::vector<std::shared_ptr<Artist>> artistList;
    std::vector<std::shared_ptr<Album>> albumList;
    std::vector<std::shared_ptr<Track>> trackList;

    nlohmann::json type = msgJson["result"][0]["__model__"];
    if(type != "SearchResult") {
        return;
    }

    nlohmann::json tracks = msgJson["result"][0]["tracks"];
    for(nlohmann::json &element: tracks) {
        if(element["__model__"] == "Track") {
            std::shared_ptr<Track> tmpTrack = parse_mopidy_track_model(element);
            trackList.push_back(tmpTrack);

            // Comparing albums and inserting into list if unique
            std::shared_ptr<Album> tmpAlbum = tmpTrack->get_album();
            if(albumList.size() == 0) {
                albumList.push_back(tmpAlbum);
            } else if(albumList.size() > 0) {
                bool unique = true;
                for(std::shared_ptr<Album> tmpAlbumFromList: albumList) {
                    bool compare = tmpAlbum->compare(tmpAlbumFromList);
                    if(compare == true) {
                        unique = false;
                        break;
                    }
                }

                if(unique) {
                    albumList.push_back(tmpAlbum);
                }
            }

            // Comparing artists and inserting into list if unique
            std::vector<std::shared_ptr<Artist>> tmpArtistList = tmpTrack->get_artists();
            for(std::shared_ptr<Artist> tmpArtist: tmpArtistList) {
                std::cout << "parse_search_results artist.name: " << tmpArtist->get_name().toStdString() << std::endl;
                if(artistList.size() == 0) {
                    artistList.push_back(tmpArtist);
                } else if(artistList.size() > 0) {
                    bool unique = true;
                    for(std::shared_ptr<Artist> tmpArtistFromList: artistList) {
                        bool compare = tmpArtist->compare(tmpArtistFromList);
                        //std::cout << compare << ": " << tmpArtist->get_name().toStdString() << " (" << tmpArtist->get_object_hash() << ") " << " with " << tmpArtistFromList->get_name().toStdString() << " (" << tmpArtistFromList->get_object_hash() << ")" << std::endl;
                        if(compare == true) {
                            unique = false;
                            break;
                        }
                    }

                    if(unique) {
                        artistList.push_back(tmpArtist);
                    }
                }
                std::cout << "List size: " << artistList.size() << std::endl;
            }
        }
    }

    /*
    for(std::shared_ptr<Album> album: albumSet) {
        std::cout << album->get_name().toStdString() << std::endl;
    }
    */

    emit search_results(artistList, albumList, trackList);
}

std::shared_ptr<Track> MessageHandler::parse_mopidy_track_model(nlohmann::json json) {
    nlohmann::json album_json = json["album"];
    nlohmann::json artists_json = json["artists"];
    std::shared_ptr<Album> album_obj = parse_mopidy_album_model(album_json);
    std::vector<std::shared_ptr<Artist>> artists_obj = parse_mopidy_artist_model(artists_json);

    std::string title = json["name"];
    int length = json["length"];
    int track_number = json["track_no"];

    QString titleQ = QString::fromStdString(title);

    return std::make_shared<Track>(titleQ, album_obj, artists_obj, length, track_number);
}

std::vector<std::shared_ptr<Artist>> MessageHandler::parse_mopidy_artist_model(nlohmann::json artists) {
    std::vector<std::shared_ptr<Artist>> artists_obj;
    QString name;

    if(artists.size() == 0) {
        std::cout << "No artists found" << std::endl;
    }

    for(nlohmann::json &artist: artists) {
        if(artist["__model__"] == "Artist") {
            name = QString::fromStdString(artist["name"]);
            artists_obj.push_back(std::make_shared<Artist>(name));
        } else {
            std::cout << "Something went wrong during parsing of an artist model" << std::endl;
            std::cout << artist.dump(2) << std::endl;
        }
    }

    return artists_obj;
}

std::shared_ptr<Album> MessageHandler::parse_mopidy_album_model(nlohmann::json album) {
    QString name, date;
    int num_tracks, num_discs;
    std::vector<std::shared_ptr<Artist>> album_artists;

    if(album["__model__"] == "Album") {
        name = QString::fromStdString(album["name"]);
        num_tracks = album["num_tracks"];
        num_discs = album["num_discs"];
        date = QString::fromStdString(album["date"]);
        album_artists = parse_mopidy_artist_model(album["artists"]);
    }  else {
        std::cout << "Something went wrong during parsing of an album model" << std::endl;
        std::cout << album.dump(2) << std::endl;
    }

    return std::make_shared<Album>(name, album_artists);
}
