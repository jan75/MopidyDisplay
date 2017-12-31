// ws_client.hpp
#ifndef H_WS_CLIENT
#define H_WS_CLIENT

#include <memory>
#include <iostream>
#include <thread>

#include <easywsclient.hpp>

class WebSocketClient {
    private:
        easywsclient::WebSocket::pointer ws;
        
        void handle_message(std::string msg);
    
	public:
        easywsclient::WebSocket::pointer get_ws();
        bool connect_ws(std::string url);
        static void poll_ws(easywsclient::WebSocket::pointer ws);
        
};

#endif
