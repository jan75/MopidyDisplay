#include <iostream>

#include <QApplication>
#include <QLabel>
#include <QtWidgets>

#include "ws_client.hpp"
#include <memory>

using std::unique_ptr;
using easywsclient::WebSocket;



int main(int argv, char **args) {
	char text[] = "Hello World!";
    
    WebSocketClient wsc;
    wsc.connect_ws("ws://192.168.178.26:6680/mopidy/ws");
    wsc.poll_ws();
    /*
    unique_ptr<WebSocket> ws = wsc.get_ws();
    while(true) {
        WebSocket::pointer wsp = &*ws;
        ws->poll(1);
        ws->dispatch([wsp](const std::string &message) {
                handle_message(message);
                //printf("%s\n", message.c_str());
            });
    }
    */

	QApplication application(argv, args);
	QWidget window;
	
	QLabel label;
	label.setText(text);

	QHBoxLayout layout;
	layout.addWidget(&label);
	
	window.setLayout(&layout);
	window.show();

	/*
	QLabel *label = new QLabel;
	label->setText(text);

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(&label2);
	window.setLayout(layout);
	window.show();
	*/

	return application.exec();
}

