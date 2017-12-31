// ui.cpp
#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    MainWindow::label.setText("Hello World!");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(&label);
    
    setLayout(layout);
};

void MainWindow::update_label_text(std::string text) {
    QString qstring = QString::fromStdString(text);
    printf("%s\n", text.c_str());
    //MainWindow::label.setText(qstring);
};
