#ifndef WINDOWREADER_H
#define WINDOWREADER_H

#include "seriesReader.h"
#include <QTableView>
#include <QDialog>
#include <QStandardItemModel>
namespace Ui {
class WindowReader;
}

class WindowReader : public QDialog, public SeriesReader
{
    Q_OBJECT

public:
    explicit WindowReader(QWidget *parent = 0);
    ~WindowReader();

private slots:

    void on_buttonBox_accepted();

    void on_fillPushButton_clicked();

private:
    QStandardItemModel *model;
    Ui::WindowReader *ui;
};

#endif // WINDOWREADER_H
