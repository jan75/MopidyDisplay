// ws_client.cpp
#include "ws_client.hpp"
#include "mainwindow.hpp"

using easywsclient::WebSocket;
using namespace std::placeholders;

void WebSocketClient::set_mainwindow(MainWindow *mainWin) {
    this->mainWindow = mainWin;
}

WebSocketClient::WebSocketClient() {
    connected = false;
    connect(this, &WebSocketClient::dispatch_message, this, &WebSocketClient::test_print_slot);
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

void WebSocketClient::test_print_slot(QString msg) {
    std::string msgStr = msg.toStdString();
    //std::cout << msgStr << std::endl;
}

void WebSocketClient::send_ws(std::string message) {
    ws->send(message);
}
