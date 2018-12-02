// resulttableview.c++
#include "resulttableview.h++"

ResultTableView::ResultTableView(QWidget *parent) : QTableView(parent) {
    this->verticalHeader()->setVisible(false);
    this->horizontalHeader()->setVisible(false);
    this->setShowGrid(false);
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
    this->setColumnWidth(1, this->width() / 10 * 9);
}
