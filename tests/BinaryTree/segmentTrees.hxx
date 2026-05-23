#include <vector>

#include "catch2/catch_test_macros.hpp"

#include "SegmentTree.hxx"

using namespace std;

bool TestGenerateSegmentTree()
{
  return Grove::GenerateSegmentTree({1, 2, 3, 4, 5, 6, 7})->data == 28;
}

TEST_CASE("Segment tree tests", "[segment_tree]")
{
  REQUIRE(TestGenerateSegmentTree());
}