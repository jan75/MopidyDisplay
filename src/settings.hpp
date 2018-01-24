// settings.hpp
#ifndef H_SETTINGS
#define H_SETTINGS
#include <QApplication>
#include <QtWidgets>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QTabWidget>
#include <unistd.h>

#include "ws_client.hpp"
#include <json.hpp>

class SettingsWindow : public QTabWidget {
    Q_OBJECT
    
    public:
        SettingsWindow(QTabWidget *parent = 0);
        void set_wsc(WebSocketClient *wsc);
        
    private:
        WebSocketClient *wsc;
        MainWindow *mainWindow;

        QWidget connectionSettings;
        QPushButton btnConnectWS;
        QLineEdit inputWSAddress;
        QGroupBox connectBox;
        QString placeholderConnectionStr;
        QLabel connectionStatus;
        
    private slots:
        void connect_ws();
};

#endif
