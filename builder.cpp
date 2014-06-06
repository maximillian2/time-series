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
    size = sourceSeries.size()+predictSeries.size()-1;

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
        dy = (height-height/20)/(max_y+2);

    //find centrum
    x0=10;


    //find step_y
    if(max_y > 100 && max_y < 1000)
        step_y = dy*10;
    else if(max_y > 1 && max_y < 100)
        step_y = dy;
    else if (max_y < 1)
        step_y = dy/10;

    //find step_x
    if(size > 100&&size<1000)
        step_x = size/10;
    else if(size<100)
        step_x = size;
    else if(size>1000)
        step_x = size/100;

      y0=height-height/20;
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
    for(int i = 1; (i*step_x) < width-width/20-20; i++)
        drawingScene->addLine(x0+step_x*(i),height-height/17,x0+step_x*(i),height-height/24);//x notches

    for(int i = y0-step_y; i > 0+height/15+step_y; i= i-step_y)
        drawingScene->addLine(7,i,13,i,QPen());//y notches

    QGraphicsTextItem *text = drawingScene->addText("(c) G.D. aka Morphei, 2014",QFont());

}

void Builder::drawSeries()
{
    i=0; j=0;
    for(int i_next=1; i_next < srcSeries.size(); i_next++)
    {
        drawingScene->addLine(x0 + dx*j, y0 - srcSeries[i]*dy, x0 + dx*(j+1), y0 - srcSeries[i_next]*dy, QPen());
        i++;
        j++;
        //qDebug() << "src - " << i_next;
    }
    drawingScene->addLine(x0 + dx*j, y0 - srcSeries[i]*dy, x0 + dx*(j+1), y0 - predSeries[0]*dy, QPen());
    i = 0;
    j++;
    for(int i_next=1; i_next < predSeries.size(); i_next++)
    {
        drawingScene->addLine(x0 + dx*j, y0 - predSeries[i]*dy, x0 + dx*(j+1), y0 - predSeries[i_next]*dy, QPen(Qt::DashLine));
        i++;
        j++;
        //qDebug() << "pred" << i_next;
    }
    /*i_next = 0; */i = 0; j = 0;
}

