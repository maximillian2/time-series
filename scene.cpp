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
    series_map.insert(pair <string, double>("1992", 321));
    series_map.insert(pair <string, double>("1993", 242));
    series_map.insert(pair <string, double>("1994", 253));
    series_map.insert(pair <string, double>("1995", 235));
    series_map.insert(pair <string, double>("1996", 431));
    series_map.insert(pair <string, double>("1997", 732));
    series_map.insert(pair <string, double>("1998", 163));
    series_map.insert(pair <string, double>("1999", 399));
    series_map.insert(pair <string, double>("2000", 591));
    series_map.insert(pair <string, double>("2001", 876));
    Builder build(series_map, ui->graphicsView->height(), ui->graphicsView->width(), scene);
    build.drawOsi();
    build.drawSeries();
}
