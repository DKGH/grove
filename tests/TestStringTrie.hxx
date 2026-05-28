#include <vector>

#include "catch2/catch_test_macros.hpp"

#include "StringTrie.hxx"

using namespace std;

TEST_CASE("String Trie tests", "[string_trie]")
{

  Grove::StringTrie<char> trie;
  trie.Insert("hello");
  trie.Insert("world");
  REQUIRE(trie.Contains("hello") == true);
  REQUIRE(trie.Contains("world") == true);
  REQUIRE(trie.Contains("foo") == false);
}