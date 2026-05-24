#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "catch2/catch_session.hpp"

#include "TestTraversals.hxx"
#include "TestBST.hxx"
#include "TestSegmentTree.hxx"
#include "TestFenwickTree.hxx"
#include "TestRedBlackTree.hxx"

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
