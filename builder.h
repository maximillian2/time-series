#ifndef BUILDER_H
#define BUILDER_H

#include <string>
#include <map>
#include <QGraphicsScene>

using namespace std;

class Builder
{
public:
    Builder(map<string, double> tSeries, int view_height, int view_width, QGraphicsScene *scene);

    map <string,double> s_map;
    int height, width;
    int x0,y0;
    QGraphicsScene *drawingScene;
    double dx,dy, max_y=0, min_y=0;

    void drawOsi();
    void drawSeries();
};

#endif // BUILDER_H
