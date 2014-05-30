#ifndef SCENE_H
#define SCENE_H

#include <QMainWindow>
#include <QGraphicsScene>
//#include <map>
//#include <string>
using namespace std;

namespace Ui {
class Scene;
}

class Scene : public QMainWindow
{
    Q_OBJECT

public:
    explicit Scene(QWidget *parent = 0);
    // make such constructor
    // Scene(QMap inputMap);
    ~Scene();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Scene *ui;
    QGraphicsScene *scene;

};

#endif // SCENE_H
