#include "windowreader.h"
#include "ui_windowreader.h"

#include <QStandardItem>
#include <QtDebug>
#include <iostream>

WindowReader::WindowReader(QWidget *parent) : QDialog(parent), ui(new Ui::WindowReader)
{
    ui->setupUi(this);
    model = new QStandardItemModel(2, ui->spinBox->value(), this);

    ui->tableView->horizontalHeader()->hide();
//    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

WindowReader::~WindowReader()
{
    delete ui;
}

void WindowReader::on_buttonBox_accepted()
{
        for(int i = 0; i < model->columnCount(); i++)
        {
            keys.push_back(model->item(0, i)->text().toStdString());
            values.push_back(model->item(1, i)->text().toDouble());
        }

        for ( int i; i < values.size(); ++i ) {
            std::cerr << "READ VALUE" << values[i] << std::endl;
        }

        qDebug() << "pushed up.";
}

void WindowReader::on_fillPushButton_clicked()
{
    for (int row = 0; row < 2; ++row)
    {
        for (int column = 0; column < ui->spinBox->value(); ++column)
        {
            QStandardItem* item = new QStandardItem();
            model->setVerticalHeaderItem(0, new QStandardItem(QString(ui->unitLineEdit->text() ) ) );
            model->setVerticalHeaderItem(1, new QStandardItem(QString(ui->valuePerUnitEdit->text() ) ) );
            model->setItem(row, column, item);
        }
    }
    ui->tableView->setModel(model);
}
