#ifndef SERIES_READER
#define SERIES_READER

#include <string>
#include <vector>

// базовый класс с интрефейсом для заполнения временного ряда

using namespace std;

class SeriesReader {
protected:
	vector<string> keys;	
	vector<double> values;

public:
	vector<string> getKeys() { return keys; }
	vector<double> getValues() { return values; }

};

#endif