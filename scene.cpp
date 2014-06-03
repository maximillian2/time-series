#include "scene.h"
#include "ui_scene.h"
#include <QGraphicsScene>
#include "builder.h"
#include <QDebug>
#include <vector>

using namespace std;

Scene::Scene(vector <double> source, vector <double> predict, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Scene)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    sourceSeries = source;
    predictSeries = predict;
    index = 1;
}

Scene::Scene(vector <double> source, vector <double> predict, vector<double> future, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Scene)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    sourceSeries = source;
    predictSeries = predict;
    futureSeries = future;
    index = 2;
}

Scene::~Scene()
{
    delete scene;
    delete ui;
}

void Scene::on_pushButton_clicked()
{
    scene->clear();
    Builder build(sourceSeries,predictSeries, ui->graphicsView->height(), ui->graphicsView->width(), scene);
    if(index == 1)
    {
        build.drawOsi();
        build.drawSeries();
    }

    if(index == 2)
    {
        Builder buildReal(sourceSeries,futureSeries, ui->graphicsView->height(), ui->graphicsView->width(), scene);
        build.drawOsi();
        build.drawSeries();
        buildReal.drawSeries();
    }

}
