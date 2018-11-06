// mainwindow.h++
#ifndef H_MAINWINDOW
#define H_MAINWINDOW
#include <QApplication>
#include <QLabel>
#include <QtWidgets>
#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QGroupBox>
#include <QAction>
#include <QMutex>
#include <QMenuBar>
#include <QMenu>
#include <QTabWidget>
#include <QPlainTextEdit>
#include <QMetaType>
#include <QPixmap>
#include <memory>

#include "models/track.h++"
#include "models/playlist.h++"
#include "messagehandler.h++"
#include <json.h++>

#ifdef WIN32
    #include <io.h>
#else
    #include <unistd.h>
#endif

class MainWindow : public QWidget {
    Q_OBJECT
    
    public:
        MainWindow(MessageHandler *messageHandler);
        //void set_wsc(WebSocketClientQt *wsc);
        QPushButton get_searchBtn();
        
    private:
        MessageHandler *messageHandler;
        QLabel label;
        QPlainTextEdit plainText;
		mutable QMutex mutex;
        QMenuBar menuBar;
        QMenu mainMenu;
        QMenu aboutMenu;
        QAction settingsAction;
        QAction quitAction;
        
        QGroupBox topBox;
        QPushButton previousSong;
        QPushButton togglePlay;
        QPushButton nextSong;
        QLineEdit searchInput;
        QPushButton searchBtn;
        
        QGroupBox contentBox;

        QPixmap coverImage;
        QLabel coverLabel;
        QLabel title;
        QLabel album;
        QLabel artist;

        Playlist playlistModel;
        QListView playlistView;

        QGroupBox bottomBox;
        QLabel connectionStatusLabel;
        QPushButton connectWSBtn;
        
        std::shared_ptr<Track> track;
        std::vector<Track> playlist;

    protected:
        void closeEvent(QCloseEvent*);
    
    private slots:
        void quit_application();
        void search_artist();
        void replace_playlist(std::vector<std::shared_ptr<Track>> playlist);
        void set_current_song(std::shared_ptr<Track> track);
        void update_label_text(nlohmann::json msg);
        
};

#endif
