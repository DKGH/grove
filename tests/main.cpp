#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "catch2/catch_session.hpp"

#include "TestTraversals.hxx"
#include "TestBST.hxx"
#include "TestSegmentTrees.hxx"
#include "TestFenwickTrees.hxx"

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
