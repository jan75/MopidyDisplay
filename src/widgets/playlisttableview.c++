// playlisttableview.c++
#include "playlisttableview.h++"

PlaylistTableView::PlaylistTableView(QWidget *parent) : QTableView(parent) {
    this->horizontalHeader()->setStretchLastSection(true);
    this->verticalHeader()->setVisible(false);
}

PlaylistTableView::~PlaylistTableView() {

}

void PlaylistTableView::resizeEvent(QResizeEvent *event) {
    if(event->type() == QResizeEvent::Resize) {
        this->resizeColumns();
    }
}

void PlaylistTableView::resizeColumns() {
    this->setColumnWidth(0, this->width() / 10 * 1);
    this->setColumnWidth(1, this->width() / 10 * 6);
    this->setColumnWidth(2, this->width() / 10 * 3);
}
