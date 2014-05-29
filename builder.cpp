#include "builder.h"

#include <map>
#include <string>
#include <math.h>
#include <QDebug>

Builder::Builder(map<string, double> tSeries, int view_height, int view_width, QGraphicsScene *scene)
{
    s_map = tSeries;
    height = view_height;
    width = view_width;
    drawingScene = scene;

    //find interval
    dx=width/(*s_map.end()).second-(*s_map.begin()).second+2;
    dy=height/(s_map.size()+2);


    //find centrum
    x0=fabs(1*dx)+dx;
    y0=fabs(2*dy);
}

void Builder::drawOsi()
{
drawingScene->addLine(0,y0, width,y0);
}
