#include "windowreader.h"
#include "ui_windowreader.h"

WindowReader::WindowReader(QWidget *parent) : QDialog(parent), ui(new Ui::WindowReader)
{
    ui->setupUi(this);
}

WindowReader::~WindowReader()
{
    delete ui;
}

void WindowReader::on_tableView_clicked(const QModelIndex &index)
{

}
