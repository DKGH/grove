#include <vector>

#include "catch2/catch_test_macros.hpp"

#include "BinaryTree.hxx"

using namespace std;

bool TestGenerateBinarySearchTree()
{
  return Grove::GenerateBinarySearchTree({1, 2, 3, 4, 5, 6, 7});
}

bool TestGenerateBinarySearchTree2()
{
  return IsBinarySearchTree(Grove::GenerateBinarySearchTree(Grove::GenerateBinaryTree({1, 2, 3, 4, 5, 6, 7})));
}

TEST_CASE("Binary search tree tests", "[binary_search_tree]")
{
  REQUIRE(TestGenerateBinarySearchTree());
  REQUIRE(TestGenerateBinarySearchTree2());
}