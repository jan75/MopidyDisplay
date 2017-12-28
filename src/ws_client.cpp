#include <iostream>
#include <memory>
#include "assert.h"

#include <easywsclient.hpp>
#include <easywsclient.cpp>

using std::unique_ptr;
using easywsclient::WebSocket;

class WebSocketClient {
	unique_ptr<WebSocket> get_ws() {
		WebSocket::pointer ws = WebSocket::from_url("ws://192.168.178.26:6680/mopidy/ws");
		unique_ptr<WebSocket> uws(ws);
		return uws;
	}
};
