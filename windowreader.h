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

    virtual ~WindowReader();

private slots:
    void on_buttonBox_accepted();
    void on_fillPushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

private:
    QStandardItemModel *model;
    Ui::WindowReader *ui;
};

#endif // WINDOWREADER_H
