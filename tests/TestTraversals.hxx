#include <vector>

#include "catch2/catch_test_macros.hpp"

#include "BinaryTree.hxx"

using namespace std;

vector<int> TestGetPreOrder()
{
  const shared_ptr<Grove::BinaryNode<int>> &root =
      shared_ptr<Grove::BinaryNode<int>>(Grove::GenerateBinaryTree({1, 2, 3, 4, 5, 6, 7}));
  return root->GetPreOrder();
}

vector<int> TestGetInOrder()
{
  vector<int> test{1, 2, 3, 4, 5, 6, 7};
  Grove::BinaryNode<int> *root = Grove::GenerateBinaryTree(test);
  const vector<int> &answer = root->GetInOrder();
  delete root;
  return answer;
}

vector<int> TestGetPostOrder()
{
  return shared_ptr<Grove::BinaryNode<int>>(Grove::GenerateBinaryTree({1, 2, 3, 4, 5, 6, 7}))->GetPostOrder();
}

string TestVisitLevelOrder()
{
  Grove::BinaryNode<int> *root = Grove::GenerateBinaryTree(vector<int>{1, 2, 3, 4, 5, 6, 7});
  stringstream ss;
  root->VisitLevelOrder([&ss](const int &value)
                        { ss << '\'' << value << "' "; });
  delete root;
  return ss.str();
}

string TestVisitPreOrder()
{
  Grove::BinaryNode<int> *root = Grove::GenerateBinaryTree(vector<int>{1, 2, 3, 4, 5, 6, 7});
  stringstream ss;
  root->VisitPreOrder([&ss](const int &value)
                      { ss << '\'' << value << "' "; });
  delete root;
  return ss.str();
}

string TestVisitInOrder()
{
  Grove::BinaryNode<int> *root = Grove::GenerateBinaryTree(vector<int>{1, 2, 3, 4, 5, 6, 7});
  stringstream ss;
  root->VisitInOrder([&ss](const int &value)
                     { ss << '\'' << value << "' "; });
  delete root;
  return ss.str();
}

string TestVisitPostOrder()
{
  Grove::BinaryNode<int> *root = Grove::GenerateBinaryTree(vector<int>{1, 2, 3, 4, 5, 6, 7});
  stringstream ss;
  root->VisitPostOrder([&ss](const int &value)
                       { ss << '\'' << value << "' "; });
  delete root;
  return ss.str();
}

TEST_CASE("Binary tree traversals", "[binary_tree]")
{
  REQUIRE(TestGetPreOrder() == vector<int>{1, 2, 4, 5, 3, 6, 7});
  REQUIRE(TestGetInOrder() == vector<int>{4, 2, 5, 1, 6, 3, 7});
  REQUIRE(TestGetPostOrder() == vector<int>{4, 5, 2, 6, 7, 3, 1});

  REQUIRE(TestVisitLevelOrder() == "'1' '2' '3' '4' '5' '6' '7' ");
  REQUIRE(TestVisitPreOrder() == "'1' '2' '4' '5' '3' '6' '7' ");
  REQUIRE(TestVisitInOrder() == "'4' '2' '5' '1' '6' '3' '7' ");
  REQUIRE(TestVisitPostOrder() == "'4' '5' '2' '6' '7' '3' '1' ");
}