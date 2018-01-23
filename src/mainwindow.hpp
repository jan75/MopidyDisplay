// mainwindow.hpp
#ifndef H_MAINWINDOW
#define H_MAINWINDOW
#include <QApplication>
#include <QLabel>
#include <QtWidgets>
#include <QWidget>
#include <QLineEdit>
#include <QGroupBox>
#include <QMutex>

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
        QLabel label;
		mutable QMutex mutex;
        QPushButton btnConnectWS;
        QLineEdit inputWSAddress;
        QGroupBox connectBox;
        QString placeholderConnectionStr;
    
    private slots:
        void connect_ws();
        
};

#endif
