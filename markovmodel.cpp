#include "markovmodel.h"
#include <QtDebug>

void MarkovModel::predict(int times)
{
    sourceKeys   = reader->getKeys();
    sourceValues = reader->getValues();

    double alpha = 2.0 / sourceValues.size()+1;
    qDebug() << "alpha = " << alpha;

    double U0 = 0;
    double elementsSum = 0;

    for(unsigned int i = 0; i < sourceValues.size(); i++)
        elementsSum += sourceValues[i];

    qDebug() << "Sum of elements = " << elementsSum;

    U0 = elementsSum / sourceValues.size();

    qDebug() << "First value = " << firstValue;

    double temp = 0;
    for(int i = 0; i < times; i++)
    {
        temp = alpha * sourceValues.back() + (1 - alpha) * U0;
        qDebug() << temp;
        U0 = temp;
    }
}
