// resulttableview.h++
#ifndef H_RESULTTABLEVIEW
#define H_RESULTTABLEVIEW
#include <QString>
#include <QTableView>
#include <QHeaderView>
#include <QResizeEvent>
#include <memory>
#include <iostream>

class ResultTableView : public QTableView {

    public:
        ResultTableView(QWidget *parent = nullptr);

        void resizeEvent(QResizeEvent *event) override;

        ~ResultTableView() override;

    private:
        void resizeColumns();
};

#endif
