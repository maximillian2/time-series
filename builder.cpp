#include "builder.h"

#include <map>
#include <string>
#include <math.h>
#include <QDebug>

Builder::Builder(vector<double> sourceSeries, vector<double> predictSeries, int view_height, int view_width, QGraphicsScene *scene)
{
    srcSeries = sourceSeries;
    predSeries = predictSeries;
    allSeries = sourceSeries+predictSeries;
    height = view_height;
    width = view_width;
    drawingScene = scene;
    size = sourceSeries.size()+predictSeries.size();

    min_y = 0;
    max_y = 0;

    //find interval dx
    dx=width/(size+1);

    //find interval dy
        //find maxi y
        for(int i = 0; i < size; i++)
            if(max_y < allSeries[i])
                max_y = allSeries[i];

        //find min y
        min_y=max_y;
        for(int i = 0; i < size; i++)
            if(min_y > allSeries[i])
                min_y = allSeries[i];

        //find dy
        dy = (height/(max_y-min_y+2));

    //find centrum
    x0=10;
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
    for(int i = 0; i < s_map.size(); i++)
        drawingScene->addLine(10+dx*(i+1),height-height/17,10+dx*(i+1),height-height/24);//x notches

    if(dy<10) dy *= 10;
    for(int i = 0; height-height/20-dy*(i+1) > 0+height/15+2*dy; i++)
        drawingScene->addLine(7,height-height/20-dy*(i+1),13,height-height/20-dy*(i+1),QPen());

    QGraphicsTextItem *text = drawingScene->addText("(c) G.D. aka Morphei, 2014",QFont());
}

void Builder::drawSeries()
{
    int j = 0, i = 0, i_next = 1;
    for(i_next; i_next < size; i_next++)
    {
        drawingScene->addLine(x0+dx*j,allSeries[i]/2, x0+dx*(j+1), allSeries[i_next]/2, QPen());
        j++;
        i++;
    }
}

