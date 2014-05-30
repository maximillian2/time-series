#ifndef BUILDER_H
#define BUILDER_H

#include <string>
#include <map>
#include <QGraphicsScene>

using namespace std;

class Builder
{
public:
    Builder(vector<double> sourceSeries, vector<double> predictSeries, int view_height, int view_width, QGraphicsScene *scene);

    vector<double>srcSeries;
    vector<double>predSeries;
    vector<double>allSeries;
    int height, width, size;
    int x0,y0;
    QGraphicsScene *drawingScene;
    double dx,dy, max_y, min_y;

    void drawOsi();
    void drawSeries();
};

#endif // BUILDER_H
