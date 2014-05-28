#ifndef PREDICTION_H
#define PREDICTION_H

#include <string>
#include <map>

#include "seriesReader.h"

// базовый класс для  предугадывания

class TsPredictor {
protected:
	SeriesReader* reader;

	map<string, double> predictedValues;  //  Prediction algorithms gonna fill this map;   


public:
    TsPredictor(SeriesReader* s_reader = 0) : reader(s_reader) {}

	void setReader(SeriesReader* newReader) {
		if ( newReader != NULL ) {
			reader = newReader;
		}
	}

	/*Method will make a prediction according to required value
	Realise your prediction algorithm in the inherited class*/
	virtual string predict(string required)  = 0;
};

#endif //PREDICTION_H
