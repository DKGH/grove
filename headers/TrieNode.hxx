#pragma once

#include <array>
#include <unordered_map>

using namespace std;

namespace Grove
{
  template <typename T>
  struct TrieNode final
  {
    unordered_map<T, TrieNode<T>> Children;
    bool IsEndOfWord{false};
  };

  template <typename T, size_t N>
  struct FixedTrieNode final
  {
    array<TrieNode<T>, N> Children;
    bool IsEndOfWord{false};
  };
}