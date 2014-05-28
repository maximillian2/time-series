#include "scene.h"
#include "ui_scene.h"
#include <QGraphicsScene>
#include "builder.h"
#include <QDebug>

Scene::Scene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Scene)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
}

Scene::~Scene()
{
    delete ui;

}

void Scene::on_pushButton_clicked()
{
    scene->clear();
    map <string, double> series_map;
    Builder build(series_map, ui->graphicsView->height(), ui->graphicsView->width(), scene);
    qDebug() << ui->graphicsView->geometry();
    qDebug() << ui->graphicsView->width();
    build.drawOsi();
}
