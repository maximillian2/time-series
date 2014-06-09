#include "windowreader.h"
#include "ui_windowreader.h"

#include <QStandardItem>
#include <QtDebug>
#include <QMessageBox>

WindowReader::WindowReader(QWidget *parent) : QDialog(parent), ui(new Ui::WindowReader)
{
    ui->setupUi(this);
    model = new QStandardItemModel(2, ui->spinBox->value(), this);

    ui->tableView->horizontalHeader()->hide();
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->fillPushButton->setEnabled(false);
    ui->buttonBox->setEnabled(false);
}

WindowReader::~WindowReader()
{
    delete ui;
}

void WindowReader::on_buttonBox_accepted()
{
    for(int i = 0; i < model->columnCount(); i++)
    {
        if(!model->item(0, i)->text().isEmpty() && !model->item(1, i)->text().isEmpty())
        {
            keys.push_back(model->item(0, i)->text().toStdString());
            values.push_back(model->item(1, i)->text().toDouble());
            qDebug() << "k = " << model->item(0,i)->text().toLatin1() << "; v = " << model->item(1,i)->text().toDouble();
        } else {
            QMessageBox::warning(this, "Пусте поле", "Перевірте правильність введення даних.");
            this->reject();
            break;
        }
    }
}

void WindowReader::on_fillPushButton_clicked()
{
    for (int row = 0; row < 2; ++row)
    {
        for (int column = 0; column < ui->spinBox->value(); ++column)
        {
            QStandardItem* item = new QStandardItem();
            model->setItem(row, column, item);
        }
    }
    ui->tableView->setModel(model);

    ui->buttonBox->setEnabled(true);
}

void WindowReader::on_spinBox_valueChanged(int value)
{
    if (value)
        ui->fillPushButton->setEnabled(true);
    else
        ui->fillPushButton->setEnabled(false);
}
