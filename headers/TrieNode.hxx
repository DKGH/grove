#pragma once

#include <unordered_map>

using namespace std;

namespace Grove
{
  template <typename T>
  struct TrieNode final
  {
    unordered_map<T, TrieNode<T> *> Children;
    bool IsEndOfWord{false};
    T Value;

    ~TrieNode()
    {
      for (auto &[_, child] : Children)
        delete child;
    }
  };
}