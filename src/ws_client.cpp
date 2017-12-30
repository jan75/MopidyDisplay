#include "ws_client.hpp"

using easywsclient::WebSocket;

/*
std::unique_ptr<WebSocket> WebSocketClient::get_ws() {
    WebSocket::pointer wsx = WebSocket::from_url("ws://192.168.178.26:6680/mopidy/ws");
    std::unique_ptr<WebSocket> uws(wsx);
    return uws;
}
*/

bool WebSocketClient::connect_ws(std::string url) {
    if(url == "") {
        return false;
    }
    
    WebSocket::pointer wsp = WebSocket::from_url(url);
    
    std::unique_ptr<WebSocket> ws(wsp);
    
    return true;
}


void WebSocketClient::handle_message(std::string msg) {
    printf("%s\n", msg.c_str());
}

void WebSocketClient::poll_ws() {
    //WebSocket::pointer wsp = &*ws;
    this->ws->poll(1);
    /*
    ws->dispatch([wsp](const std::string &msg) {
            //this->handle_message(msg);
            printf("%s\n", msg.c_str());
        });
        */
}
