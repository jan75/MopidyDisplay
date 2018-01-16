// mainwindow.cpp
#include "mainwindow.hpp"

using nlohmann::json;

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    label.setText("Hello World!");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(&label);
    
    setLayout(layout);
};

void MainWindow::update_label_text(std::string text) {
	QMutexLocker locker(&mutex); 
    json json_test;
    json_test = json::parse(text);
    QString qstring = QString::fromStdString(text);
    printf("%s\n", text.c_str());
    label.setText(qstring);
};
