#include <gtest/gtest.h>
#include "../src/XYZReader.h"
#include <filesystem>  // For checking file existence

// Test for successfully reading a typical file
TEST(XYZReaderTest, SuccessfullyReadsFile) {
	XYZReader reader("/mnt/d/C++/MDTraj/tests/snap.xyz");
	ASSERT_TRUE(reader.openFile());
	std::vector<Atom> atoms;
	EXPECT_TRUE(reader.readNextFrame(atoms));
}


// Test to read correct number of atoms
TEST(XYZReaderTest, ReadsCorrectNumberOfAtoms) {
    XYZReader reader("/mnt/d/C++/MDTraj/tests/snap.xyz");
    reader.openFile();
    std::vector<Atom> atoms;
    reader.readNextFrame(atoms);
    EXPECT_EQ(atoms.size(), 270); 
}

// Test for handling an empty file
TEST(XYZReaderTest, HandlesEmptyFile) {
    XYZReader reader("/mnt/d/C++/MDTraj/tests/snap_empty.xyz");
    ASSERT_TRUE(reader.openFile());
    std::vector<Atom> atoms;
    EXPECT_FALSE(reader.readNextFrame(atoms)); 
}


// Test for reading a file with incorrect format
TEST(XYZReaderTest, HandlesIncorrectFormat) {
    XYZReader reader("/mnt/d/C++/MDTraj/tests/incorrect_snap.xyz");
    ASSERT_TRUE(reader.openFile());
    std::vector<Atom> atoms;
    EXPECT_FALSE(reader.readNextFrame(atoms)); // Expect readNextFrame to fail due to format
}

// Test for file not found
TEST(XYZReaderTest, HandlesFileNotFound) {
    XYZReader reader("/mnt/d/C++/MDTraj/tests/nonexistent_snap.xyz");
    EXPECT_FALSE(reader.openFile()); // Expect openFile to fail
}

// Test for reading a large file (performance test)
TEST(XYZReaderTest, HandlesLargeFile) {
    XYZReader reader("/mnt/d/C++/MDTraj/tests/snap.xyz");
    ASSERT_TRUE(reader.openFile());
    std::vector<Atom> atoms;
    bool result = true;
    // Try reading all frames until failure or end of file
    while (reader.readNextFrame(atoms)) {
        EXPECT_GT(atoms.size(), 0); // Each frame should have more than 0 atoms
        if (atoms.empty()) {
            result = false;
            break;
        }
    }
    EXPECT_TRUE(result);
}
