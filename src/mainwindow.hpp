// mainwindow.hpp
#ifndef H_MAINWINDOW
#define H_MAINWINDOW
#include <QApplication>
#include <QLabel>
#include <QtWidgets>
#include <QWidget>
#include <QMutex>

#include "ws_client.hpp"
#include <json.hpp>

class MainWindow : public QWidget {
    Q_OBJECT
    
    public:
        MainWindow(QWidget *parent = 0);
        void update_label_text(std::string text);
        
    private:
		mutable QMutex mutex;
        QLabel label;
        
    signals:
        void overflow();
        void text_changed(std::string text);
        
};

#endif
