// album.h++
#ifndef H_ALBUM
#define H_ALBUM
#include <QString>
#include <QSettings>
#include <QListWidgetItem>
#include <memory>
#include <iostream>
#include <json.h++>

class Album {
    public:
        Album(QString name);

        void set_name(QString name);
        QString get_name();
        
    private:
        QString name;
};

#endif
