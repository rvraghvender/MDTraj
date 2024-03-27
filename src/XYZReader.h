#ifndef XYZREADER_H
#define XYZREADER_H

#include <string>
#include <vector>
#include <fstream>

// Define a structure to hold atom data
struct Atom {
	std::string symbol;
	float x, y, z;
};

// Define a class to read XYZ files
class XYZReader {
	public:
		XYZReader(const std::string& filename);
		~XYZReader();
	
		bool openFile();
		bool readNextFrame(std::vector<Atom>& atoms);
	
	private:
		std::string filename;
		std::ifstream fileStream; 
};

#endif // XYZREADER_H
