#include <iostream>

#include <QApplication>
#include <QLabel>
#include <QtWidgets>

#include "ws_client.hpp"
#include "ui.hpp"

using easywsclient::WebSocket;



int main(int argv, char **args) {
	char text[] = "Hello World!";
    
    WebSocketClient wsc;
    wsc.connect_ws("ws://192.168.178.26:6680/mopidy/ws");
    
    WebSocket::pointer ws = wsc.get_ws();
    std::thread thread_poll(&WebSocketClient::poll_ws, ws);
    thread_poll.detach();
    
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

