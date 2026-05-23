#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "catch2/catch_session.hpp"

#include "BinaryTree/traversal.hxx"
#include "BinaryTree/bst.hxx"
#include "BinaryTree/segmentTrees.hxx"

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
