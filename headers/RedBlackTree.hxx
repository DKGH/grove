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
    T data;
    Color color{Color::Red};
  };

  template <typename T>
  class RedBlackTree
  {
    BinaryNode<RedBlackNodeData<T>> *root{nullptr};

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
      using Node = BinaryNode<RedBlackNodeData<T>>;
      Node *z = new Node{RedBlackNodeData<T>{value, Color::Red}, nullptr, nullptr, nullptr};
      Node *y = nullptr;
      Node *x = root;

      while (x)
      {
        y = x;
        if (value < x->data.data)
          x = x->left;
        else
          x = x->right;
      }

      z->parent = y;
      if (!y)
        root = z;
      else if (value < y->data.data)
        y->left = z;
      else
        y->right = z;

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
        result.push_back(n.data);
      return result;
    }

  private:
    BinaryNode<RedBlackNodeData<T>> *FindNode(const T &value) const noexcept
    {
      auto *current = root;
      while (current)
      {
        if (value == current->data.data)
          return current;
        if (value < current->data.data)
          current = current->left;
        else
          current = current->right;
      }
      return nullptr;
    }

    void LeftRotate(BinaryNode<RedBlackNodeData<T>> *x)
    {
      using Node = BinaryNode<RedBlackNodeData<T>>;
      Node *y = x->right;
      if (!y)
        return;
      x->right = y->left;
      if (y->left)
        y->left->parent = x;
      y->parent = x->parent;
      if (!x->parent)
        root = y;
      else if (x == x->parent->left)
        x->parent->left = y;
      else
        x->parent->right = y;
      y->left = x;
      x->parent = y;
    }

    void RightRotate(BinaryNode<RedBlackNodeData<T>> *y)
    {
      using Node = BinaryNode<RedBlackNodeData<T>>;
      Node *x = y->left;
      if (!x)
        return;
      y->left = x->right;
      if (x->right)
        x->right->parent = y;
      x->parent = y->parent;
      if (!y->parent)
        root = x;
      else if (y == y->parent->right)
        y->parent->right = x;
      else
        y->parent->left = x;
      x->right = y;
      y->parent = x;
    }

    void InsertFixup(BinaryNode<RedBlackNodeData<T>> *z)
    {
      using Node = BinaryNode<RedBlackNodeData<T>>;
      while (z->parent && z->parent->data.color == Color::Red)
      {
        Node *parent = z->parent;
        Node *grand = parent->parent;
        if (!grand)
          break;

        if (parent == grand->left)
        {
          Node *uncle = grand->right;
          if (uncle && uncle->data.color == Color::Red)
          {
            parent->data.color = Color::Black;
            uncle->data.color = Color::Black;
            grand->data.color = Color::Red;
            z = grand;
          }
          else
          {
            if (z == parent->right)
            {
              z = parent;
              LeftRotate(z);
              parent = z->parent;
              grand = parent ? parent->parent : nullptr;
            }
            if (parent)
              parent->data.color = Color::Black;
            if (grand)
            {
              grand->data.color = Color::Red;
              RightRotate(grand);
            }
          }
        }
        else
        {
          Node *uncle = grand->left;
          if (uncle && uncle->data.color == Color::Red)
          {
            parent->data.color = Color::Black;
            uncle->data.color = Color::Black;
            grand->data.color = Color::Red;
            z = grand;
          }
          else
          {
            if (z == parent->left)
            {
              z = parent;
              RightRotate(z);
              parent = z->parent;
              grand = parent ? parent->parent : nullptr;
            }
            if (parent)
              parent->data.color = Color::Black;
            if (grand)
            {
              grand->data.color = Color::Red;
              LeftRotate(grand);
            }
          }
        }
      }
      if (root)
        root->data.color = Color::Black;
    }
  };
}
