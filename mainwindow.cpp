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
    seriesReader = 0;
    predicted = false;

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exitApplication()));
    connect(ui->actionOpen_file, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionInsert_Data, SIGNAL(triggered()), this, SLOT(insertData()));

    activeFileLabel = new QLabel("Using: nothing");
    ui->statusbar->addWidget(activeFileLabel);

    ui->calculatePushButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calculatePushButton_clicked()
{

    if(!predicted)
    {
        predictor->setPartsInSeason(ui->partsSpinBox->value());
        predictor->predict(ui->predictPeriodSpinBox->text().toInt());
        predicted = true;
//        qDebug() << "Entered";
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

    qDebug() << fileName;

    QFileInfo fileInfo(fileName);
    activeFileLabel->setText(QString("Using: %1").arg(fileInfo.fileName()));

    seriesReader = new FileReader(fileName.toStdString());
    predictor = new Bayesian(seriesReader);
    ui->calculatePushButton->setEnabled(true);
}

void MainWindow::saveFile()
{
    qDebug() << "Not available yet.";
}

void MainWindow::insertData()
{
    windowReader = new WindowReader;
    seriesReader = windowReader;

    windowReader->show();


    ui->calculatePushButton->setEnabled(true);
    qDebug() << "linked";
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
    //        delete predictor;
    //        predictor = new FuzzySet();
        break;

        case 2:
    //        delete predictor;
    //        predictor = new NeuralSet();
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
