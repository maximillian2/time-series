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

const QString ONLINE_LINK = "https://github.com/maximillian2/time-series/wiki/%D0%94%D0%BE%D0%BF%D0%BE%D0%BC%D0%BE%D0%B3%D0%B0-%D0%BF%D0%BE-Time-Series";

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    seriesReader = 0;
    predictor    = 0;
    predictor = new Bayesian(seriesReader);

    connect(ui->actionInsert_Data,    SIGNAL(triggered()), this, SLOT(insertData()));
    connect(ui->actionOpen_file,      SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionExit,           SIGNAL(triggered()), this, SLOT(exitApplication()));

    connect(ui->actionOnline_manual,  SIGNAL(triggered()), this, SLOT(onlineHelp()));
    connect(ui->actionOffline_Manual, SIGNAL(triggered()), this, SLOT(offlineHelp()));
    connect(ui->actionAbout_Series,   SIGNAL(triggered()), this, SLOT(aboutSeries()));

    activeFileLabel = new QLabel("Нічого не використовуємо");
    ui->statusbar->addWidget(activeFileLabel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calculatePushButton_clicked()
{
    if (predictor->getResultValues().size())
        predictor->eraseResult();

    if ( ui->onSeasonRadioButton->isChecked() ) {

        predictor->seriesType = TsPredictor::WITH_SEASONAL_VARIATON;
        predictor->setPartsInSeason(ui->partsSpinBox->text().toInt());

    } else {
        predictor->seriesType = TsPredictor::WITHOUT_SEASONAL_VARIATON;
    }

    qDebug() << "before predict";
    predictor->predict(ui->predictPeriodSpinBox->text().toInt());
    qDebug() << "after";

    scene = new Scene(predictor->getSourceValues(), predictor->getResultValues() /* result vector */ );
    scene->show();

    ui->actionSave_as->setEnabled(true);

//    predictor->eraseResult();

}

void MainWindow::exitApplication()
{
    QCoreApplication::exit();
}

void MainWindow::openFile()
{
    if ( seriesReader )
        delete seriesReader;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Відкрити файл"), "", tr("Текстові файли (*.txt)"));
    if (!fileName.isEmpty())
    {
        QFileInfo fileInfo(/*fileName*/QString("/home/maxi/Qt_Projects/maximillian2-time-series/test.txt"));

        activeFileLabel->setText(QString("Використовуємо файл: %1").arg(fileInfo.fileName()));

        seriesReader = new FileReader(fileName.toStdString());
        predictor->setReader(seriesReader);

        ui->groupBox            ->setEnabled(true);
        ui->calculatePushButton ->setEnabled(true);
    }
}

void MainWindow::insertData()
{
    if ( seriesReader ) {
        delete seriesReader;
    }

    windowReader = new WindowReader(this);

    // 1 - accepted, 0 - rejected
    int result = windowReader->exec();

    if(result)
    {
        seriesReader = windowReader;

        activeFileLabel->setText(QString("Використовуємо: програмне введення"));

        ui->groupBox            ->setEnabled(true);
        ui->calculatePushButton ->setEnabled(true);
        predictor->setReader(seriesReader);
    }
    else
        activeFileLabel->setText(QString("Нічого не використовуємо"));
}

void MainWindow::offlineHelp()
{
    Help *help = new Help(this);
    help->exec();
}

void MainWindow::onlineHelp()
{
    QDesktopServices::openUrl(QUrl(ONLINE_LINK));
}

void MainWindow::aboutSeries()
{
    QMessageBox::about(this, ("Про Time Series"),
            ("<h2>Time Series 1.0</h2>"
               "<p>Copyright &copy; 2014 GoogleKiller Inc."
               "<p>Time Series - це застосування для "
               "моделювання часових рядів з використанням  "
               "графіків."));
}

void MainWindow::on_onSeasonRadioButton_clicked()
{
    ui->partsLabel->setEnabled(true);
    ui->partsSpinBox->setEnabled(true);
}

void MainWindow::on_offSeasonRadioButton_clicked()
{
    ui->partsLabel->setEnabled(false);
    ui->partsSpinBox->setEnabled(false);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(!seriesReader)
        QMessageBox::warning(this, "Нема активного джерела", "Виберіть джерело інформації.");
    else
    {
       if (predictor) delete predictor;

        ui->groupBox->setEnabled(true);
        switch(index)
        {
        case 0:
            predictor  = new Bayesian(seriesReader);
        break;

        case 1:
            predictor = new FuzzySet(seriesReader);
        break;

        case 2:
            predictor = new NeuralNetwork(seriesReader);
        break;

        case 3:
            predictor = new MarkovModel(seriesReader);
        break;

        default:
            ui->groupBox->setEnabled(false);
        }
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Відкрити директорію"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    ofstream out((dir.toStdString() + "/result.txt").c_str());

    vector<double> res = predictor->getResultValues();

    for (unsigned int i = 0; i < res.size(); ++i ) {
        out << res[i] << ", ";
    }
}
