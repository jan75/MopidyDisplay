// ui.hpp
#ifndef H_MAINWINDOW
#define H_MAINWINDOW
#include <QApplication>
#include <QLabel>
#include <QtWidgets>
#include <QWidget>

#include "ws_client.hpp"

class MainWindow : public QWidget {
    Q_OBJECT
    
    public:
        MainWindow(QWidget *parent = 0);
        void update_label_text(std::string text);
        
    private:
        QLabel label;
        
    signals:
        void overflow();
        void text_changed(std::string text);
        
};

#endif
