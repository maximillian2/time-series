#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "scene.h"
#include "fileReader.h"
#include "seriesReader.h"
#include "tsPrediction.h"
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
    bool predicted;

    ~MainWindow();
    
private slots:
    void on_calculatePushButton_clicked();
    void on_onSeasonRadioButton_clicked();
    void on_offSeasonRadioButton_clicked();
    void on_comboBox_currentIndexChanged(int index);

public slots:
    void exitApplication();
    void openFile();
    void saveFile();
    void insertData();

private:
    Ui::MainWindow *ui;
    Scene *scene;
    TsPredictor *predictor;
    SeriesReader *seriesReader;
    QLabel *activeFileLabel;
    WindowReader *windowReader;
};

#endif // MAINWINDOW_H
