#include "help.h"
#include "ui_help.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>

Help::Help(QWidget *parent) : QDialog(parent), ui(new Ui::Help)
{
    ui->setupUi(this);

    QFile file(":/manual_page.text");
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0, "File error!", file.errorString());

    QTextStream stream(&file);
    stream.setCodec("UTF-8");

    ui->textBrowser->setText(stream.readAll());
}

Help::~Help()
{
    delete ui;
}

void Help::on_pushButton_clicked()
{
    this->reject();
}
