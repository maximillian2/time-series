#include "builder.h"

#include <map>
#include <string>
#include <math.h>
#include <QDebug>

Builder::Builder(vector<double> sourceSeries, vector<double> predictSeries, int view_height, int view_width, QGraphicsScene *scene)
{
    srcSeries = sourceSeries;
    predSeries = predictSeries;
    allSeries = sourceSeries;
    for(int i = 0; i < predictSeries.size(); i++)
    {
        allSeries.push_back(predictSeries[i]);
    }
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

    //find step
    if(max_y > 1000)
        step = dy*125;
    else if(max_y > 100)
        step = dy*12;
    else if (max_y > 10)
        step = dy;
     qDebug() << step;
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

    for(int i = 0; i < size-1; i++)
        drawingScene->addLine(10+dx*(i+1),height-height/17,10+dx*(i+1),height-height/24);//x notches

    for(int i = y0-y0/15; i > 0+height/15+step*2; i= i-step)
        drawingScene->addLine(7,i,13,i,QPen());//y notches

    QGraphicsTextItem *text = drawingScene->addText("(c) G.D. aka Morphei, 2014",QFont());

}

void Builder::drawSeries()
{
    int j = 0, i = 0, i_next = 1;
    for(i_next; i_next < size; i_next++)
    {
        drawingScene->addLine(x0+dx*j,allSeries[i]/step, x0+dx*(j+1), allSeries[i_next]/step, QPen());
        j++;
        i++;
    }
}

