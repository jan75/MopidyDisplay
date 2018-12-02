// playlisttableview.h++
#ifndef H_PLAYLISTTABLEVIEW
#define H_PLAYLISTTABLEVIEW
#include <QString>
#include <QTableView>
#include <QHeaderView>
#include <QResizeEvent>
#include <memory>
#include <iostream>

class PlaylistTableView : public QTableView {

    public:
        PlaylistTableView(QWidget *parent = nullptr);

        void resizeEvent(QResizeEvent *event) override;

        ~PlaylistTableView() override;

    private:
        void resizeColumns();
};

#endif
