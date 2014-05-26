#ifndef CONSOLE_READER
#define CONSOLE_READER 

#include "seriesReader.h"

#include <iostream>

// наследник seriesReader, отвечает за считывания файла с консоли


class ConsoleReader : SeriesReader {

public:
	ConsoleReader() {

		/* Input format : 
		1990 - 10, 1991 - 11, 1992 - 12,...
		To terminate - type '.' 
		*/

		char delim;  // delimiter

		while ( delim != '.' ) {
			string K, V;

			cin >> K >> delim >> V;
			tSeries[K] = V;

			cin >> delim;
		}
	}
};

#endif  // CONSOLE_READER
