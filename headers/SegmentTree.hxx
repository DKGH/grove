#pragma once

#include <iterator>
#include <vector>

using namespace std;

namespace Grove
{
  template <typename T>
  class SegmentTree final
  {
    vector<T> tree;
    size_t elementCount{0};

    static T BuildTree(const vector<T> &elements, size_t left, size_t right, size_t index, vector<T> &tree)
    {
      if (left == right)
      {
        tree[index] = elements[left];
        return tree[index];
      }

      const size_t mid = left + (right - left) / 2;
      const T leftSum = BuildTree(elements, left, mid, index * 2 + 1, tree);
      const T rightSum = BuildTree(elements, mid + 1, right, index * 2 + 2, tree);
      tree[index] = leftSum + rightSum;
      return tree[index];
    }

    static vector<T> GenerateSegmentTree(const vector<T> &elements)
    {
      if (elements.empty())
        return {};

      const size_t n = elements.size();
      vector<T> tree(4 * n);
      BuildTree(elements, 0, n - 1, 0, tree);
      return tree;
    }

    template <typename InputIt>
    static vector<T> GenerateSegmentTree(const InputIt &first, const InputIt &last)
    {
      vector<T> elements(first, last);
      return GenerateSegmentTree(elements);
    }

    T GetRangeSumHelper(size_t nodeIndex, size_t nodeLeft, size_t nodeRight, size_t queryLeft, size_t queryRight) const
    {
      if (nodeLeft > queryRight || nodeRight < queryLeft)
        return 0;
      if (queryLeft <= nodeLeft && nodeRight <= queryRight)
        return tree[nodeIndex];

      const size_t mid = nodeLeft + (nodeRight - nodeLeft) / 2;
      return GetRangeSumHelper(nodeIndex * 2 + 1, nodeLeft, mid, queryLeft, queryRight) +
             GetRangeSumHelper(nodeIndex * 2 + 2, mid + 1, nodeRight, queryLeft, queryRight);
    }

  public:
#pragma region Constructors, Assignment Operators, and Destructor
    SegmentTree() = default;

    template <typename InputIt>
    SegmentTree(const InputIt &first, const InputIt &last)
        : tree(GenerateSegmentTree(first, last)), elementCount(distance(first, last))
    {
    }

    SegmentTree(initializer_list<T> &&elements)
        : tree(GenerateSegmentTree(elements.begin(), elements.end())), elementCount(elements.size())
    {
    }

    SegmentTree(const vector<T> &elements)
        : tree(GenerateSegmentTree(elements)), elementCount(elements.size())
    {
    }

    SegmentTree(const SegmentTree &other) = default;
    SegmentTree(SegmentTree &&other) noexcept = default;
    SegmentTree &operator=(const SegmentTree &other) = default;
    SegmentTree &operator=(SegmentTree &&other) noexcept = default;
    ~SegmentTree() = default;
#pragma endregion

    T GetRangeSum(size_t left, size_t right) const
    {
      if (tree.empty() || left > right || right >= elementCount)
        return 0;

      return GetRangeSumHelper(0, 0, elementCount - 1, left, right);
    }

    void Update(size_t index, const T &value)
    {
      if (index >= elementCount)
        return;

      const T oldValue = GetRangeSum(index, index);
      const T delta = value - oldValue;

      size_t nodeIndex = 0;
      size_t nodeLeft = 0;
      size_t nodeRight = elementCount - 1;

      while (true)
      {
        tree[nodeIndex] += delta;
        if (nodeLeft == nodeRight)
          break;

        const size_t mid = nodeLeft + (nodeRight - nodeLeft) / 2;
        if (index <= mid)
        {
          nodeIndex = nodeIndex * 2 + 1;
          nodeRight = mid;
        }
        else
        {
          nodeIndex = nodeIndex * 2 + 2;
          nodeLeft = mid + 1;
        }
      }
    }
  };
}
