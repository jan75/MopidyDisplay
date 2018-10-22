// mainwindow.cpp
#include "mainwindow.hpp"

using nlohmann::json;

MainWindow::MainWindow(MessageHandler *messageHandler) {
    /* === OBJECTS === */
    this->messageHandler = messageHandler;

    /* === UI ELEMENTS === */
    QVBoxLayout *layout = new QVBoxLayout;

    /* === SETTINGS === */
    QSettings settings("metasoft", "mopidydisplay");
    settings.beginGroup("display");
    QString img_path = settings.value("cover", "/home/jan/git/MopidyDisplay/media/images/placeholder_small.jpg").toString();
    settings.endGroup();

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

    // SEARCH LAYOUT
    QVBoxLayout *playlistLayout = new QVBoxLayout;
    playlistList.addItem("Hello World!");
    playlistList.addItem("Hello World!");
    playlistList.addItem("Hello World!");
    playlistLayout->addWidget(&playlistList);

    // PLAY LAYOUT
    QVBoxLayout *playLayout = new QVBoxLayout;
    //coverImage.load(img_path);
    //coverLabel.setScaledContents(true);
    //coverLabel.setMaximumWidth(450);
    //coverLabel.setMaximumHeight(450);
    //coverLabel.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    //coverLabel.setAlignment(Qt::AlignHCenter);
    //coverLabel.setPixmap(coverImage);
    title.setText("<title>");
    album.setText("<album>");
    artist.setText("<artist>");
    //playLayout->addWidget(&coverLabel); // https://stackoverflow.com/questions/8211982/qt-resizing-a-qlabel-containing-a-qpixmap-while-keeping-its-aspect-ratio
    playLayout->addWidget(&title);
    playLayout->addWidget(&album);
    playLayout->addWidget(&artist);

    // CONTENT LAYOUT
    QHBoxLayout *contentLayout = new QHBoxLayout;
    contentLayout->addItem(playLayout);
    contentLayout->addItem(playlistLayout);
    contentBox.setLayout(contentLayout);

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
    layout->addWidget(&contentBox);
    layout->addWidget(&plainText);
    layout->addWidget(&bottomBox);
    setLayout(layout);

    /* === SIGNALS === */
    connect(messageHandler, &MessageHandler::text_msg_received, this, &MainWindow::update_label_text);
    connect(&quitAction, &QAction::triggered, this, &MainWindow::quit_application);
    connect(&searchBtn, &QPushButton::clicked, this, &MainWindow::search_artist);
    connect(&connectWSBtn, &QPushButton::clicked, messageHandler, &MessageHandler::connect_ws);
    connect(messageHandler, &MessageHandler::track_change, this, &MainWindow::set_current_song);
    connect(messageHandler, &MessageHandler::playlist_change, this, &MainWindow::replace_playlist);
};

void MainWindow::closeEvent(QCloseEvent*) {
    quit_application();
}

void MainWindow::quit_application() {
    qApp->quit();
}

void MainWindow::search_artist() {
    QString query = searchInput.text();
    messageHandler->search_artists(query);
}

void MainWindow::update_label_text(nlohmann::json msg) {
    //std::cout << "update_label_text" << std::endl;
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
}

void MainWindow::replace_playlist(std::vector<Track> playlist) {
    playlistList.clear();
    for(Track track: playlist) {
        playlistList.addItem(track.get_title());
    }
}
