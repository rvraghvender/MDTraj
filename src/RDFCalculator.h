#ifndef RDFCALCULATOR_H
#define RDFCALCULATOR_H

#include <vector>
#include "XYZReader.h"

class RDFCalculator {
	public:
		RDFCalculator(double binSize, double maxDistance);
		std::vector<std::pair<double, double>> computeRDF(const std::vector<Atom> &atoms);

	private:
		double binSize;
		double maxDistance;
		std::vector<double> distances;
		std::vector<int> distribution;

		void calculateDistances(const std::vector<Atom>& atoms);
		void calculateDistribution();

		double calculateDistance(const Atom& atom1, const Atom& atom2);
};

#endif // RDFCALCULATOR_H
