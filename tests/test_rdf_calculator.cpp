#include <gtest/gtest.h>
#include "../src/RDFCalculator.h"

// Function to create a simple cubic lattice of atoms
std::vector<Atom> createCubicLattice(int perSide, double spacing) {
    std::vector<Atom> atoms;
    for (int x = 0; x < perSide; ++x) {
        for (int y = 0; y < perSide; ++y) {
            for (int z = 0; z < perSide; ++z) {
                atoms.push_back(Atom{"C", x * spacing, y * spacing, z * spacing});
            }
        }
    }
    return atoms;
}

// Test RDF calculation on a simple cubic lattice
TEST(RDFCalculatorTest, CalculatesRDFOnCubicLattice) {
    int perSide = 2; // Creates 8 atoms
    double spacing = 1.0;
    auto atoms = createCubicLattice(perSide, spacing);
    RDFCalculator calculator(0.1, 5.0);

    auto rdf = calculator.computeRDF(atoms);
    // Depending on the bin size and max distance, verify certain peaks or values
    // This is a simplified check. You should calculate expected values based on the lattice and bin size
    ASSERT_FALSE(rdf.empty()); // Ensure RDF is not empty

    // More detailed checks on rdf values can be added here
}

// Test handling of an empty set of atoms
TEST(RDFCalculatorTest, HandlesEmptyAtomSet) {
    std::vector<Atom> atoms; // Empty atom set
    RDFCalculator calculator(0.1, 5.0);

    auto rdf = calculator.computeRDF(atoms);
    EXPECT_TRUE(rdf.empty()); // RDF should be empty for an empty set of atoms
}

// Test for correct handling of a single atom
TEST(RDFCalculatorTest, HandlesSingleAtom) {
    std::vector<Atom> atoms = {Atom{"C", 0.0, 0.0, 0.0}};
    RDFCalculator calculator(0.1, 5.0);

    auto rdf = calculator.computeRDF(atoms);
    EXPECT_TRUE(rdf.empty()); // RDF should be empty for a single atom
}

