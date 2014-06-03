#ifndef FUZZYSET_H
#define FUZZYSET_H

#include "fileReader.h"
#include "tsPrediction.h"
#include "seriesReader.h"

#include <new>

class FuzzySet:public TsPredictor
{
public:
    FuzzySet(SeriesReader* sr) : TsPredictor(sr) {};
    void predict(int size);
};

#endif // FUZZYSET_H
