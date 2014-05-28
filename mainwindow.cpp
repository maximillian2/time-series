#include "mainwindow.h"
#include "ui_mainwindow.h"

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
