// settings.cpp
#include "settings.hpp"

SettingsWindow::SettingsWindow(QTabWidget *parent) : QTabWidget(parent) {
    setWindowTitle("Settings");
    
    QVBoxLayout *settingsLayout = new QVBoxLayout;
    
    QHBoxLayout *connectLayout = new QHBoxLayout;
    
    placeholderConnectionStr = QString::fromStdString("ws://127.0.0.1:6680/mopidy/ws");
    inputWSAddress.setPlaceholderText(placeholderConnectionStr);
    inputWSAddress.setText(placeholderConnectionStr);
    connectLayout->addWidget(&inputWSAddress);
    btnConnectWS.setText("Connect");
    connectLayout->addWidget(&btnConnectWS);
    //connectBox.setFlat(true);
    connectBox.setLayout(connectLayout);
    
    settingsLayout->addWidget(&connectBox);
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
        //mainWindow->update_label_text(msg);
        std::thread thread_poll(&WebSocketClient::poll_ws, wsc);
        thread_poll.detach();
    } else {
        std::stringstream msgStream;
        msgStream << "Could not connect to " << urlStr << std::endl;
        std::string msg = msgStream.str();
        //mainWindow->update_label_text(msg);
    }
}
