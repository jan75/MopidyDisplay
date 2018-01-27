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
    connectBox.setLayout(connectLayout);
    
    settingsLayout->addWidget(&connectBox);
    connectionSettings.setLayout(settingsLayout);
    
    addTab(&connectionSettings, "Connection");
};


void SettingsWindow::set_wsc(WebSocketClient *wscParam) {
    this->wsc = wscParam;
}

bool SettingsWindow::connect_ws() {
    QString url = inputWSAddress.text();
    std::string urlStr = url.toStdString();
    bool result = wsc->connect_ws(urlStr);
    if(result != false) {
        std::thread thread_poll(&WebSocketClient::poll_ws, wsc);
        thread_poll.detach();
        return true;
    }
    return false;
}
