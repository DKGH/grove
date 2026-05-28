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
    TrieNode<T> *root{nullptr};

  public:
    StringTrie() = default;

    ~StringTrie()
    {
      delete root;
      root = nullptr;
    }

    template <typename InputIt>
    void Insert(InputIt first, InputIt last)
    {
      if (!root)
        root = new TrieNode<T>{};

      TrieNode<T> *current = root;
      for (auto it = first; it != last; ++it)
      {
        if (current->Children.find(*it) == current->Children.end())
          current->Children[*it] = new TrieNode<T>{};

        current = current->Children[*it];
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
      TrieNode<T> *current = root;
      for (auto it = first; it != last; ++it)
      {
        if (!current || current->Children.find(*it) == current->Children.end())
          return false;

        current = current->Children[*it];
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