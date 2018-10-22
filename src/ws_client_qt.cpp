// ws_client_qt.cpp
#include "ws_client_qt.hpp"
#include "mainwindow.hpp"

WebSocketClientQt::WebSocketClientQt() {
    connected = false;

    connect(this, &WebSocketClientQt::stateChanged, this, &WebSocketClientQt::changed_state);
    connect(this, &WebSocketClientQt::disconnected, this, &WebSocketClientQt::disconnected_state);
    connect(this, &WebSocketClientQt::textMessageReceived, this, &WebSocketClientQt::text_msg_received);
}

void WebSocketClientQt::connect_to_ws(QString qStrUrl) {
    if(not connected) {
        url = QUrl(qStrUrl);
        //qWebSocket.open(url);
        open(url);
    } else {
        std::cout << "Already connected" << std::endl;
    }
}

void WebSocketClientQt::disconnected_state() {
    std::cout << "Disconnected from websocket " << url.toString().toStdString() << std::endl;
}

void WebSocketClientQt::changed_state(QAbstractSocket::SocketState state) {
    std::cout << "Connected state changed to: " << state << std::endl;
    if(state == 3) {
        std::cout << "Connected" << std::endl;
        connected = true;
    } else {
        connected = false;
    }
}

void WebSocketClientQt::text_msg_received(QString msg) {
    std::cout << "Text message received: << " << msg.toStdString() << std::endl;
    emit dispatch_message(msg);
}

void WebSocketClientQt::send_msg(QString msg) {
    std::cout << "Sending message: " << msg.toStdString() << std::endl;
    qint64 response = sendTextMessage(msg);
    std::cout << "Bytes sent: " << response << std::endl;
}
