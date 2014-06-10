#ifndef BAYESIAN
#define BAYESIAN

#include "fileReader.h"
#include "tsPredictor.h"
#include "seriesReader.h"
#include <QtDebug>

#include <new>
#include <iostream>

class Bayesian : public TsPredictor {
public:

    Bayesian(SeriesReader* sr) : TsPredictor(sr) {}


    //  Only filled  result vectors.
	void predict(int times) {
        qDebug() << "i'm in predict";

        sourceKeys   = reader->getKeys();
        sourceValues = reader->getValues();

        switch ( seriesType ) {
			
            case ( WITHOUT_SEASONAL_VARIATON ) : {

                const int N = 3;

                vector<string> movingAverageKeys;
                vector<double> movingAverageValues;

                for (unsigned int i = 1; i < sourceKeys.size()-1 ; ++i) {
                    double average = sourceValues[i];

                    for ( int j = 1; j <= 1; j ++ ) {
                        average += sourceValues[i+j];
                        average += sourceValues[i-j];
                    }

                    average /= N;

                    movingAverageKeys	.push_back(sourceKeys[i]);
                    movingAverageValues	.push_back(average);

                }

                for ( int t = 0; t < times; ++t ) {
                    double value = movingAverageValues[movingAverageValues.size()-1];

                    value += (1.0/3.0)*(sourceValues[sourceValues.size()-1] - sourceValues[sourceValues.size()-2]);
				
                    sourceValues.push_back(value);
                    resultValues.push_back(value);

                    int lastSource = sourceValues.size()-1;

                    movingAverageValues.push_back((sourceValues[lastSource]+sourceValues[lastSource-1]+sourceValues[lastSource-2]) / 3.0);
                }

                for ( int i = 0; i < times; ++i ) {
                    sourceValues.pop_back();
                }

                for (unsigned int i = 0; i < resultValues.size() ; ++i)
                {
                    std::cout << resultValues[i] << std::endl;
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
};

#endif
