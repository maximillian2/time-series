#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new Scene;

    model = new QStandardItemModel(2, ui->spinBox->value(), this);

    ui->tableView->horizontalHeader()->hide();
//    ui->tableView->verticalHeader()->setResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fillPushButton_clicked()
{
//    model->setHorizontalHeaderItem(0, new QStandardItem(QString(ui->unitLineEdit->text())));
//    model->setHorizontalHeaderItem(1, new QStandardItem(QString(ui->valuePerUnitEdit->text())));
        for (int row = 0; row < 2; ++row)
        {
            for (int column = 0; column < ui->spinBox->value(); ++column)
            {
//                QString text = QString('A' + row) + QString::number(column + 1);
                QStandardItem* item = new QStandardItem();
                model->setVerticalHeaderItem(0, new QStandardItem(QString(ui->unitLineEdit->text())));
                model->setVerticalHeaderItem(1, new QStandardItem(QString(ui->valuePerUnitEdit->text()))  );
                model->setItem(row, column, item);
            }
         }

        ui->tableView->setModel(model);

}

void MainWindow::on_calculatePushButton_clicked()
{
    for(int i = 0; i < model->columnCount(); i++)
    {
        localMap.insert(std::make_pair(model->item(0, i)->text().toStdString(), model->item(1,i)->text().toDouble()));
    }

    for(std::map<std::string, double>::iterator it = localMap.begin(); it != localMap.end(); ++it)
        qDebug() << (*it).first;

    scene->show();
}
