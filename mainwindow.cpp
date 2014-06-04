#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene.h"
#include "bayesian.h"
#include "markovmodel.h"
#include "seriesReader.h"
#include "fuzzyset.h"
#include "neuralnetwork.h"
#include "help.h"

#include <QtDebug>
#include <QFileDialog>
#include <QtDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    seriesReader = 0;
    predicted = false;

    connect(ui->actionInsert_Data, SIGNAL(triggered()), this, SLOT(insertData()));
    connect(ui->actionOpen_file, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exitApplication()));

    connect(ui->actionOnline_manual, SIGNAL(triggered()), this, SLOT(onlineHelp()));
    connect(ui->actionOffline_Manual, SIGNAL(triggered()), this, SLOT(offlineHelp()));
    connect(ui->actionAbout_Series, SIGNAL(triggered()), this, SLOT(aboutSeries()));

    activeFileLabel = new QLabel("Using: nothing");
    ui->statusbar->addWidget(activeFileLabel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calculatePushButton_clicked()
{

    if(!predicted)
    {
        qDebug() << "before predict";
        predictor->predict(ui->predictPeriodSpinBox->text().toInt());
        predicted = true;
        qDebug() << "after";
    }

//    vector<double> x = {543,323,432,543,323,453,435,234,542};
//    vector<double> y = {654,345,345,324,564,495};
//    vector<double> z = {654,345,340,320,494,490};
//     qDebug() << "result";
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
    if ( !seriesReader )
        delete seriesReader;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text files (*.txt)"));

//    qDebug() << fileName;

    QFileInfo fileInfo(fileName);
    activeFileLabel->setText(QString("Using: %1").arg(fileInfo.fileName()));

    seriesReader = new FileReader(fileName.toStdString());
    predictor = new Bayesian(seriesReader);
    ui->groupBox->setEnabled(true);
    ui->calculatePushButton->setEnabled(true);
}

void MainWindow::saveFile()
{
    qDebug() << "Not available yet.";
}

void MainWindow::insertData()
{
    if ( !seriesReader )
        delete seriesReader;

    windowReader = new WindowReader(this);
    seriesReader = windowReader;

    windowReader->show();

    activeFileLabel->setText(QString("Using: program input"));

    ui->groupBox->setEnabled(true);
    ui->calculatePushButton->setEnabled(true);
}

void MainWindow::offlineHelp()
{
    Help *help = new Help(this);
    help->show();
}

void MainWindow::onlineHelp()
{
    QDesktopServices::openUrl(QUrl("https://github.com/maximillian2/time-series/wiki/%D0%94%D0%BE%D0%BF%D0%BE%D0%BC%D0%BE%D0%B3%D0%B0-%D0%BF%D0%BE-Time-Series"));
}

void MainWindow::aboutSeries()
{
    QMessageBox::about(this, tr("Про Time Series"),
            tr("<h2>Time Series 1.0</h2>"
               "<p>Copyright &copy; 2014 GoogleKiller Inc."
               "<p>Time Series - це застосування для "
               "моделювання часових рядів з використанням  "
               "графіків."));
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
    predicted = false;
    if(!seriesReader)
        QMessageBox::warning(this, "No active file", "Select file or other source of data.");
    else
        switch(index)
        {
        case 0:
            delete predictor;
            predictor  = new Bayesian(seriesReader);
        break;

        case 1:
            delete predictor;
            predictor = new FuzzySet(seriesReader);
        break;

        case 2:
            delete predictor;
            predictor = new NeuralNetwork(seriesReader);
        break;

        case 3:
            delete predictor;
            predictor = new MarkovModel(seriesReader);
        break;
        }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    ofstream out((dir.toStdString() + "/result.txt").c_str());

    vector<double> res = predictor->getResultValues();

    for ( int i = 0; i < res.size(); ++i ) {
        out << res[i] << ", ";
    }
}
