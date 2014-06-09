#ifndef FILE_READER
#define FILE_READER 

#include "seriesReader.h"

#include <fstream>
#include <iostream>

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
			string K;
			double V;  
			char delim;  // delimiter

			source >> K >> delim >> V;
			
			keys  .push_back(K);
			values.push_back(V);

			source >> delim;
		}
	}

    virtual ~FileReader() {
        source.close();
    }
};



#endif
