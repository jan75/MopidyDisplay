// ws_client_qt.cpp
#include "ws_client_qt.hpp"
#include "mainwindow.hpp"

WebSocketClientQt::WebSocketClientQt() {
    connected = false;

    connect(this, SIGNAL(connect_ws(QUrl)), &qWebSocket, SLOT(open(QUrl)));
    connect(&qWebSocket, SIGNAL(connected()), this, SLOT(connected_state()));
    connect(&qWebSocket, SIGNAL(disconnected()), this, SLOT(disconnected_state()));
    connect(&qWebSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(changed_state(QAbstractSocket::SocketState)));
    connect(&qWebSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(text_msg_received(QString)));
    //std::cout << "Last QWebSocket error: " << qWebSocket.errorString().toStdString() << std::endl;

    //std::cout << isValid() << std::endl;
}

void WebSocketClientQt::connect_to_ws(QString qStrUrl) {
    if(not connected) {
        url = QUrl(qStrUrl);
        emit connect_ws(url);
    } else {
        std::cout << "Already connected" << std::endl;
    }
}

void WebSocketClientQt::connected_state() {
    std::cout << "Connected to websocket " << url.toString().toStdString() << std::endl;
}

void WebSocketClientQt::disconnected_state() {
    std::cout << "Disconnected from websocket " << url.toString().toStdString() << std::endl;
}

void WebSocketClientQt::changed_state(QAbstractSocket::SocketState state) {
    std::cout << "Connected state changed to: " << state << std::endl;
    if(state == 3) {
        connected = true;
    } else {
        connected = false;
    }
}

void WebSocketClientQt::text_msg_received(QString msg) {
    //std::cout << "Text message received: << " << msg.toStdString() << std::endl;
    emit dispatch_message(msg);
}

void WebSocketClientQt::send_msg(QString msg) {
    std::cout << "Sending message: " << msg.toStdString() << std::endl;
    qint64 response = qWebSocket.sendTextMessage(msg);
    std::cout << "Bytes sent: " << response << std::endl;
}
