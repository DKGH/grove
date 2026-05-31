#pragma once

#include <iterator>
#include <vector>
#include <functional>

using namespace std;

namespace Grove
{
  template <typename T, typename Op = std::plus<T>>
  class SegmentTree final
  {
    vector<T> tree;
    size_t elementCount{0};
    Op op{};
    T identity{};

    T BuildTree(const vector<T> &elements, size_t left, size_t right, size_t index)
    {
      if (left == right)
      {
        tree[index] = elements[left];
        return tree[index];
      }

      const size_t mid = left + (right - left) / 2;
      const T leftVal = BuildTree(elements, left, mid, index * 2 + 1);
      const T rightVal = BuildTree(elements, mid + 1, right, index * 2 + 2);
      tree[index] = op(leftVal, rightVal);
      return tree[index];
    }

    template <typename InputIt>
    static vector<T> ToVector(const InputIt &first, const InputIt &last)
    {
      return vector<T>(first, last);
    }

    T QueryHelper(size_t nodeIndex, size_t nodeLeft, size_t nodeRight, size_t queryLeft, size_t queryRight) const
    {
      if (nodeLeft > queryRight || nodeRight < queryLeft)
        return identity;
      if (queryLeft <= nodeLeft && nodeRight <= queryRight)
        return tree[nodeIndex];

      const size_t mid = nodeLeft + (nodeRight - nodeLeft) / 2;
      return op(QueryHelper(nodeIndex * 2 + 1, nodeLeft, mid, queryLeft, queryRight),
                QueryHelper(nodeIndex * 2 + 2, mid + 1, nodeRight, queryLeft, queryRight));
    }

    T UpdateHelper(size_t nodeIndex, size_t nodeLeft, size_t nodeRight, size_t index, const T &value)
    {
      if (nodeLeft == nodeRight)
      {
        tree[nodeIndex] = value;
        return tree[nodeIndex];
      }

      const size_t mid = nodeLeft + (nodeRight - nodeLeft) / 2;
      if (index <= mid)
        UpdateHelper(nodeIndex * 2 + 1, nodeLeft, mid, index, value);
      else
        UpdateHelper(nodeIndex * 2 + 2, mid + 1, nodeRight, index, value);

      tree[nodeIndex] = op(tree[nodeIndex * 2 + 1], tree[nodeIndex * 2 + 2]);
      return tree[nodeIndex];
    }

  public:
#pragma region Constructors, Assignment Operators, and Destructor
    SegmentTree() = default;

    template <typename InputIt>
    SegmentTree(const InputIt &first, const InputIt &last, Op op = Op{}, T identity = T())
        : op(op), identity(identity), elementCount(distance(first, last))
    {
      const vector<T> elements = ToVector(first, last);
      if (elements.empty())
        return;

      tree.assign(4 * elementCount, identity);
      BuildTree(elements, 0, elementCount - 1, 0);
    }

    SegmentTree(initializer_list<T> &&elements, Op op = Op{}, T identity = T())
        : op(op), identity(identity), elementCount(elements.size())
    {
      if (elements.size() == 0)
        return;
      tree.assign(4 * elementCount, identity);
      const vector<T> elems(elements.begin(), elements.end());
      BuildTree(elems, 0, elementCount - 1, 0);
    }

    SegmentTree(const vector<T> &elements, Op op = Op{}, T identity = T())
        : op(op), identity(identity), elementCount(elements.size())
    {
      if (elements.empty())
        return;
      tree.assign(4 * elementCount, identity);
      BuildTree(elements, 0, elementCount - 1, 0);
    }

    SegmentTree(const SegmentTree &other) = default;
    SegmentTree(SegmentTree &&other) noexcept = default;
    SegmentTree &operator=(const SegmentTree &other) = default;
    SegmentTree &operator=(SegmentTree &&other) noexcept = default;
    ~SegmentTree() = default;
#pragma endregion

    T GetRangeValue(size_t left, size_t right) const
    {
      if (tree.empty() || left > right || right >= elementCount)
        return identity;

      return QueryHelper(0, 0, elementCount - 1, left, right);
    }

    void Update(size_t index, const T &value)
    {
      if (index >= elementCount || tree.empty())
        return;

      UpdateHelper(0, 0, elementCount - 1, index, value);
    }
  };
}
