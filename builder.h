#ifndef BUILDER_H
#define BUILDER_H

#include <string>
#include <map>

using namespace std;

class Builder
{
public:
    Builder(map <string,string> tSeries,int view_height, int view_width);
    map <string,string> s_map;
    int height, width;
    void drawOsi();
    void drawSeries();
};

#endif // BUILDER_H
