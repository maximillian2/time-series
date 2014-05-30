#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene.h"
#include <QtDebug>
#include <QTextCodec>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    model = new QStandardItemModel(2, ui->spinBox->value(), this);

    ui->tableView->horizontalHeader()->hide();
<<<<<<< HEAD
    //ui->tableView->verticalHeader()->setResizeMode(QHeaderView::Stretch);
=======
    ui->tableView->verticalHeader()->setResizeMode(QHeaderView::Stretch);

    connect(ui->actionExit, SIGNAL(activated()), this, SLOT(exitApplication()));
    connect(ui->actionOpen_file, SIGNAL(activated()), this, SLOT(openFile()));
    connect(ui->actionSave, SIGNAL(activated()), this, SLOT(saveFile()));
>>>>>>> 4936ba784bdf4270460e72b5d17644b151e3c628
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
            model->setVerticalHeaderItem(0, new QStandardItem(QString(ui->unitLineEdit->text() ) ) );
            model->setVerticalHeaderItem(1, new QStandardItem( QString(ui->valuePerUnitEdit->text() ) ) );
            model->setItem(row, column, item);
        }
    }
    ui->tableView->setModel(model);
}

void MainWindow::on_calculatePushButton_clicked()
{
    for(int i = 0; i < model->columnCount(); i++)
        localMap.insert(model->item(0, i)->text().toStdString(), model->item(1, i)->text().toDouble());

    scene = new Scene; // в параметрах передать мап, который запилит Сергей

    scene->show();
}

void MainWindow::exitApplication()
{
    QCoreApplication::exit();
}

void MainWindow::openFile()
{
    delete fileReader;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text files (*.txt)"));
    fileReader = new FileReader(fileName.toStdString());
}

void MainWindow::saveFile()
{

}
