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
}

Scene::~Scene()
{
    delete ui;

}

void Scene::on_pushButton_clicked()
{
    scene->clear();
    Builder build(sourceSeries,predictSeries, ui->graphicsView->height(), ui->graphicsView->width(), scene);
    build.drawOsi();
    build.drawSeries();
}
