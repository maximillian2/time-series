#ifndef FUZZY_H
#define FUZZY_H

#include "fileReader.h"
#include "tsPredictor.h"
#include "seriesReader.h"

#include <new>
#include <vector>

using namespace std;

class FuzzySet : public TsPredictor
{
public:
    FuzzySet(SeriesReader* sr) : TsPredictor(sr) {}
    void predict(int n);
    float max, min;
    float interval;
    double next, alpha, beta, gamma, s, for_1, for_2, for_3, for_4, for_5;
    vector<double> omega;
    vector<double> first;
    vector<double> second;
    vector<double> third;
    vector<double> fourth;
    vector<double> fifth;
    vector<double> T;
    vector<double> S;
};

#endif // FUZZY_H
