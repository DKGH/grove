#include <vector>

#include "catch2/catch_test_macros.hpp"

#include "FenwickTree.hxx"

using namespace std;

bool TestGenerateFenwickTree()
{
  return Grove::FenwickTree<int>({1, 2, 3, 4, 5, 6, 7}).GetRangeValue(0, 6) == 28;
}

TEST_CASE("Fenwick tree tests", "[fenwick_tree]")
{
  Grove::FenwickTree<int> tree({1, 2, 3, 4, 5, 6, 7});
  const int totalSum = tree.GetRangeValue(0, 6);
  REQUIRE(totalSum == 28);

  tree.Update(3, 10);
  const int updatedSum = tree.GetRangeValue(0, 6);
  REQUIRE(updatedSum == 34);

  tree.Add(0, 5);
  const int addedSum = tree.GetRangeValue(0, 6);
  REQUIRE(addedSum == 39);
}
