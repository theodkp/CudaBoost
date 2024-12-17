#include <gtest/gtest.h>
#include "dataset.hpp"

TEST(DatasetTest, TestLoadCSVValidFile) {
    Dataset dataset = loadCSV("tests/sample.csv");

    ASSERT_EQ(dataset.data.size(), 2);
    EXPECT_EQ(dataset.data[0][0], 1.0);
    EXPECT_EQ(dataset.data[0][1], 2.0);
    EXPECT_EQ(dataset.data[0][2], 3.0);
}
