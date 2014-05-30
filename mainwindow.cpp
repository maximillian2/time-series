#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene.h"
#include <QtDebug>
#include <QTextCodec>
#include <QFileDialog>
#include <QtDebug>
#include <iostream>
#include "bayesian.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    model = new QStandardItemModel(2, ui->spinBox->value(), this);
    predictor = new Bayesian();

    ui->tableView->horizontalHeader()->hide();
<<<<<<< HEAD
    //ui->tableView->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    //ui->tableView->verticalHeader()->setResizeMode(QHeaderView::Stretch);
=======
//    ui->tableView->verticalHeader()->setResizeMode(QHeaderView::Stretch);
>>>>>>> 1e33b15bd1660d8135731b58fdb0cf447ccfdf51

    connect(ui->actionExit, SIGNAL(activated()), this, SLOT(exitApplication()));
    connect(ui->actionOpen_file, SIGNAL(activated()), this, SLOT(openFile()));
    connect(ui->actionSave, SIGNAL(activated()), this, SLOT(saveFile()));
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
    {
        keys.push_back(model->item(0, i)->text().toStdString());
        values.push_back(model->item(1, i)->text().toDouble());
    }

    predictor->predict(ui->partsSpinBox->text().toInt());
    scene = new Scene(values /*source vector*/, predictor->getResultValues() /* result vector */ );

//    scene->show();
}

void MainWindow::exitApplication()
{
    QCoreApplication::exit();
}

void MainWindow::openFile()
{
//    delete fileReader;
//    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text files (*.txt)"));
//    fileReader = new FileReader(fileName.toStdString());
}

void MainWindow::saveFile()
{

}

void MainWindow::on_onSeasonRadioButton_clicked()
{
    predictor->seriesType = TsPredictor::WITH_SEASONAL_VARIATON;
    predictor->setPartsInSeason(ui->partsSpinBox->text().toInt());
}

void MainWindow::on_offSeasonRadioButton_clicked()
{
    predictor->seriesType = TsPredictor::WITHOUT_SEASONAL_VARIATON;
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
        delete predictor;
        predictor  = new Bayesian();
    break;

    case 1:
        delete predictor;

    break;

    case 2:
        delete predictor;

    break;

    case 3:
        delete predictor;

        break;


    }
}
