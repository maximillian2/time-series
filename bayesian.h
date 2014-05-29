#ifndef BAYESIAN
#define BAYESIAN

#include "fileReader.h"
#include "tsPrediction.h"

#include <new>

class Bayesian : public TsPredictor {
	int partsInSeason;   // Only for season variation

	enum {WITH_SEASONAL_WARIATON, WITHOUT_SEASONAL_WARIATON} seriesType;

public:
	Bayesian() : TsPredictor(new FileReader("test.txt")), partsInSeason(4), seriesType(WITH_SEASONAL_WARIATON) {}

	void setPartsInSeason(int parts) {
		if ( parts > 0 ) {
			partsInSeason = parts;
		}
	}

	void predict(int times) {

		sourceKeys   = reader->getKeys();
		sourceValues = reader->getValues();

		switch ( seriesType ) {
			
			case ( WITHOUT_SEASONAL_WARIATON ) : {
				
				const int N = 3; // 

				vector<string> movingAverageKeys;
				vector<double> movingAverageValues;

				// auto it = sourceValues.begin();

				// ++it;
				
				for (int i = 1; i < sourceKeys.size()-1 ; ++i) {
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

					int lastSource = sourceValues.size()-1;

					movingAverageValues.push_back((sourceValues[lastSource]+sourceValues[lastSource-1]+sourceValues[lastSource-2]) / 3.0);
				}

				for (int i = 0; i < sourceValues.size() ; ++i)
				{
					std::cout << sourceValues[i] << std::endl;
				}

			break;

			}

			case (WITH_SEASONAL_WARIATON) : {
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
				}

				for (int i = 0; i < seasSumAmnt; ++i)
				{
					seasonAver[i] = seasonSum[i] / seasons;
				}

				double centeredAver[seasSumAmnt-1];

				for (int i = 0; i < seasSumAmnt-1; ++i)
				{
					 centeredAver[i] = (seasonAver[i] + seasonAver[i+1]) / 2.0;
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
				}

				double Yx = 0, sumX= 0, xq= 0, Y= 0;

				for (int i = 1 ; i <= sourceValues.size(); ++i ) {
					Yx 	 += i * sourceValues[i-1];
					sumX += i;
					xq   += i * i;
					Y += sourceValues[i-1];
				}
 

				double a = 0, b = 0;

				a = (Yx - (sumX*Y)/sourceValues.size())/(xq - (sumX * sumX)/sourceValues.size());
				b = Y/sourceValues.size() - a*sumX/sourceValues.size();


				
				for (int i = sourceValues.size(); i < sourceValues.size() + times; i++) {
					predictedKeys  .push_back(string("s"));
					predictedValues.push_back((a*i+b)*partIndexes[i%partsInSeason]); 
				}

				for (int i = 0; i < predictedKeys.size(); ++i)
				{
					std::cout << predictedKeys[i] << "  " << predictedValues[i] << std::endl;
				}

				break;
			}
		}
	}
};

#endif