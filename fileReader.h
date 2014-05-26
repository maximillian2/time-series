#ifndef FILE_READER
#define FILE_READER 

#include "seriesReader.h"

#include <fstream>
#include <iostream>


// для файла

using namespace std;

//Exception throws if file name is invalid
class FileNotFound {};


class FileReader : public SeriesReader {
private:
	ifstream source;

public:
	FileReader(string fName) : source(fName.c_str()) {
		
		if ( !source ) {
			throw FileNotFound();
		}

		/* File format : 
		1990 - 10, 1991 - 11, 1992 - 12,...
		You can change delimiter(-.~...)
		*/

		while ( source ) {
			/*k - key; v - value . (c) captain */
			string K, V;  
			char delim;  // delimiter

			source >> K >> delim >> V;
			tSeries[K] = V;

			source >> delim;
		}
	}
};



#endif