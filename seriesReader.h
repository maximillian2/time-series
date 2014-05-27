#ifndef SERIES_READER
#define SERIES_READER

#include <string>
#include <map>

// базовый класс с интрефейсом для заполнения временного ряда

using namespace std;

class SeriesReader {
protected:
	map<string, string> tSeries;

public:
	virtual map<string, string> getSeries() { return tSeries; }
};

#endif