#ifndef SCENE_H
#define SCENE_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class Scene;
}

class Scene : public QMainWindow
{
    Q_OBJECT

public:
    explicit Scene(QWidget *parent = 0);
    ~Scene();

private:
    Ui::Scene *ui;
    QGraphicsScene *scene;

};

#endif // SCENE_H
