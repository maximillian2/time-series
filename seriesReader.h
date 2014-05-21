#ifndef SERIES_READER
#define SERIES_READER

#include <string>
#include <map>

using namespace std;

class SeriesReader {
protected:
	map<string, string> tSeries;

public:
	virtual map<string, string> getSeries() { return tSeries; }
};

#endif