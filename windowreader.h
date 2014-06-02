#ifndef WINDOWREADER_H
#define WINDOWREADER_H

#include <QDialog>

#include "seriesReader.h"

namespace Ui {
class WindowReader;
}

class WindowReader : public QDialog, public SeriesReader
{
    Q_OBJECT
    
public:
    explicit WindowReader(QWidget *parent = 0);
    ~WindowReader();
    
private:
    Ui::WindowReader *ui;
};

#endif // WINDOWREADER_H
