#ifndef MARKOVMODEL_H
#define MARKOVMODEL_H

#include "seriesReader.h"
#include "tsPredictor.h"

class MarkovModel : public TsPredictor
{
public:
    MarkovModel(SeriesReader *sr) : TsPredictor(sr) {}
    void predict(int times);
};

#endif // MARKOVMODEL_H
