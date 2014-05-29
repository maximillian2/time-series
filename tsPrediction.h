#ifndef PREDICTION_H
#define PREDICTION_H

#include <vector>
#include <string>

#include "seriesReader.h"

using std::string;
using std::map;
// базовый класс для  предугадывания

class TsPredictor {
protected:
	SeriesReader* reader;

	vector<string> sourceKeys;	
	vector<double> sourceValues;  // This map is covered by series reader

	vector<string> predictedKeys;	
	vector<double> predictedValues;  //  Prediction algorithms gonna fill this map;   

public:

    TsPredictor(SeriesReader* s_reader = 0) : reader(s_reader) {}

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
