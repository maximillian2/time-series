#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "fileReader.h"
#include "tsPredictor.h"
#include "seriesReader.h"
#include <vector>
#include <string>
#include <math.h>

class NeuralNetwork:public TsPredictor
{
public:
    NeuralNetwork(SeriesReader* sr) : TsPredictor(sr) {}
    void predict(int times);

    template <class K>
        K getVectorSum(vector<K> vec);
};

#endif // NEURALNETWORK_H
