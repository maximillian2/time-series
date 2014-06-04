#include "neuralnetwork.h"
#include <QtDebug>

void NeuralNetwork::predict(int times){
    sourceKeys   = reader->getKeys();
    sourceValues = reader->getValues();

    vector<int> keys;
    for (int i=1;i<=sourceKeys.size();i++)
        keys.push_back(i);

    vector<double> keysMulValues;
    vector<int> keysPow2;
    for(int i=0;i<keys.size();i++) {
        keysMulValues.push_back(keys[i] * sourceValues[i]);
        keysPow2.push_back(keys[i] * keys[i]);
    }

    //coefficients
    double a = (getVectorSum(keysMulValues) - (getVectorSum(keys) * getVectorSum(sourceValues)) / sourceValues.size()) / (getVectorSum(keysPow2) - pow(getVectorSum(keys), 2) / sourceValues.size());
    double b = getVectorSum(sourceValues) / sourceValues.size() - a * (getVectorSum(keys)) / sourceValues.size();

    /*
        //calculation of the average relative error
        vector<double> avarageErrorValues;
        for (int i=0; i<keys.size(); i++)
            avarageErrorValues.push_back( (fabs(sourceValues[i] - (a * keys[i] + b)) / sourceValues[i]) * 100 );
        cout << "prediction error=" <<getVectorSum(avarageErrorValues)/sourceValues.size() <<"%" <<endl;
    */

    for(int i=0;i<times;i++) {
        //calculated (smoothed) value for the series
        keys.push_back(keys[keys.size() - 1] + 1);
        resultValues.push_back(a * keys[keys.size() - 1] + b);
    }
}

template <class K>
NeuralNetwork::getVectorSum(vector<K> vec) {
    K sum = 0.0;

    for(int i=0; i<vec.size(); i++) {
        sum += vec[i];
    }

    return sum;
}
