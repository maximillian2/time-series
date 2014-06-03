#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene.h"
#include "bayesian.h"
#include "markovmodel.h"
#include "seriesReader.h"

#include <QtDebug>
#include <QFileDialog>
#include <QtDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel(2, ui->spinBox->value(), this);
    fileReader = 0;

    ui->tableView->horizontalHeader()->hide();
//    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exitApplication()));
    connect(ui->actionOpen_file, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));

    activeFileLabel = new QLabel("Using: nothing");
    ui->statusbar->addWidget(activeFileLabel);

    ui->calculatePushButton->setEnabled(false);
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
    static bool predicted = false;
    for(int i = 0; i < model->columnCount(); i++)
    {
        keys.push_back(model->item(0, i)->text().toStdString());
        values.push_back(model->item(1, i)->text().toDouble());
    }

    if(!predicted)
    {
        predictor->predict(ui->predictPeriodSpinBox->text().toInt());
        predicted = true;
        qDebug() << "Entered";
    }

//    vector<double> x = {543,323,432,543,323,453,435,234,542};
//    vector<double> y = {654,345,345,324,564,495};
//    vector<double> z = {654,345,340,320,494,490};
//    vector<double> result = predictor->getResultValues();
//    for(int i = 0; i < result.size(); i++)
//        qDebug() << "result = " << i;
    scene = new Scene(predictor->getSourceValues(), predictor->getResultValues() /* result vector */ );

//    scene = new Scene(x,y,z);
    scene->show();
}

void MainWindow::exitApplication()
{
    QCoreApplication::exit();
}

void MainWindow::openFile()
{
    if ( !fileReader )
        delete fileReader;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text files (*.txt)"));
    qDebug() << fileName;

    QFileInfo fileInfo(fileName);
    activeFileLabel->setText(QString("Using: %1").arg(fileInfo.fileName()));

    fileReader = new FileReader(fileName.toStdString());
    predictor = new Bayesian(fileReader);
    ui->calculatePushButton->setEnabled(true);
}

void MainWindow::saveFile()
{
    qDebug() << "Not available yet.";
}

void MainWindow::on_onSeasonRadioButton_clicked()
{
    predictor->seriesType = TsPredictor::WITH_SEASONAL_VARIATON;
    predictor->setPartsInSeason(ui->partsSpinBox->text().toInt());

    ui->partsLabel->setEnabled(true);
    ui->partsSpinBox->setEnabled(true);
}

void MainWindow::on_offSeasonRadioButton_clicked()
{
    predictor->seriesType = TsPredictor::WITHOUT_SEASONAL_VARIATON;

    ui->partsLabel->setEnabled(false);
    ui->partsSpinBox->setEnabled(false);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(!fileReader)
        QMessageBox::warning(this, "No active file", "Select file or other source of data.");
    else
        switch(index)
        {
        case 0:
            delete predictor;
            predictor  = new Bayesian(fileReader);
        break;

        case 1:
    //        delete predictor;
    //        predictor = new FuzzySet();
        break;

        case 2:
    //        delete predictor;
    //        predictor = new NeuralSet();
        break;

        case 3:
            delete predictor;
            predictor = new MarkovModel(fileReader);
        break;
        }
}
