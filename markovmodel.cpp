#include "markovmodel.h"
#include <QtDebug>

void MarkovModel::predict(int times)
{
    sourceKeys   = reader->getKeys();
    sourceValues = reader->getValues();

    double U0 = 0, elementsSum = 0;

    double alpha = 2.0 / sourceValues.size()+1;

    vector<double> inputValues = sourceValues;

    for(int i = 0; i < times; i++)
    {
        for(unsigned int i = 0; i < inputValues.size(); i++)
            elementsSum += inputValues[i];

        U0 = elementsSum / inputValues.size();

        inputValues.push_back(alpha * inputValues.back() + (1 - alpha) * U0);

        resultValues.push_back(inputValues.back());

        elementsSum = 0;
    }
}
