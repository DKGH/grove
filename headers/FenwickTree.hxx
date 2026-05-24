#pragma once

#include <iterator>
#include <vector>

using namespace std;

namespace Grove
{
  template <typename T>
  class FenwickTree final
  {
    vector<T> tree; // 1-based internal binary indexed tree
    size_t elementCount{0};

    static vector<T> GenerateFenwickTree(const vector<T> &elements)
    {
      if (elements.empty())
        return {};

      const size_t n = elements.size();
      vector<T> bit(n + 1);

      for (size_t i = 1; i <= n; ++i)
        bit[i] = elements[i - 1];

      for (size_t i = 1; i <= n; ++i)
      {
        const size_t j = i + (i & -i);
        if (j <= n)
          bit[j] += bit[i];
      }

      return bit;
    }

    template <typename InputIt>
    static vector<T> GenerateFenwickTree(const InputIt &first, const InputIt &last)
    {
      vector<T> elements(first, last);
      return GenerateFenwickTree(elements);
    }

    T GetPrefixSumHelper(size_t index) const
    {
      if (tree.empty() || index >= elementCount)
        return 0;

      T result = 0;
      size_t i = index + 1; // convert to 1-based
      while (i > 0)
      {
        result += tree[i];
        i -= (i & -i);
      }
      return result;
    }

    void AddHelper(size_t index, const T &delta)
    {
      if (tree.empty() || index >= elementCount)
        return;

      size_t i = index + 1; // convert to 1-based
      const size_t n = elementCount;
      while (i <= n)
      {
        tree[i] += delta;
        i += (i & -i);
      }
    }

  public:
#pragma region Constructors, Assignment Operators, and Destructor
    FenwickTree() = default;

    template <typename InputIt>
    FenwickTree(const InputIt &first, const InputIt &last)
        : tree(GenerateFenwickTree(first, last)), elementCount(distance(first, last))
    {
    }

    FenwickTree(initializer_list<T> &&elements)
        : tree(GenerateFenwickTree(elements.begin(), elements.end())), elementCount(elements.size())
    {
    }

    FenwickTree(const vector<T> &elements)
        : tree(GenerateFenwickTree(elements)), elementCount(elements.size())
    {
    }

    FenwickTree(const FenwickTree &other) = default;
    FenwickTree(FenwickTree &&other) noexcept = default;
    FenwickTree &operator=(const FenwickTree &other) = default;
    FenwickTree &operator=(FenwickTree &&other) noexcept = default;
    ~FenwickTree() = default;
#pragma endregion

    T GetPrefixSum(size_t index) const
    {
      if (tree.empty() || index >= elementCount)
        return 0;

      return GetPrefixSumHelper(index);
    }

    T GetRangeSum(size_t left, size_t right) const
    {
      if (tree.empty() || left > right || right >= elementCount)
        return 0;

      return GetPrefixSumHelper(right) - (left == 0 ? 0 : GetPrefixSumHelper(left - 1));
    }

    void Update(size_t index, const T &value)
    {
      if (index >= elementCount)
        return;

      const T oldValue = GetRangeSum(index, index);
      const T delta = value - oldValue;
      AddHelper(index, delta);
    }

    void Add(size_t index, const T &delta)
    {
      AddHelper(index, delta);
    }
  };
}
