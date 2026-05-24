#pragma once

#include <functional>
#include <vector>

using namespace std;

namespace Grove
{
  template <typename T>
  struct BinaryNode final
  {
    T Value;
    BinaryNode<T> *Left{nullptr};
    BinaryNode<T> *Right{nullptr};
    BinaryNode<T> *Parent{nullptr};

    ~BinaryNode()
    {
      delete Left;
      delete Right;
    }

    bool IsLeaf() const noexcept
    {
      return !Left && !Right;
    }

    const BinaryNode<T> *GetParent() const noexcept
    {
      return Parent;
    }

    BinaryNode<T> *GetParent() noexcept
    {
      return Parent;
    }

    bool IsRoot() const noexcept
    {
      return Parent == nullptr;
    }

#pragma region Breadth-First Traversal

    vector<T> GetLevelOrder() const
    {
      vector<T> result;
      vector<const BinaryNode<T> *> queue{this};
      while (!queue.empty())
      {
        const BinaryNode<T> *current = queue.front();
        queue.erase(queue.begin());
        result.push_back(current->Value);
        if (current->Left)
          queue.push_back(current->Left);
        if (current->Right)
          queue.push_back(current->Right);
      }
      return result;
    }

#pragma endregion

#pragma region Depth-First Traversals

    vector<T> GetPreOrder() const
    {
      vector<T> result;
      result.push_back(Value);
      if (Left)
      {
        const auto &leftValues = Left->GetPreOrder();
        result.insert(result.end(), leftValues.begin(), leftValues.end());
      }
      if (Right)
      {
        const auto &rightValues = Right->GetPreOrder();
        result.insert(result.end(), rightValues.begin(), rightValues.end());
      }
      return result;
    }

    vector<T> GetInOrder() const
    {
      vector<T> result;
      if (Left)
      {
        const auto &leftValues = Left->GetInOrder();
        result.insert(result.end(), leftValues.begin(), leftValues.end());
      }
      result.push_back(Value);
      if (Right)
      {
        const auto &rightValues = Right->GetInOrder();
        result.insert(result.end(), rightValues.begin(), rightValues.end());
      }
      return result;
    }

    vector<T> GetPostOrder() const
    {
      vector<T> result;
      if (Left)
      {
        const auto &leftValues = Left->GetPostOrder();
        result.insert(result.end(), leftValues.begin(), leftValues.end());
      }
      if (Right)
      {
        const auto &rightValues = Right->GetPostOrder();
        result.insert(result.end(), rightValues.begin(), rightValues.end());
      }
      result.push_back(Value);
      return result;
    }

#pragma endregion

#pragma region Visitors

    void VisitLevelOrder(const function<void(const T &)> &visitor) const
    {
      vector<const BinaryNode<T> *> queue{this};
      while (!queue.empty())
      {
        const BinaryNode<T> *current = queue.front();
        queue.erase(queue.begin());
        visitor(current->Value);
        if (current->Left)
          queue.push_back(current->Left);
        if (current->Right)
          queue.push_back(current->Right);
      }
    }

    void VisitPreOrder(const function<void(const T &)> &visitor) const
    {
      visitor(Value);
      if (Left)
        Left->VisitPreOrder(visitor);
      if (Right)
        Right->VisitPreOrder(visitor);
    }

    void VisitInOrder(const function<void(const T &)> &visitor) const
    {
      if (Left)
        Left->VisitInOrder(visitor);
      visitor(Value);
      if (Right)
        Right->VisitInOrder(visitor);
    }

    void VisitPostOrder(const function<void(const T &)> &visitor) const
    {
      if (Left)
        Left->VisitPostOrder(visitor);
      if (Right)
        Right->VisitPostOrder(visitor);
      visitor(Value);
    }

#pragma endregion
  };
}