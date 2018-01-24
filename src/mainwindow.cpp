// mainwindow.cpp
#include "mainwindow.hpp"

using nlohmann::json;

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {    
    plainText.setLineWrapMode(QPlainTextEdit::WidgetWidth);
    plainText.setReadOnly(true);
    plainText.document()->setPlainText("You need to connect to a Mopidy server with web api enabled");

    QVBoxLayout *layout = new QVBoxLayout;
    
    settingsAction.setText("Settings");
    mainMenu.setTitle("Action");
    mainMenu.addAction(&settingsAction);
    mainMenu.addAction("Quit");
    menuBar.addMenu(&mainMenu);
    
    aboutMenu.setTitle("Help");
    aboutMenu.addAction("Help");
    aboutMenu.addAction("About");
    menuBar.addMenu(&aboutMenu);
    
    layout->setMenuBar(&menuBar);
    connect(&settingsAction, SIGNAL(triggered()), this, SLOT(show_settings()));
    
    //layout->addWidget(&connectBox);
    layout->addWidget(&plainText);
    layout->addWidget(&label);
    setLayout(layout);
};

void MainWindow::show_settings() {
    settingsWindow.show();
}

void MainWindow::set_wsc(WebSocketClient *wscParam) {
    this->wsc = wscParam;
    settingsWindow.set_wsc(wscParam);
}

void MainWindow::update_label_text(std::string text) {
	QMutexLocker locker(&mutex);
    //json json_test;
    //json_test = json::parse(text);
    QString qText = QString::fromStdString(text);
    plainText.document()->setPlainText(qText);
    //printf("%s\n", text.c_str());
    //label.setText(qText);
};
