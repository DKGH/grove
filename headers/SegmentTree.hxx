#pragma once

#include <vector>

#include "BinaryNode.hxx"

using namespace std;

namespace Grove
{
  template <typename T, typename InputIt>
  BinaryNode<T> *GenerateSegmentTree(const InputIt &first, const InputIt &last)
  {
    vector<T> elements(first, last);
    if (elements.empty())
      return nullptr;
    if (elements.size() == 1)
      return new BinaryNode<T>{elements[0], nullptr, nullptr};

    const size_t mid = elements.size() / 2;
    BinaryNode<T> *node = new BinaryNode<T>{0, nullptr, nullptr};
    node->left = GenerateSegmentTree<T>(elements.begin(), elements.begin() + mid);
    node->right = GenerateSegmentTree<T>(elements.begin() + mid, elements.end());
    node->data = (node->left ? node->left->data : 0) + (node->right ? node->right->data : 0);
    return node;
  }

  template <typename T>
  BinaryNode<T> *GenerateSegmentTree(vector<T> &&elements)
  {
    return GenerateSegmentTree<T>(elements.begin(), elements.end());
  }

  template <typename T>
  BinaryNode<T> *GenerateSegmentTree(const initializer_list<T> &elements)
  {
    return GenerateSegmentTree<T>(elements.begin(), elements.end());
  }
}