#include "RDFCalculator.h"
#include <cmath>
#include <algorithm>
#define M_PI   3.14159265358979323846  /* pi */

using std::pair;
using std::vector;


RDFCalculator::RDFCalculator(double binSize, double maxDistance, double boxLength)
    : binSize(binSize), maxDistance(maxDistance), boxLength(boxLength) {}

vector<pair<double, double>> RDFCalculator::computeRDF(const vector<Atom>& atoms) {
    
    // If the file is empty (For passing tests)
    if (atoms.size() < 2)  return {};
    	
    calculateDistances(atoms);
    calculateDistribution();

    double rhoBox = atoms.size() / (std::pow(boxLength, 3));

    vector<pair<double, double>> rdf;
    for (size_t i = 0; i < distribution.size(); ++i) {
        double r = binSize * (i + 0.5);
        double outerRadius = r + binSize / 2.0;
        double innerRadius = r - binSize / 2.0;
        double volumeShell = (4.0/3.0) * M_PI * (pow(outerRadius, 3) - pow(innerRadius, 3)); // Shell volume
        double normalizeDensity = distribution[i] / (rhoBox * volumeShell);
        rdf.push_back({r, normalizeDensity * (2.0 / atoms.size())}); // Don't know
    }

    return rdf;
}

void RDFCalculator::calculateDistances(const vector<Atom>& atoms) {
    distances.clear();
    for (size_t i = 0; i < atoms.size(); ++i) {
        for (size_t j = i + 1; j < atoms.size(); ++j) {
            double d = calculateDistance(atoms[i], atoms[j], boxLength);
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

double RDFCalculator::calculateDistance(const Atom& atom1, const Atom& atom2, const double boxLength) {
    double dx = atom1.x - atom2.x;
    double dy = atom1.y - atom2.y;
    double dz = atom1.z - atom2.z;

    dx -= boxLength * round(dx / boxLength);
    dy -= boxLength * round(dy / boxLength);
    dz -= boxLength * round(dz / boxLength);

    return sqrt(dx * dx + dy * dy + dz * dz);
}

