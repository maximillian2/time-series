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

    min_y = 0;
    max_y = 0;

    //find interval dx
    dx=width/(s_map.size()+2);

    //find interval dy
        //find maxi y
        for(map <string, double>::iterator it = s_map.begin(); it != s_map.end(); it++)
            if(max_y < (*it).second)
                max_y = (*it).second;

        //find min y
        min_y=max_y;
        for(map <string, double>::iterator ii = s_map.begin(); ii != s_map.end(); ii++)
            if(min_y > (*ii).second)
                    min_y = (*ii).second;

        //find dy
        dy = (height/(max_y-min_y+2));

    //find centrum
    x0=width-width/20;
    y0=height;//-height/20;
}

void Builder::drawOsi()
{
    //axis
    drawingScene->addLine(10,0+height/15,10,height-height/20,QPen());//y_axis
    drawingScene->addLine(10,height-height/20,width-width/20,height-height/20,QPen());//x_axis

    //arrows
    drawingScene->addLine(width-width/20,height-height/20,width-width/10,height-height/27,QPen());
    drawingScene->addLine(width-width/20,height-height/20,width-width/10,height-height/17,QPen());

    drawingScene->addLine(10,0+height/15,10+width/100,0+height/8,QPen());
    drawingScene->addLine(10,0+height/15,10-width/100,0+height/8,QPen());

    //notches
    for(unsigned int i = 0; i < s_map.size(); i++)
        drawingScene->addLine(10+dx*(i+1),height-height/17,10+dx*(i+1),height-height/24);//x notches

    if(dy<10) dy *= 10;

    for(unsigned int i = 0; height-height/20-dy*(i+1) > 0+height/15+2*dy; i++)
        drawingScene->addLine(7,height-height/20-dy*(i+1),13,height-height/20-dy*(i+1),QPen());

    QGraphicsTextItem *text = drawingScene->addText("© G.D. aka Morphei, 2014",QFont());
}

