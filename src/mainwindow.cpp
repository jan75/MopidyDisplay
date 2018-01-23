// mainwindow.cpp
#include "mainwindow.hpp"

using nlohmann::json;

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    label.setText("Hello World!");

    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *connectLayout = new QHBoxLayout;
    
    placeholderConnectionStr = QString::fromStdString("ws://127.0.0.1:6680/mopidy/ws");
    inputWSAddress.setPlaceholderText(placeholderConnectionStr);
    inputWSAddress.setText(placeholderConnectionStr);
    connectLayout->addWidget(&inputWSAddress);
    btnConnectWS.setText("Connect");
    connectLayout->addWidget(&btnConnectWS);
    connectBox.setFlat(true);
    connectBox.setLayout(connectLayout);
    
    connect(&btnConnectWS, SIGNAL(clicked()), this, SLOT(connect_ws()));
    
    layout->addWidget(&connectBox);
    layout->addWidget(&label);
    setLayout(layout);
};

void MainWindow::connect_ws() {
    QString url = inputWSAddress.text();
    std::string urlStr = url.toStdString();
    //std::cout << urlStr << std::endl;
    bool result = wsc->connect_ws(urlStr);
    if(result != false) {
        std::stringstream msgStream;
        msgStream << "Connected to " << urlStr << std::endl;
        std::string msg = msgStream.str();
        update_label_text(msg);
    } else {
        std::stringstream msgStream;
        msgStream << "Could not connect to " << urlStr << std::endl;
        std::string msg = msgStream.str();
        update_label_text(msg);
    }
}

void MainWindow::set_wsc(WebSocketClient *wscParam) {
    this->wsc = wscParam;
}

void MainWindow::update_label_text(std::string text) {
	QMutexLocker locker(&mutex);
    //json json_test;
    //json_test = json::parse(text);
    QString qstring = QString::fromStdString(text);
    //printf("%s\n", text.c_str());
    label.setText(qstring);
};
