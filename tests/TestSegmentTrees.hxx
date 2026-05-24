#include <vector>

#include "catch2/catch_test_macros.hpp"

#include "SegmentTree.hxx"

using namespace std;

bool TestGenerateSegmentTree()
{
  return Grove::SegmentTree<int>({1, 2, 3, 4, 5, 6, 7}).GetRangeSum(0, 6) == 28;
}

TEST_CASE("Segment tree tests", "[segment_tree]")
{
  Grove::SegmentTree<int> tree({1, 2, 3, 4, 5, 6, 7});
  const int totalSum = tree.GetRangeSum(0, 6);
  REQUIRE(totalSum == 28);

  tree.Update(3, 10);
  const int updatedSum = tree.GetRangeSum(0, 6);
  REQUIRE(updatedSum == 34);
}