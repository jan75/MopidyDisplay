// mainwindow.cpp
#include "mainwindow.hpp"

using nlohmann::json;

MainWindow::MainWindow(MessageHandler *messageHandler) {
    /* === OBJECTS === */
    this->messageHandler = messageHandler;

    /* === UI ELEMENTS === */
    QVBoxLayout *layout = new QVBoxLayout;

    // MENUBAR
    mainMenu.setTitle("Action");
    quitAction.setText("Quit");
    mainMenu.addAction(&quitAction);
    menuBar.addMenu(&mainMenu);
    aboutMenu.setTitle("Help");
    aboutMenu.addAction("Help");
    aboutMenu.addAction("About");
    menuBar.addMenu(&aboutMenu);
    layout->setMenuBar(&menuBar);

    // CONTROL BAR
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
    barLayout->addWidget(&title);
    barLayout->addStretch();
    barLayout->addWidget(&searchInput);
    barLayout->addWidget(&searchBtn);
    topBox.setLayout(barLayout);

    // PLAY LAYOUT
    QVBoxLayout *playLayout = new QVBoxLayout;
    coverImage.load("C:/Users/Jan Ackermann/git/MopidyDisplay/media/images/placeholder_small.jpg");
    coverLabel.setScaledContents(true);
    coverLabel.setMaximumWidth(450);
    coverLabel.setMaximumHeight(450);
    //coverLabel.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    coverLabel.setAlignment(Qt::AlignHCenter);
    coverLabel.setPixmap(coverImage);
    title.setText("<title>");
    album.setText("<album>");
    artist.setText("<artist>");
    playLayout->addWidget(&coverLabel); // https://stackoverflow.com/questions/8211982/qt-resizing-a-qlabel-containing-a-qpixmap-while-keeping-its-aspect-ratio
    playLayout->addWidget(&title);
    playLayout->addWidget(&album);
    playLayout->addWidget(&artist);
    playBox.setFlat(true);
    playBox.setLayout(playLayout);

    // TEXT AREA
    plainText.setLineWrapMode(QPlainTextEdit::WidgetWidth);
    plainText.setReadOnly(true);

    // FOOTER
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    connectWSBtn.setText("Connect");
    connectionStatusLabel.setText("Not connected");
    bottomLayout->addWidget(&connectWSBtn);
    bottomLayout->addWidget(&connectionStatusLabel);
    bottomBox.setFlat(true);
    bottomBox.setLayout(bottomLayout);

    // COMPLETE LAYOUT
    layout->addWidget(&topBox);
    layout->addWidget(&playBox);
    layout->addWidget(&plainText);
    layout->addWidget(&bottomBox);
    setLayout(layout);

    /* === SIGNALS === */
    connect(messageHandler, &MessageHandler::text_msg_received, this, &MainWindow::update_label_text);
    connect(&quitAction, &QAction::triggered, this, &MainWindow::quit_application);
    connect(&searchBtn, &QPushButton::clicked, this, &MainWindow::search_artist);
    connect(&connectWSBtn, &QPushButton::clicked, messageHandler, &MessageHandler::connect_ws);
};

void MainWindow::closeEvent(QCloseEvent*) {
    quit_application();
}

void MainWindow::quit_application() {
    qApp->quit();
}

void MainWindow::search_artist() {
    /*
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
    */
}

void MainWindow::update_label_text(nlohmann::json msg) {
    QString qPrettyJson = QString::fromStdString(msg.dump(2));
    std::cout << msg << std::endl;
    
    plainText.clear();
    plainText.appendPlainText(qPrettyJson);
    //label.setText(qText);
};

void MainWindow::set_current_song(std::shared_ptr<Track> track) {
    this->track = track;
    std::cout << "Changing track to " << track->get_title().toStdString() << std::endl;
    title.setText(track->get_title());
    album.setText(track->get_album());
    artist.setText(track->get_artist());
    if(track->has_cover_path() == true) {
        std::cout << "setting cover path to " << track->get_cover_path().toStdString() << std::endl;
        coverImage.load(track->get_cover_path());
        coverLabel.setPixmap(coverImage);
    }
}
