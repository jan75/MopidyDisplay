// ws_client.hpp
#ifndef H_WS_CLIENT
#define H_WS_CLIENT

#include <memory>

#include <easywsclient.hpp>

class WebSocketClient {
    private:
        easywsclient::WebSocket::pointer ws;
        
        void handle_message(std::string msg);
    
	public:
        bool connect_ws(std::string url);
        void poll_ws();
};

#endif
