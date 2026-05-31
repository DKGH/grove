#include <vector>
#include <algorithm>
#include <limits>

#include "catch2/catch_test_macros.hpp"

#include "SegmentTree.hxx"

using namespace std;

bool TestGenerateSegmentTree()
{
  return Grove::SegmentTree<int>({1, 2, 3, 4, 5, 6, 7}).GetRangeValue(0, 6) == 28;
}

TEST_CASE("Segment tree tests", "[segment_tree]")
{
  Grove::SegmentTree<int> tree({1, 2, 3, 4, 5, 6, 7});
  const int totalSum = tree.GetRangeValue(0, 6);
  REQUIRE(totalSum == 28);

  tree.Update(3, 10);
  const int updatedSum = tree.GetRangeValue(0, 6);
  REQUIRE(updatedSum == 34);
}

TEST_CASE("Segment tree min operation", "[segment_tree][min]")
{
  struct MinOp
  {
    int operator()(int a, int b) const { return std::min(a, b); }
  };

  const std::vector<int> values{5, 3, 8, 1, 6};
  Grove::SegmentTree<int, MinOp> st(values.begin(), values.end(), MinOp{}, std::numeric_limits<int>::max());

  REQUIRE(st.GetRangeValue(0, 4) == 1);
  REQUIRE(st.GetRangeValue(0, 0) == 5);
  REQUIRE(st.GetRangeValue(1, 2) == 3);

  // Update index 3 (value 1 -> 10), min over whole range becomes 3
  st.Update(3, 10);
  REQUIRE(st.GetRangeValue(0, 4) == 3);
}