// resulttableview.c++
#include "resulttableview.h++"

ResultTableView::ResultTableView(QWidget *parent) : QTableView(parent) {
    this->horizontalHeader()->setStretchLastSection(true);
    this->verticalHeader()->setVisible(false);
}

ResultTableView::~ResultTableView() {

}

void ResultTableView::resizeEvent(QResizeEvent *event) {
    if(event->type() == QResizeEvent::Resize) {
        this->resizeColumns();
    }
}

void ResultTableView::resizeColumns() {
    this->setColumnWidth(0, this->width() / 10 * 1);
    this->setColumnWidth(1, this->width() / 10 * 6);
    this->setColumnWidth(2, this->width() / 10 * 3);
}
