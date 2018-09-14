// mainwindow.hpp
#ifndef H_MAINWINDOW
#define H_MAINWINDOW
#include <QApplication>
#include <QLabel>
#include <QtWidgets>
#include <QWidget>
#include <QLineEdit>
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

#include "models/track.hpp"
#include "messagehandler.hpp"
#include <json.hpp>

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
        
        QGroupBox playBox;
        QPixmap coverImage;
        QLabel coverLabel;
        QLabel title;
        QLabel album;
        QLabel artist;
        
        QGroupBox bottomBox;
        QLabel connectionStatusLabel;
        QPushButton connectWSBtn;
        
        std::shared_ptr<Track> track;
        
    protected:
        void closeEvent(QCloseEvent*);
    
    private slots:
        void quit_application();
        void search_artist();
        
    public slots:
        void set_current_song(std::shared_ptr<Track> track);
        void update_label_text(nlohmann::json msg);
        
};

#endif
