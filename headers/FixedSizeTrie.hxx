#pragma once

#include <cassert>
#include <memory>
#include <type_traits>
#include "TrieNode.hxx"

namespace Grove
{
  template <typename T, size_t N>
  class FixedSizeTrie final
  {
  private:
    FixedTrieNode<T, N> root;

    static size_t ToIndex(T value) noexcept
    {
      if constexpr (std::is_same_v<std::remove_cv_t<T>, char>)
        return static_cast<size_t>(value - 'a');

      return static_cast<size_t>(value);
    }

  public:
    template <typename InputIt>
    void Insert(InputIt first, InputIt last)
    {
      FixedTrieNode<T, N> *current = &root;
      for (auto it = first; it != last; ++it)
      {
        const size_t index = ToIndex(*it);
        assert(index < N);

        if (!current->Children[index])
          current->Children[index] = make_unique<FixedTrieNode<T, N>>();

        current = current->Children[index].get();
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
      const FixedTrieNode<T, N> *current = &root;
      for (auto it = first; it != last; ++it)
      {
        if (!current)
          return false;

        const size_t index = ToIndex(*it);
        if (index >= N)
          return false;

        current = current->Children[index].get();
        if (!current)
          return false;
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