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
    quit_application();
}

void MainWindow::show_settings() {
    settingsWindow.show();
}

void MainWindow::quit_application() {
    qApp->quit();
}

void MainWindow::search_artist() {
    bool connected = wsc->get_connected();
    if(connected != false) {
        QString query = searchInput.text();
        std::string queryStr = query.toStdString();
        json queryJson;
        queryJson = {
            {"jsonrpc", "2.0"},
            {"id", 1},
            {"method", "core.library.find_exact"},
            {"params", {
                {"artist", "default"},
            }}
        };
        queryJson["params"]["artist"] = queryStr;
        //std::cout << queryJson.dump(4) << std::endl;
        wsc->send_ws(queryJson.dump());
    }
}

void MainWindow::set_wsc(WebSocketClient *wscParam) {
    this->wsc = wscParam;
    settingsWindow.set_wsc(wscParam);
    connect(wsc, &WebSocketClient::dispatch_message, this, &MainWindow::update_label_text);
}

void MainWindow::update_label_text(QString qText) {
	QMutexLocker locker(&mutex);
    //json json_test;
    //json_test = json::parse(text);
    plainText.clear();
    plainText.appendPlainText(qText);
    //label.setText(qText);
};
