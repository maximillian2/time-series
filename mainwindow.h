#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "scene.h"
#include "fileReader.h"
#include "seriesReader.h"
#include "tsPredictor.h"
#include "windowreader.h"

namespace Ui {
class MainWindow;
}

class Builder;
class WindowReader;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
    
private slots:
    void on_calculatePushButton_clicked();
    void on_onSeasonRadioButton_clicked();
    void on_offSeasonRadioButton_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_actionSave_as_triggered();

public slots:
    void exitApplication();
    void openFile();
    void insertData();
    void offlineHelp();
    void onlineHelp();
    void aboutSeries();

private:
    Ui::MainWindow *ui;
    Scene *scene;
    TsPredictor *predictor;
    SeriesReader *seriesReader;
    QLabel *activeFileLabel;
    WindowReader *windowReader;
};

#endif // MAINWINDOW_H
