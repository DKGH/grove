#pragma once

#include <array>
#include <memory>
#include <type_traits>
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
    array<unique_ptr<FixedTrieNode<T, N>>, N> Children;
    bool IsEndOfWord{false};
  };
}