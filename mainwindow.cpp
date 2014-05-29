#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QListIterator>
#include <vector>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QStandardItemModel(2, ui->spinBox->value(), this);

    ui->tableView->horizontalHeader()->hide();
    ui->tableView->verticalHeader()->setResizeMode(QHeaderView::Stretch);

    connect(ui->actionExit, SIGNAL(activated()), this, SLOT(applicationExit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fillPushButton_clicked()
{
    for (int row = 0; row < 2; ++row)
    {
        for (int column = 0; column < ui->spinBox->value(); ++column)
        {
            QStandardItem* item = new QStandardItem();
            model->setVerticalHeaderItem(0, new QStandardItem(QString(ui->unitLineEdit->text())));
            model->setVerticalHeaderItem(1, new QStandardItem(QString(ui->valuePerUnitEdit->text())));
            model->setItem(row, column, item);
        }
    }
    ui->tableView->setModel(model);
}

void MainWindow::applicationExit()
{
    QCoreApplication::exit();
}

void MainWindow::on_calculatePushButton_clicked()
{
    for(int i = 0; i < model->columnCount(); i++)
    {
        localMap.insert(std::make_pair(model->item(0, i)->text().toStdString(), model->item(1,i)->text().toDouble()));
//        localMap[model->item(0, i)->text()] = model->item(1,i)->text().toDouble();
//        localMap.insert(std::pair<std::string, double>(model->item(0, i)->text(), model->item(1, i)->text().toDouble()));
    }

    for(auto it : localMap)
        qDebug() << it.first << ' ' << it.second ;
//    for(auto it = localMap.begin(); it != localMap.end(); ++it)
//        qDebug() << it->first << ' ' << it->second;
}
