#include <iostream>
#include "XYZReader.h"
#include <sstream>

using std::istringstream;
using std::string;
using std::getline;
using std::stoul;  // Converts string to unsigned integer
using std::size_t;
using std::vector;


XYZReader :: XYZReader(const string& filename) : filename(filename) {}

XYZReader :: ~XYZReader() {
	if (fileStream.is_open()){
	    fileStream.close();
	}
}

bool XYZReader :: openFile() {
	fileStream.open(filename);
	return fileStream.is_open();
}

bool XYZReader :: readNextFrame(vector<Atom>& atoms) {
	
	string line;
	size_t numAtoms;

	// Clear previous atoms
	atoms.clear();

	// Read number of atoms
	if (!getline(fileStream, line)) return false;
	numAtoms = stoul(line); // stout :: converts string to unsigned integer

	// Skip comment line
	if (!getline(fileStream, line)) return false;

	// Read atoms
	for (size_t i = 0; i < numAtoms; ++i) {
		if (!getline(fileStream, line)) return false;
		Atom atom;
                istringstream iss(line);
		if (!(iss >> atom.symbol >> atom.x >> atom.y >> atom.z)) return false;
		atoms.push_back(atom);
	}

	return true;
}
