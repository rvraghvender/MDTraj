#ifndef RDFCALCULATOR_H
#define RDFCALCULATOR_H

#include <vector>
#include "XYZReader.h"

using std::vector;
using std::pair;


class RDFCalculator {
	public:
		RDFCalculator(double binSize, double maxDistance, double boxLength);
		vector<pair<double, double>> computeRDF(const vector<Atom> &atoms);

	private:
		double binSize;
		double maxDistance;
		double boxLength;
		vector<double> distances;
		vector<int> distribution;

		void calculateDistances(const vector<Atom>& atoms);
		void calculateDistribution();

		double calculateDistance(const Atom& atom1, const Atom& atom2, const double boxLength);
};

#endif // RDFCALCULATOR_H
