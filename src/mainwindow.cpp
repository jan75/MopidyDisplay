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
    
    //connect(btnConnectWS, SIGNAL(click()), this, SLOT(connect_ws()));
    
    layout->addWidget(&connectBox);
    layout->addWidget(&label);
    setLayout(layout);
};

void MainWindow::connect_ws() {
    update_label_text("Button clicked!");
}

void MainWindow::update_label_text(std::string text) {
	QMutexLocker locker(&mutex); 
    json json_test;
    json_test = json::parse(text);
    QString qstring = QString::fromStdString(text);
    printf("%s\n", text.c_str());
    label.setText(qstring);
};
