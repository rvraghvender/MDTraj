#ifndef XYZREADER_H
#define XYZREADER_H

#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;


// Define a structure to hold atom data
struct Atom {
	string symbol;
	double x, y, z;
};



// Define a class to read XYZ files
class XYZReader {
	
	string filename;
	ifstream fileStream;
	
	public:
		XYZReader(const string& filename);
		~XYZReader();
	
		bool openFile();
		bool readNextFrame(vector<Atom>& atoms);
		
	
};

#endif // XYZREADER_H
