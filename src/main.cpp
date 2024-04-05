#include <iostream>
#include "XYZReader.h"
#include "RDFCalculator.h"
#include <vector>
#include "configuration.h"


using std::cout;
using std::string;
using std::cin;
using std::cerr;
using std::vector;
using std::pair;
using std::ofstream;



int main(int argc, char* argv[]) {

	if (argc < 2) {
                cerr << "Usuage: "<< argv[0] << " </path/to/input.yaml> " << "\n";
                return 1;
        }

	string configFilePath = argv[1];

	YAML::Node configuration;
	try {
		configuration = loadConfiguration(configFilePath);
	} catch (const YAML::BadFile& e) {
		cerr << "Failed to open or read the file: " << configFilePath << "\n";
                return 1;
        } catch (const YAML::ParserException& e) {
                cerr << "Parser error when reading the file: " << configFilePath << "\n";
                cerr << e.what() << "\n"; 
                return 1;
        }



    string filename = configuration["FILENAME"].as<string>();
	double binSize = configuration["PARAMETERS"]["bin_width"].as<double>();
    double maxDistance = configuration["PARAMETERS"]["max_distance"].as<double>();
    double boxLength = configuration["PARAMETERS"]["lattice_constant"].as<double>();
	

	XYZReader reader(filename);
	if (!reader.openFile()) {
		cerr <<"Failed to open file: "<< filename << "\n";
		return 1;
	}

	RDFCalculator calculator(binSize, maxDistance, boxLength);


	vector<Atom> atoms;
	vector<vector<pair<double, double>>> allRDFs;

	int frameCount = 1;
	while(reader.readNextFrame(atoms)) {
		auto rdf = calculator.computeRDF(atoms);
		allRDFs.push_back(rdf);
		cout<< "Read a frame "<< frameCount << " with " << atoms.size() << " atoms." <<"\n";
		frameCount += 1;
	}

	// Now, we should average the RDFs from allRDFs. 
	// This part is simplified; we need to implement the averaging over frames."
	std::ofstream file("g_of_r.dat");
	file << " Average for bin" << "\t" << "Radius" << "\t" << "g(r)" << "\n";
	for (size_t bin = 0; bin < allRDFs.front().size(); ++bin) {
		double avgR = 0.0; // Average distance for this bin
		double avgG = 0.0; // Averge g(r) for this bin
		for (const auto& rdf : allRDFs) {
			avgR += rdf[bin].first;
			avgG += rdf[bin].second;
		}
		avgR /= allRDFs.size();
		avgG /= allRDFs.size();
		file << bin << "\t\t " << avgR << "\t\t" << avgG << "\n";
	}
	file.close();

	return 0;
}
