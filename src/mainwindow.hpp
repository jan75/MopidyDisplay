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
#include <unistd.h>

#include "settings.hpp"
#include "ws_client.hpp"
#include <json.hpp>

class MainWindow : public QWidget {
    Q_OBJECT
    
    public:
        MainWindow(QWidget *parent = 0);
        //void update_label_text(std::string text);
        void set_wsc(WebSocketClient *wsc);
        
    private:
        WebSocketClient *wsc;
        SettingsWindow settingsWindow;
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
        QLabel currentSong;
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
        
    protected:
        void closeEvent(QCloseEvent*);
    
    private slots:
        void show_settings();
        void quit_application();
        void search_artist();
        void slot_connect();
        
    public slots:
        void set_current_song(QString qText);
        void update_label_text(QString qText);
        
};

#endif
