// settings.cpp
#include "settings.hpp"

SettingsWindow::SettingsWindow(QTabWidget *parent) : QTabWidget(parent) {
    setWindowTitle("Settings");
    
    QVBoxLayout *settingsLayout = new QVBoxLayout;
    QHBoxLayout *connectLayout = new QHBoxLayout;
    
    placeholderConnectionStr = QString::fromStdString("ws://htpc-jan:6680/mopidy/ws");
    inputWSAddress.setPlaceholderText(placeholderConnectionStr);
    inputWSAddress.setText(placeholderConnectionStr);
    connectLayout->addWidget(&inputWSAddress);
    btnConnectWS.setText("Connect");
    connectLayout->addWidget(&btnConnectWS);
    //connectBox.setFlat(true);
    connectBox.setLayout(connectLayout);
    
    connectionStatus.setText("Connect to a Mopidy web interface instance");
    settingsLayout->addWidget(&connectBox);
    settingsLayout->addWidget(&connectionStatus);
    connectionSettings.setLayout(settingsLayout);
    
    connect(&btnConnectWS, SIGNAL(clicked()), this, SLOT(connect_ws()));
    
    addTab(&connectionSettings, "Connection");
};


void SettingsWindow::set_wsc(WebSocketClient *wscParam) {
    this->wsc = wscParam;
}

void SettingsWindow::connect_ws() {
    //std::cout << "triggered!" << std::endl;
    QString url = inputWSAddress.text();
    std::string urlStr = url.toStdString();
    //std::cout << urlStr << std::endl;
    bool result = wsc->connect_ws(urlStr);
    if(result != false) {
        std::stringstream msgStream;
        msgStream << "Connected to " << urlStr << std::endl;
        std::string msg = msgStream.str();
        QString qmsg = QString::fromStdString(msg);
        connectionStatus.setText(qmsg);
        std::thread thread_poll(&WebSocketClient::poll_ws, wsc);
        thread_poll.detach();
    } else {
        std::stringstream msgStream;
        msgStream << "Could not connect to " << urlStr << std::endl;
        std::string msg = msgStream.str();
        QString qmsg = QString::fromStdString(msg);
        connectionStatus.setText(qmsg);
    }
}
