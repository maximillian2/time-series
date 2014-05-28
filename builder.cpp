#include "builder.h"

#include <map>
#include <string>

Builder::Builder(map <string, string> tSeries, int view_height, int view_width)
{
    s_map = tSeries;
    height = view_height;
    width = view_width;
}

void Builder::drawOsi()
{
//    int x0,y0;
//    float dx,dy;
//    dx=width/(s_map.end()-s_map.begin()+2);
//    dy=height/(y_max-y_min+2);
//    x0=fabs(xbegin*dx)+dx;
//    y0=fabs(y_min*dy)+dy;
}
