#ifndef PREDICTION_H
#define PREDICTION_H

#include <vector>
#include <string>

#include "seriesReader.h"

using std::string;
using std::vector;

class TsPredictor {
protected:
	SeriesReader* reader;

    vector<string> sourceKeys;
    vector<double> sourceValues;  // This vector is covered by series reader

    vector<string> resultKeys;
    vector<double> resultValues;  //  These vectors are filled only with predict() method.

	int partsInSeason;   // Only for season variation

public:	
    TsPredictor(SeriesReader* s_reader = 0) : reader(s_reader), partsInSeason(12), seriesType(WITH_SEASONAL_VARIATON) {}

    enum {WITH_SEASONAL_VARIATON, WITHOUT_SEASONAL_VARIATON } seriesType;

    vector<double> getSourceValues() { return sourceValues; }

    vector<string> getResultKeys()   { return resultKeys;   }
    vector<double> getResultValues() { return resultValues; }

    void eraseResult() {
        resultKeys  .clear();
        resultValues.clear();
    }

    void setPartsInSeason(int parts) {
        if ( parts > 0 ) {
            partsInSeason = parts;
        }
    }


    void setReader(SeriesReader* newReader) {
//        if ( newReader != NULL ) {
            reader = newReader;
//        }
    }


	/*Method will make a prediction according to required value
	Realise your prediction algorithm in the inherited class*/
	virtual void predict(int times) = 0;
};

#endif //PREDICTION_H
