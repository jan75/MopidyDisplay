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
    previousSong.setMaximumWidth(20);
    togglePlay.setText("Play");
    togglePlay.setMaximumWidth(60);
    nextSong.setText(">");
    nextSong.setMaximumWidth(20);
    
    searchInput.setMaximumWidth(150);
    searchBtn.setText("Search Artist");
    
    barLayout->addWidget(&previousSong);
    barLayout->addWidget(&togglePlay);
    barLayout->addWidget(&nextSong);
    barLayout->addWidget(&currentSong);
    barLayout->addStretch();
    barLayout->addWidget(&searchInput);
    barLayout->addWidget(&searchBtn);
    //connectBox.setFlat(true);
    topBox.setLayout(barLayout);
    connect(&searchBtn, SIGNAL(clicked()), this, SLOT(search_artist()));
    
    // implement this for scaling and stuff: 
    // https://stackoverflow.com/questions/8211982/qt-resizing-a-qlabel-containing-a-qpixmap-while-keeping-its-aspect-ratio
    QVBoxLayout *playLayout = new QVBoxLayout;
    coverImage.load("/home/jan/mnt/Musik/Faithless/2005 - Forever Faithless_ The Greatest Hits/Cover.jpg");
    coverLabel.setScaledContents(true);
    coverLabel.setMaximumWidth(450);
    coverLabel.setMaximumHeight(450);
    //coverLabel.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    coverLabel.setAlignment(Qt::AlignHCenter);
    coverLabel.setPixmap(coverImage);
    title.setText("Insomnia");
    album.setText("Forever Faithless - The Greatest Hits");
    artist.setText("Faithless");
    playLayout->addWidget(&coverLabel);
    playLayout->addWidget(&title);
    playLayout->addWidget(&album);
    playLayout->addWidget(&artist);
    playBox.setFlat(true);
    playBox.setLayout(playLayout);
    
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    connectWSBtn.setText("Connect");
    connectionStatusLabel.setText("Not connected");
    bottomLayout->addWidget(&connectWSBtn);
    bottomLayout->addWidget(&connectionStatusLabel);
    bottomBox.setFlat(true);
    bottomBox.setLayout(bottomLayout);
    connect(&connectWSBtn, SIGNAL(clicked()), this, SLOT(slot_connect()));

    
    layout->addWidget(&topBox);
    layout->addWidget(&playBox);
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

void MainWindow::slot_connect() {
    bool result = settingsWindow.connect_ws();
    if(result == true) {
        connectionStatusLabel.setText("Connected");
    } else {
        connectionStatusLabel.setText("Connection failed");
    }
}
