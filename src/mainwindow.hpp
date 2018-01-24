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
#include <unistd.h>

#include "settings.hpp"
#include "ws_client.hpp"
#include <json.hpp>

class MainWindow : public QWidget {
    Q_OBJECT
    
    public:
        MainWindow(QWidget *parent = 0);
        void update_label_text(std::string text);
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
        QGroupBox searchBox;
        QPushButton searchBtn;
        QLineEdit searchInput;
        
    protected:
        void closeEvent(QCloseEvent*);
    
    private slots:
        void show_settings();
        void quit_application();
        void search_artist();
        
};

#endif
