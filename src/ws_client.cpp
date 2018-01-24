// ws_client.cpp
#include "ws_client.hpp"
#include "mainwindow.hpp"

using easywsclient::WebSocket;
using namespace std::placeholders;

void WebSocketClient::set_mainwindow(MainWindow *mainWin) {
    this->mainWindow = mainWin;
}


bool WebSocketClient::connect_ws(std::string url) {
    if(url == "") {
        return false;
    }
    
    ws = WebSocket::from_url(url);
    if(ws != NULL) {
        return true;
    } else {
        return false;
    }
}

WebSocket::pointer WebSocketClient::get_ws() {
    return ws;
}

void WebSocketClient::poll_ws() {
    WebSocket::pointer wsp = &*ws;
    while(true) {
        ws->poll(-1);        
        ws->dispatch([this, wsp](const std::string msg) {
                mainWindow->update_label_text(msg);
            });
    }
}

void WebSocketClient::send_ws(std::string message) {
    ws->send(message);
}
