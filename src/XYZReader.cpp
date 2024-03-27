#include <iostream>
#include "XYZReader.h"
#include <sstream>

XYZReader::XYZReader(const std::string& filename) : filename(filename) {}

XYZReader::~XYZReader() {
	if (fileStream.is_open()){
		fileStream.close();
	}
}


bool XYZReader::openFile() {
	fileStream.open(filename);
	return fileStream.is_open();
}

bool XYZReader::readNextFrame(std::vector<Atom>& atoms) {
	std::string line;
	std::size_t numAtoms;

	// Clear previous atoms
	atoms.clear();

	// Read number of atoms
	if (!std::getline(fileStream, line)) return false;
	numAtoms = std::stoul(line);

	// Skip comment line
	if (!std::getline(fileStream, line)) return false;

	// Read atoms
	for (std::size_t i = 0; i < numAtoms; ++i) {
		if (!std::getline(fileStream, line)) return false;
		Atom atom;
                std::istringstream iss(line);
		if (!(iss >> atom.symbol >> atom.x >> atom.y >> atom.z)) return false;
		atoms.push_back(atom);
	}

	return true;
}
