#ifndef PREDICTION_H
#define PREDICTION_H

#include <vector>
#include <string>

#include "seriesReader.h"

using std::string;
using std::vector;
// базовый класс для  предугадывания

class TsPredictor {
protected:
	SeriesReader* reader;

	vector<string> sourceKeys;	
	vector<double> sourceValues;  // This map is covered by series reader

	vector<string> predictedKeys;	
	vector<double> predictedValues;  //  Prediction algorithms gonna fill this map;   

	int partsInSeason;   // Only for season variation

	enum {WITH_SEASONAL_VARIATON, WITHOUT_SEASONAL_VARIATON} seriesType;
public:	

	void setPartsInSeason(int parts) {
		if ( parts > 0 ) {
			partsInSeason = parts;
		}
	}

    TsPredictor(SeriesReader* s_reader = 0) : reader(s_reader), partsInSeason(12), seriesType(WITH_SEASONAL_VARIATON) {}

	void setReader(SeriesReader* newReader) {
		if ( newReader != NULL ) {
			reader = newReader;
		}
	}


	/*Method will make a prediction according to required value
	Realise your prediction algorithm in the inherited class*/
	virtual void predict(int times) = 0;
};

#endif //PREDICTION_H
