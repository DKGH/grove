#pragma once

#include <initializer_list>
#include <utility>
#include <vector>

using namespace std;

namespace Grove
{
  enum class Color
  {
    Red,
    Black
  };

  template <typename T>
  struct RedBlackNodeData
  {
    T Data;
    Color Color{Color::Red};
  };

  template <typename T>
  class RedBlackTree
  {
    using Node = BinaryNode<RedBlackNodeData<T>>;
    Node *root{nullptr};

  public:
    RedBlackTree() = default;

    RedBlackTree(initializer_list<T> elements)
    {
      for (const auto &e : elements)
        Insert(e);
    }

    ~RedBlackTree()
    {
      delete root;
      root = nullptr;
    }

    bool Contains(const T &value) const noexcept
    {
      return FindNode(value) != nullptr;
    }

    void Insert(const T &value)
    {
      Node *z = new Node{RedBlackNodeData<T>{value, Color::Red}, nullptr, nullptr, nullptr};
      Node *y = nullptr;
      Node *x = root;

      while (x)
      {
        y = x;
        if (value < x->Value.Data)
          x = x->Left;
        else
          x = x->Right;
      }

      z->Parent = y;
      if (!y)
        root = z;
      else if (value < y->Value.Data)
        y->Left = z;
      else
        y->Right = z;

      InsertFixup(z);
    }

    vector<T> GetInOrder() const
    {
      if (!root)
        return {};
      const auto nodes = root->GetInOrder();
      vector<T> result;
      result.reserve(nodes.size());
      for (const auto &n : nodes)
        result.push_back(n.Data);
      return result;
    }

  private:
    Node *FindNode(const T &value) const noexcept
    {
      Node *current = root;
      while (current)
      {
        if (value == current->Value.Data)
          return current;
        if (value < current->Value.Data)
          current = current->Left;
        else
          current = current->Right;
      }
      return nullptr;
    }

    void LeftRotate(BinaryNode<RedBlackNodeData<T>> *x)
    {
      using Node = BinaryNode<RedBlackNodeData<T>>;
      Node *y = x->Right;
      if (!y)
        return;
      x->Right = y->Left;
      if (y->Left)
        y->Left->Parent = x;
      y->Parent = x->Parent;
      if (!x->Parent)
        root = y;
      else if (x == x->Parent->Left)
        x->Parent->Left = y;
      else
        x->Parent->Right = y;
      y->Left = x;
      x->Parent = y;
    }

    void RightRotate(BinaryNode<RedBlackNodeData<T>> *y)
    {
      using Node = BinaryNode<RedBlackNodeData<T>>;
      Node *x = y->Left;
      if (!x)
        return;
      y->Left = x->Right;
      if (x->Right)
        x->Right->Parent = y;
      x->Parent = y->Parent;
      if (!y->Parent)
        root = x;
      else if (y == y->Parent->Right)
        y->Parent->Right = x;
      else
        y->Parent->Left = x;
      x->Right = y;
      y->Parent = x;
    }

    void InsertFixup(BinaryNode<RedBlackNodeData<T>> *z)
    {
      using Node = BinaryNode<RedBlackNodeData<T>>;
      while (z->Parent && z->Parent->Value.Color == Color::Red)
      {
        Node *parent = z->Parent;
        Node *grand = parent->Parent;
        if (!grand)
          break;

        if (parent == grand->Left)
        {
          Node *uncle = grand->Right;
          if (uncle && uncle->Value.Color == Color::Red)
          {
            parent->Value.Color = Color::Black;
            uncle->Value.Color = Color::Black;
            grand->Value.Color = Color::Red;
            z = grand;
          }
          else
          {
            if (z == parent->Right)
            {
              z = parent;
              LeftRotate(z);
              parent = z->Parent;
              grand = parent ? parent->Parent : nullptr;
            }
            if (parent)
              parent->Value.Color = Color::Black;
            if (grand)
            {
              grand->Value.Color = Color::Red;
              RightRotate(grand);
            }
          }
        }
        else
        {
          Node *uncle = grand->Left;
          if (uncle && uncle->Value.Color == Color::Red)
          {
            parent->Value.Color = Color::Black;
            uncle->Value.Color = Color::Black;
            grand->Value.Color = Color::Red;
            z = grand;
          }
          else
          {
            if (z == parent->Left)
            {
              z = parent;
              RightRotate(z);
              parent = z->Parent;
              grand = parent ? parent->Parent : nullptr;
            }
            if (parent)
              parent->Value.Color = Color::Black;
            if (grand)
            {
              grand->Value.Color = Color::Red;
              LeftRotate(grand);
            }
          }
        }
      }
      if (root)
        root->Value.Color = Color::Black;
    }
  };
}
