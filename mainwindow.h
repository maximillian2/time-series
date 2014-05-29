#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "scene.h"

namespace Ui {
class MainWindow;
}

class Builder;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_fillPushButton_clicked();

    void on_calculatePushButton_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    Scene *scene;
};

#endif // MAINWINDOW_H
