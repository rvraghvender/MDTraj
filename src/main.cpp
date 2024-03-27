#include <iostream>
#include "XYZReader.h"
#include "RDFCalculator.h"
#include <vector>

int main() {
	std::cout <<"Enter the name of Trajectory file: "<<"\n";
	std::string filename;
	std::cin >> filename;

	XYZReader reader(filename);
	if (!reader.openFile()) {
		std::cerr <<"Failed to open file: "<< filename << "\n";
		return 1;
	}

	// Parameters for RDF
	double binSize = 0.1;
	double maxDistance = 10.0;
	RDFCalculator calculator(binSize, maxDistance);


	std::vector<Atom> atoms;
	std::vector<std::vector<std::pair<double, double>>> allRDFs;

	while(reader.readNextFrame(atoms)) {
		auto rdf = calculator.computeRDF(atoms);
		allRDFs.push_back(rdf);
		//std::cout<< "Read a frame with " << atoms.size() << " atoms." <<"\n";
	}

        // Now, we should average the RDFs from allRDFs. 
        // This part is simplified; we need to implement the 
        // averaging over frames.
	for (size_t bin = 0; bin < allRDFs.front().size(); ++bin) {
		double avgR = 0.0; // Average distance for this bin
		double avgG = 0.0; // Averge g(r) for this bin
		for (const auto& rdf : allRDFs) {
			avgR += rdf[bin].first;
			avgG += rdf[bin].second;
		}
		avgR /= allRDFs.size();
		avgG /= allRDFs.size();
		std::cout <<"Average for bin " << bin <<" : R = " << avgR << " , g(R) = " << avgG << "\n";
	}

	
	return 0;
}
