#include "RDFCalculator.h"
#include <cmath> 

RDFCalculator::RDFCalculator(double binSize, double maxDistance)
    : binSize(binSize), maxDistance(maxDistance) {}

std::vector<std::pair<double, double>> RDFCalculator::computeRDF(const std::vector<Atom>& atoms) {
    
    if (atoms.size() < 2) {
    	return {};
    }
	
    calculateDistances(atoms);
    calculateDistribution();

    std::vector<std::pair<double, double>> rdf;
    for (size_t i = 0; i < distribution.size(); ++i) {
        double r = binSize * (i + 0.5);
        rdf.push_back({r, distribution[i]});
    }

    return rdf;
}

void RDFCalculator::calculateDistances(const std::vector<Atom>& atoms) {
    distances.clear();
    for (size_t i = 0; i < atoms.size(); ++i) {
        for (size_t j = i + 1; j < atoms.size(); ++j) {
            double d = calculateDistance(atoms[i], atoms[j]);
            if (d <= maxDistance) {
                distances.push_back(d);
            }
        }
    }
}

void RDFCalculator::calculateDistribution() {
    size_t numBins = static_cast<size_t>(maxDistance / binSize);
    distribution.assign(numBins, 0);

    for (double d : distances) {
        size_t bin = static_cast<size_t>(d / binSize);
        if (bin < distribution.size()) {
            distribution[bin]++;
        }
    }
}

double RDFCalculator::calculateDistance(const Atom& atom1, const Atom& atom2) {
    double dx = atom1.x - atom2.x;
    double dy = atom1.y - atom2.y;
    double dz = atom1.z - atom2.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

