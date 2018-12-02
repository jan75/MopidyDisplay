// mainwindow.c++
#include "mainwindow.h++"

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
    searchInput.setMaximumWidth(150);
    searchBtn.setText("Search Artist");
    barLayout->addWidget(&previousSong);
    barLayout->addWidget(&togglePlay);
    barLayout->addWidget(&nextSong);
    barLayout->addStretch();
    //barLayout->addWidget(&coverLabel); // https://stackoverflow.com/questions/8211982/qt-resizing-a-qlabel-containing-a-qpixmap-while-keeping-its-aspect-ratio
    barLayout->addWidget(&title);
    barLayout->addWidget(&album);
    barLayout->addWidget(&artist);
    barLayout->addStretch();
    barLayout->addWidget(&searchInput);
    barLayout->addWidget(&searchBtn);
    topBox.setLayout(barLayout);

    // SEARCH LAYOUT
    QVBoxLayout *searchLayout = new QVBoxLayout;
    artistSearchView.setModel(&artistSearchModel);
    albumSearchView.setModel(&albumSearchModel);
    trackSearchView.setModel(&trackSearchModel);
    searchLayout->addWidget(&artistSearchView);
    searchLayout->addWidget(&albumSearchView);
    searchLayout->addWidget(&trackSearchView);

    // PLAYLIST LAYOUT
    QVBoxLayout *playlistLayout = new QVBoxLayout;
    playlistView.setModel(&playlistModel);
    playlistLayout->addWidget(&playlistView);


    // CONTENT LAYOUT
    QHBoxLayout *contentLayout = new QHBoxLayout;
    contentLayout->addItem(searchLayout);
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
    connect(messageHandler, &MessageHandler::search_results, this, &MainWindow::replace_searchresults);
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
    QString qPrettyJson = QString::fromStdString(msg.dump(2));
    
    plainText.clear();
    plainText.appendPlainText(qPrettyJson);
    //label.setText(qText);
};

/**
 * @brief Update labels to represent current playing song
 * @param track
 */
void MainWindow::set_current_song(std::shared_ptr<Track> track) {
    this->track = track;
    std::cout << "Changing track to " << track->get_title().toStdString() << std::endl;
    title.setText(track->get_title());
    album.setText(track->get_album());
    artist.setText(track->get_artist());
}

void MainWindow::replace_playlist(std::vector<std::shared_ptr<Track>> playlist) {
    playlistModel.clearItems();
    this->playlistModel.addTracks(playlist);
}

void MainWindow::replace_searchresults(std::set<std::shared_ptr<Artist>> artists, std::set<std::shared_ptr<Album>> albums, std::vector<std::shared_ptr<Track>> tracks) {
    artistSearchModel.clearItems();

    // Mocking data
    std::shared_ptr<Artist> artist1 = std::make_shared<Artist>("Nightwish");
    std::shared_ptr<Artist> artist2 = std::make_shared<Artist>("Ensiferum");
    std::shared_ptr<Album> album1 = std::make_shared<Album>("Once");
    std::shared_ptr<Album> album2 = std::make_shared<Album>("Devi'ls Got a new Disguise");
    std::shared_ptr<Track> track1 = std::make_shared<Track>("Track 1", "Album", "Nightwish", 3600, 1);
    std::shared_ptr<Track> track2 = std::make_shared<Track>("Track 2", "Album", "Nightwish", 3600, 1);
    std::shared_ptr<Track> track3 = std::make_shared<Track>("Track 3", "Album", "Nightwish", 3600, 1);
    std::shared_ptr<Track> track4 = std::make_shared<Track>("Track 4", "Album", "Nightwish", 3600, 1);
    std::shared_ptr<Track> track5 = std::make_shared<Track>("Track 5", "Album", "Nightwish", 3600, 1);
    std::shared_ptr<Track> track6 = std::make_shared<Track>("Track 6", "Album", "Nightwish", 3600, 1);
    std::shared_ptr<Track> track7 = std::make_shared<Track>("Track 7", "Album", "Nightwish", 3600, 1);
    std::shared_ptr<Track> track8 = std::make_shared<Track>("Track 8", "Album", "Nightwish", 3600, 1);
    std::shared_ptr<Track> track9 = std::make_shared<Track>("Track 9", "Album", "Nightwish", 3600, 1);

    this->artistSearchModel.addArtist(artist1);
    this->artistSearchModel.addArtist(artist2);
    this->albumSearchModel.addAlbum(album1);
    this->albumSearchModel.addAlbum(album2);
    this->trackSearchModel.addTrack(track1);
    this->trackSearchModel.addTrack(track2);
    this->trackSearchModel.addTrack(track3);
    this->trackSearchModel.addTrack(track4);
    this->trackSearchModel.addTrack(track5);
    this->trackSearchModel.addTrack(track6);
    this->trackSearchModel.addTrack(track7);
    this->trackSearchModel.addTrack(track8);
    this->trackSearchModel.addTrack(track9);
}
