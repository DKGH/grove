#pragma once

#include <functional>
#include <vector>

using namespace std;

namespace Grove
{
  template <typename T>
  struct Node
  {
    T data;
    Node<T> *left{nullptr};
    Node<T> *right{nullptr};

    bool IsLeaf() const noexcept
    {
      return !left && !right;
    }

#pragma region Breadth-First Traversal

    vector<T> GetLevelOrder() const
    {
      vector<T> result;
      vector<const Node<T> *> queue{this};
      while (!queue.empty())
      {
        const Node<T> *current = queue.front();
        queue.erase(queue.begin());
        result.push_back(current->data);
        if (current->left)
          queue.push_back(current->left);
        if (current->right)
          queue.push_back(current->right);
      }
      return result;
    }

#pragma endregion

#pragma region Depth-First Traversals

    vector<T> GetPreOrder() const
    {
      vector<T> result;
      result.push_back(data);
      if (left)
      {
        const auto &leftValues = left->GetPreOrder();
        result.insert(result.end(), leftValues.begin(), leftValues.end());
      }
      if (right)
      {
        const auto &rightValues = right->GetPreOrder();
        result.insert(result.end(), rightValues.begin(), rightValues.end());
      }
      return result;
    }

    vector<T> GetInOrder() const
    {
      vector<T> result;
      if (left)
      {
        const auto &leftValues = left->GetInOrder();
        result.insert(result.end(), leftValues.begin(), leftValues.end());
      }
      result.push_back(data);
      if (right)
      {
        const auto &rightValues = right->GetInOrder();
        result.insert(result.end(), rightValues.begin(), rightValues.end());
      }
      return result;
    }

    vector<T> GetPostOrder() const
    {
      vector<T> result;
      if (left)
      {
        const auto &leftValues = left->GetPostOrder();
        result.insert(result.end(), leftValues.begin(), leftValues.end());
      }
      if (right)
      {
        const auto &rightValues = right->GetPostOrder();
        result.insert(result.end(), rightValues.begin(), rightValues.end());
      }
      result.push_back(data);
      return result;
    }

#pragma endregion

#pragma region Visitors

    void VisitLevelOrder(const function<void(const T &)> &visitor) const
    {
      vector<const Node<T> *> queue{this};
      while (!queue.empty())
      {
        const Node<T> *current = queue.front();
        queue.erase(queue.begin());
        visitor(current->data);
        if (current->left)
          queue.push_back(current->left);
        if (current->right)
          queue.push_back(current->right);
      }
    }

    void VisitPreOrder(const function<void(const T &)> &visitor) const
    {
      visitor(data);
      if (left)
        left->VisitPreOrder(visitor);
      if (right)
        right->VisitPreOrder(visitor);
    }

    void VisitInOrder(const function<void(const T &)> &visitor) const
    {
      if (left)
        left->VisitInOrder(visitor);
      visitor(data);
      if (right)
        right->VisitInOrder(visitor);
    }

    void VisitPostOrder(const function<void(const T &)> &visitor) const
    {
      if (left)
        left->VisitPostOrder(visitor);
      if (right)
        right->VisitPostOrder(visitor);
      visitor(data);
    }

#pragma endregion
  };
}