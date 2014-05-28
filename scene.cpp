#include "scene.h"
#include "ui_scene.h"
#include <QGraphicsScene>

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
