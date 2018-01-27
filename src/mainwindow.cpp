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
    
    QHBoxLayout *barLayout = new QHBoxLayout;
    previousSong.setText("<");
    togglePlay.setText("Play");
    nextSong.setText(">");
    currentSong.setText("-");    
    searchBtn.setText("Search Artist");
    
    barLayout->addWidget(&previousSong);
    barLayout->addWidget(&togglePlay);
    barLayout->addWidget(&nextSong);
    barLayout->addWidget(&currentSong);
    barLayout->addWidget(&searchInput);
    barLayout->addWidget(&searchBtn);
    //connectBox.setFlat(true);
    topBox.setLayout(barLayout);
    connect(&searchBtn, SIGNAL(clicked()), this, SLOT(search_artist()));
    
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    connectWSBtn.setText("Connect");
    connectionStatusLabel.setText("Not connected");
    bottomLayout->addWidget(&connectWSBtn);
    bottomLayout->addWidget(&connectionStatusLabel);
    bottomBox.setFlat(true);
    bottomBox.setLayout(bottomLayout);
    
    layout->addWidget(&topBox);
    layout->addWidget(&plainText);
    //layout->addWidget(&label);
    layout->addWidget(&bottomBox);
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
}

void MainWindow::update_label_text(QString qText) {
	QMutexLocker locker(&mutex);
    
    std::string textStr = qText.toStdString();
    json json_test = json::parse(qText.toStdString());
    QString qPrettyJson = QString::fromStdString(json_test.dump(4));
    
    plainText.clear();
    plainText.appendPlainText(qPrettyJson);
    //label.setText(qText);
};

void MainWindow::set_current_song(QString qText) {
    currentSong.setText(qText);
}
