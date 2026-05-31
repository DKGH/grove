#pragma once

#include <functional>
#include <iterator>
#include <limits>
#include <vector>

using namespace std;

namespace Grove
{
  template <typename T, typename Op = std::plus<T>>
  class FenwickTree final
  {
    vector<T> tree;   // 1-based internal binary indexed tree
    vector<T> values; // underlying point values (0-based)
    size_t elementCount{0};
    Op op{};
    T identity{};

    static vector<T> GenerateFenwickTree(const vector<T> &elements, const Op &op, const T &identity)
    {
      if (elements.empty())
        return {};

      const size_t n = elements.size();
      vector<T> bit(n + 1, identity);

      for (size_t i = 1; i <= n; ++i)
        bit[i] = elements[i - 1];

      for (size_t i = 1; i <= n; ++i)
      {
        const size_t j = i + (i & -i);
        if (j <= n)
          bit[j] = op(bit[j], bit[i]);
      }

      return bit;
    }

    template <typename InputIt>
    static vector<T> GenerateFenwickTree(const InputIt &first, const InputIt &last, const Op &op, const T &identity)
    {
      vector<T> elements(first, last);
      return GenerateFenwickTree(elements, op, identity);
    }

    T GetPrefixHelper(size_t index) const
    {
      if (tree.empty() || index >= elementCount)
        return identity;

      T result = identity;
      size_t i = index + 1;
      while (i > 0)
      {
        result = op(result, tree[i]);
        i -= (i & -i);
      }
      return result;
    }

    void AddHelper(size_t index, const T &value)
    {
      if (tree.empty() || index >= elementCount)
        return;

      size_t i = index + 1;
      const size_t n = elementCount;
      while (i <= n)
      {
        tree[i] = op(tree[i], value);
        i += (i & -i);
      }
    }

  public:
#pragma region Constructors, Assignment Operators, and Destructor
    FenwickTree() = default;

    template <typename InputIt>
    FenwickTree(const InputIt &first, const InputIt &last, Op op_ = Op{}, T identity_ = T{})
        : tree(GenerateFenwickTree(first, last, op_, identity_)), values(first, last), elementCount(distance(first, last)), op(op_), identity(identity_)
    {
    }

    FenwickTree(initializer_list<T> &&elements, Op op_ = Op{}, T identity_ = T{})
        : tree(GenerateFenwickTree(elements.begin(), elements.end(), op_, identity_)), values(elements.begin(), elements.end()), elementCount(elements.size()), op(op_), identity(identity_)
    {
    }

    FenwickTree(const vector<T> &elements, Op op_ = Op{}, T identity_ = T{})
        : tree(GenerateFenwickTree(elements, op_, identity_)), values(elements), elementCount(elements.size()), op(op_), identity(identity_)
    {
    }

    FenwickTree(const FenwickTree &other) = default;
    FenwickTree(FenwickTree &&other) noexcept = default;
    FenwickTree &operator=(const FenwickTree &other) = default;
    FenwickTree &operator=(FenwickTree &&other) noexcept = default;
    ~FenwickTree() = default;
#pragma endregion

    T GetPrefixValue(size_t index) const
    {
      if (tree.empty() || index >= elementCount)
        return identity;

      return GetPrefixHelper(index);
    }

    T GetRangeValue(size_t left, size_t right) const
    {
      if (values.empty() || left > right || right >= elementCount)
        return identity;

      T result = identity;
      for (size_t i = left; i <= right; ++i)
        result = op(result, values[i]);
      return result;
    }

    void Update(size_t index, const T &value)
    {
      if (index >= elementCount)
        return;

      values[index] = value;
      tree = GenerateFenwickTree(values, op, identity);
    }

    void Add(size_t index, const T &value)
    {
      if (index >= elementCount)
        return;

      values[index] = op(values[index], value);
      AddHelper(index, value);
    }

    size_t Size() const { return elementCount; }
  };

  template <typename T>
  using FenwickTreeSum = FenwickTree<T, std::plus<T>>;
}
