#ifndef WINDOWREADER_H
#define WINDOWREADER_H

#include "seriesReader.h"
#include <QDialog>

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
    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::WindowReader *ui;
};

#endif // WINDOWREADER_H
