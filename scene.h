#ifndef SCENE_H
#define SCENE_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <vector>

using namespace std;

namespace Ui {
class Scene;
}

class Scene : public QMainWindow
{
    Q_OBJECT

public:
    Scene(vector <double> source, vector <double> predict,QWidget *parent = 0);
    Scene(vector <double> source, vector <double> predict, vector<double> future, QWidget *parent = 0);
    ~Scene();

private slots:
    void on_pushButton_clicked();

private:
    int index;
    Ui::Scene *ui;
    QGraphicsScene *scene;
    vector <double> sourceSeries;
    vector <double> predictSeries;
    vector <double> futureSeries;
};

#endif // SCENE_H
