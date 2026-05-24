#include <vector>

#include "catch2/catch_test_macros.hpp"

#include "RedBlackTree.hxx"

using namespace std;

TEST_CASE("Red-black tree tests", "[red_black_tree]")
{
  Grove::RedBlackTree<int> tree({10, 20, 30, 15, 5, 1, 50});

  REQUIRE(tree.Contains(15));
  REQUIRE(tree.Contains(50));
  REQUIRE(!tree.Contains(100));

  tree.Insert(25);
  REQUIRE(tree.Contains(25));

  const vector<int> inorder = tree.GetInOrder();
  REQUIRE(inorder == vector<int>{1, 5, 10, 15, 20, 25, 30, 50});
}
