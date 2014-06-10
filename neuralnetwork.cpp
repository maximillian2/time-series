#include "neuralnetwork.h"
#include <QtDebug>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #include <random>

void NeuralNetwork::predict(int times){


    sourceKeys   = reader->getKeys();
    sourceValues = reader->getValues();

    switch ( seriesType ) {

        case ( WITHOUT_SEASONAL_VARIATON ) : {

        vector<int> keys;
        for (unsigned int i=1;i<=sourceKeys.size();i++)
            keys.push_back(i);

        vector<double> keysMulValues;
        vector<int> keysPow2;
        for(unsigned int i=0;i<keys.size();i++) {
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

        break;

        }
        case (WITH_SEASONAL_VARIATON) : {
            int seasons = sourceValues.size() / partsInSeason;
            int seasSumAmnt = seasons * partsInSeason - partsInSeason + 1;

            double seasonSum [seasSumAmnt];
            double seasonAver[seasSumAmnt];

            for (int i = 0; i < seasSumAmnt; ++i)
            {
                seasonSum[i] = 0;

                for (int j = i; j < i + seasons; ++j)
                {
                    seasonSum[i] += sourceValues[j];
                }
                std::cout << "\nseas sum " << seasonSum[i];
            }

            for (int i = 0; i < seasSumAmnt; ++i)
            {
                seasonAver[i] = seasonSum[i] / seasons;
                std::cout << "\nseas aver " << seasonAver[i];
            }

            double centeredAver[seasSumAmnt-1];

            for (int i = 0; i < seasSumAmnt-1; ++i)
            {
                 centeredAver[i] = (seasonAver[i] + seasonAver[i+1]) / 2.0;
                 std::cout << "\ncenter sum " << centeredAver[i];
            }

            double seasMark[seasSumAmnt-1];
            double temp     [seasSumAmnt-1];

            int indexes = seasons * partsInSeason - partsInSeason;

            for (int i = 0 ; i < indexes; ++i)
            {
                temp[i] = sourceValues[i+partsInSeason/2] / centeredAver[i];
            }

            for (int i = 0; i < partsInSeason/2; ++i)
            {
                seasMark[i] = temp[(seasons-1)*partsInSeason- partsInSeason/2 +i];
            }

            for (int i = partsInSeason/2; i < indexes; ++i)
            {
                seasMark[i] = temp[i - partsInSeason/2];
            }

            double partIndexes[partsInSeason];

            for (int i = 0; i < partsInSeason; ++i)
            {
                partIndexes[i] = 0;

                for (int j = 0; j < seasons-1; ++j)
                {
                    partIndexes[i] += seasMark[partsInSeason*j + i];
                }

                partIndexes[i] /= seasons-1;
                partIndexes[i] *= (0.8 + (random()%4)/10.0);

                 std :: cout << partIndexes[i] << std::endl;
            }

            double Yx = 0, sumX= 0, xq= 0, Y= 0;

            std::cout << "size=" << sourceValues.size();

            for (unsigned int i = 1 ; i <= sourceValues.size(); ++i ) {
                Yx 	 += i * sourceValues[i-1];
                std :: cout << i * sourceValues[i-1] << '\n';
                sumX += i;
                xq   += i * i;
                Y += sourceValues[i-1];
            }

            std :: cout << " Yx  == " << Yx << std::endl;
            std::cout << " sum x " << sumX << std::endl;
            std::cout << "xQ =  " << xq << std::endl;
            std::cout << "Y == " << Y << std::endl;


            double a = 0, b = 0;

            a = -(Yx - (sumX*Y)/sourceValues.size())/(xq - (sumX * sumX)/sourceValues.size());

            std::cout << std::endl << a << '\n';

            b = Y/sourceValues.size() - a*sumX/sourceValues.size();

            std::cout << std::endl << b << '\n';



            for (unsigned int i = sourceValues.size(); i < sourceValues.size() + times; i++) {
                resultKeys  .push_back(sourceKeys[i%sourceValues.size()]);
                resultValues.push_back((a*i+b)*partIndexes[i%partsInSeason]);
            }

            double sum = 0;
            int counter = 0;

           for (int i = 0; i < resultKeys.size(); ++i)
            {
               std::cout << resultKeys[i] << "  " << resultValues[i] << std::endl;

                counter++;
               sum += resultValues[i];

                if (counter == partsInSeason) {
                    std::cout << "\nTotal : " << sum <<"\n\n";
                    counter = 0;
                    sum = 0;
                }

            }


            break;
        }
    }

}

template <class K>
K NeuralNetwork::getVectorSum(vector<K> vec) {
    K sum = 0.0;

    for(unsigned  int i=0; i<vec.size(); i++) {
        sum += vec[i];
    }

    return sum;
}
