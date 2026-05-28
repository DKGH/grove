#pragma once

#include <iterator>
#include <utility>

#include "TrieNode.hxx"

using namespace std;

namespace Grove
{
  template <typename T = char>
  class StringTrie
  {
    TrieNode<T> root;

  public:
    template <typename InputIt>
    void Insert(InputIt first, InputIt last)
    {
      TrieNode<T> *current = &root;
      for (auto it = first; it != last; ++it)
      {
        if (current->Children.find(*it) == current->Children.end())
          current->Children[*it] = TrieNode<T>{};

        current = &current->Children[*it];
      }
      current->IsEndOfWord = true;
    }

    void Insert(const vector<T> &word)
    {
      Insert(word.begin(), word.end());
    }

    void Insert(const initializer_list<T> &word)
    {
      Insert(word.begin(), word.end());
    }

    void Insert(const string &word)
    {
      Insert(word.begin(), word.end());
    }

    template <typename InputIt>
    bool Contains(InputIt first, InputIt last) const noexcept
    {
      const TrieNode<T> *current = &root;
      for (auto it = first; it != last; ++it)
      {
        if (!current)
          return false;

        const auto childIt = current->Children.find(*it);
        if (childIt == current->Children.end())
          return false;

        current = &childIt->second;
      }
      return current && current->IsEndOfWord;
    }

    bool Contains(const vector<T> &word) const noexcept
    {
      return Contains(word.begin(), word.end());
    }

    bool Contains(const initializer_list<T> &word) const noexcept
    {
      return Contains(word.begin(), word.end());
    }

    bool Contains(const string &word) const noexcept
    {
      return Contains(vector<T>(word.begin(), word.end()));
    }
  };
}