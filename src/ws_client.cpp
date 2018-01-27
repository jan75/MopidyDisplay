// ws_client.cpp
#include "ws_client.hpp"
#include "mainwindow.hpp"

using easywsclient::WebSocket;
using namespace std::placeholders;

WebSocketClient::WebSocketClient() {
    connected = false;
}

bool WebSocketClient::connect_ws(std::string url) {
    if(url == "") {
        return false;
    }
    
    ws = WebSocket::from_url(url);
    if(ws != NULL) {
        connected = true;
        return true;
    } else {
        return false;
    }
}

WebSocket::pointer WebSocketClient::get_ws() {
    return ws;
}

bool WebSocketClient::get_connected() {
    return connected;
}

void WebSocketClient::poll_ws() {
    WebSocket::pointer wsp = &*ws;
    while(true) {
        ws->poll(0);        
        ws->dispatch([this, wsp](std::string msg) {
                QString qMsg = QString::fromStdString(msg);
                emit dispatch_message(qMsg);
            });
    }
}

void WebSocketClient::send_ws(std::string message) {
    ws->send(message);
}
