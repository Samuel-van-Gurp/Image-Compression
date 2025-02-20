#include <gtest/gtest.h>
#include "RunLengthEnoding.h"

TEST(RunLengthEncodeTest, SimpleCase)
{
    RunLengthEnoding rle;
    std::vector<int> input = {1, 1, 1, 2, 2, 3};
    std::vector<std::pair<int, int>> expected = {{1, 3}, {2, 2}, {3, 1}};
    EXPECT_EQ(rle.RunLengthEncode(input), expected);
}

TEST(RunLengthEncodeTest, EmptyInput)
{
    RunLengthEnoding rle;
    std::vector<int> input = {};
    std::vector<std::pair<int, int>> expected = {};
    EXPECT_EQ(rle.RunLengthEncode(input), expected);
}

TEST(RunLengthEncodeTest, SingleElement)
{
    RunLengthEnoding rle;
    std::vector<int> input = {5};
    std::vector<std::pair<int, int>> expected = {{5, 1}};
    EXPECT_EQ(rle.RunLengthEncode(input), expected);
}

TEST(RunLengthEncodeTest, AllDifferent)
{
    RunLengthEnoding rle;
    std::vector<int> input = {1, 2, 3, 4};
    std::vector<std::pair<int, int>> expected = {{1, 1}, {2, 1}, {3, 1}, {4, 1}};
    EXPECT_EQ(rle.RunLengthEncode(input), expected);
}

TEST(RunLengthDecodeTest, SimpleCase)
{
    RunLengthEnoding rle;
    std::vector<std::pair<int, int>> input = {{1, 3}, {2, 2}, {3, 1}};
    std::vector<int> expected = {1, 1, 1, 2, 2, 3};
    EXPECT_EQ(rle.RunLengthDecode(input), expected);
}

TEST(RunLengthDecodeTest, EmptyInput)
{
    RunLengthEnoding rle;
    std::vector<std::pair<int, int>> input = {};
    std::vector<int> expected = {};
    EXPECT_EQ(rle.RunLengthDecode(input), expected);
}

TEST(RunLengthDecodeTest, SingleElement)
{
    RunLengthEnoding rle;
    std::vector<std::pair<int, int>> input = {{5, 1}};
    std::vector<int> expected = {5};
    EXPECT_EQ(rle.RunLengthDecode(input), expected);
}

TEST(RunLengthDecodeTest, AllDifferent)
{
    RunLengthEnoding rle;
    std::vector<std::pair<int, int>> input = {{1, 1}, {2, 1}, {3, 1}, {4, 1}};
    std::vector<int> expected = {1, 2, 3, 4};
    EXPECT_EQ(rle.RunLengthDecode(input), expected);
}
