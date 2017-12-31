#include "ws_client.hpp"

using easywsclient::WebSocket;

bool WebSocketClient::connect_ws(std::string url) {
    if(url == "") {
        return false;
    }
    
    ws = WebSocket::from_url(url);
    
    return true;
}

WebSocket::pointer WebSocketClient::get_ws() {
    return ws;
}

void WebSocketClient::poll_ws(WebSocket::pointer ws, MainWindow mainWindow) {
    //printf("%s\n", ws);
    //std::cout<<"ws is of type: " << typeid(ws).name() << std::endl;
    WebSocket::pointer wsp = &*ws;
    while(true) {
        ws->poll(-1);
        ws->dispatch(MainWindow::update_label_text);
        /*
        ws->dispatch([wsp](const std::string &msg) {
                //printf("%s\n", msg.c_str());
                MainWindow::update_label_text(msg);
            });
            */
            
    }
}
