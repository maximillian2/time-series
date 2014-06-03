#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QLabel>
#include "scene.h"
#include "fileReader.h"
#include "seriesReader.h"
#include "tsPrediction.h"

namespace Ui {
class MainWindow;
}

class Builder;

class MainWindow : public QMainWindow, public SeriesReader
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_fillPushButton_clicked();
    void on_calculatePushButton_clicked();
    void on_onSeasonRadioButton_clicked();
    void on_offSeasonRadioButton_clicked();
    void on_comboBox_currentIndexChanged(int index);

    void on_actionSave_as_triggered();

public slots:
    void exitApplication();
    void openFile();
    void saveFile();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    Scene *scene;
    TsPredictor *predictor;
    SeriesReader *fileReader;
    QLabel *activeFileLabel;
};

#endif // MAINWINDOW_H
