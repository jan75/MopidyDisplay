// mainwindow.cpp
#include "mainwindow.hpp"

using nlohmann::json;

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {    
    plainText.setLineWrapMode(QPlainTextEdit::WidgetWidth);
    plainText.setReadOnly(true);

    QVBoxLayout *layout = new QVBoxLayout;
    
    mainMenu.setTitle("Action");
    
    settingsAction.setText("Settings");
    mainMenu.addAction(&settingsAction);
    
    quitAction.setText("Quit");
    mainMenu.addAction(&quitAction);
    
    menuBar.addMenu(&mainMenu);
    
    aboutMenu.setTitle("Help");
    aboutMenu.addAction("Help");
    aboutMenu.addAction("About");
    menuBar.addMenu(&aboutMenu);
    
    layout->setMenuBar(&menuBar);
    connect(&settingsAction, SIGNAL(triggered()), this, SLOT(show_settings()));
    connect(&quitAction, SIGNAL(triggered()), this, SLOT(quit_application()));
    
    QHBoxLayout *searchLayout = new QHBoxLayout;
    searchLayout->addWidget(&searchInput);
    searchBtn.setText("Search");
    searchLayout->addWidget(&searchBtn);
    //connectBox.setFlat(true);
    searchBox.setLayout(searchLayout);
    connect(&searchBtn, SIGNAL(clicked()), this, SLOT(search_artist()));
    
    layout->addWidget(&searchBox);
    layout->addWidget(&plainText);
    layout->addWidget(&label);
    setLayout(layout);
};

void MainWindow::closeEvent(QCloseEvent*) {
    qApp->quit();
}

void MainWindow::show_settings() {
    settingsWindow.show();
}

void MainWindow::quit_application() {
    qApp->quit();
}

void MainWindow::search_artist() {
    QString query = searchInput.text();
    std::string queryStr = query.toStdString();
    std::cout << queryStr << std::endl;
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
    plainText.clear();
    plainText.appendPlainText(qText);
};
