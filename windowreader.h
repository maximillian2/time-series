#ifndef WINDOWREADER_H
#define WINDOWREADER_H

#include "seriesReader.h"
#include <QTableView>
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

private:

    Ui::WindowReader *ui;
};

#endif // WINDOWREADER_H
