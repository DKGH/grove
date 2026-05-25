#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <vector>

#include "BinaryNode.hxx"

using namespace std;

namespace Grove
{
#pragma region Binary Tree Creators

    template <typename T, typename InputIt>
    unique_ptr<BinaryNode<T>> GenerateBinaryTree(InputIt first, InputIt last)
    {
        vector<BinaryNode<T> *> nodes;
        for (; first != last; ++first)
            nodes.push_back(new BinaryNode<T>{*first, nullptr, nullptr});

        const size_t n{nodes.size()};
        if (n == 0)
            return nullptr;

        for (size_t i{0}; i < n; ++i)
        {
            if (const size_t leftIndex = 2 * i + 1; leftIndex < n)
            {
                nodes[i]->Left = nodes[leftIndex];
                nodes[leftIndex]->Parent = nodes[i];
            }
            if (const size_t rightIndex = 2 * i + 2; rightIndex < n)
            {
                nodes[i]->Right = nodes[rightIndex];
                nodes[rightIndex]->Parent = nodes[i];
            }
        }

        return unique_ptr<BinaryNode<T>>(nodes[0]);
    }

    template <typename T>
    unique_ptr<BinaryNode<T>> GenerateBinaryTree(initializer_list<T> &&elements)
    {
        return GenerateBinaryTree<T>(elements.begin(), elements.end());
    }

    template <typename T>
    unique_ptr<BinaryNode<T>> GenerateBinaryTree(const vector<T> &elements)
    {
        return GenerateBinaryTree<T>(elements.begin(), elements.end());
    }

    template <typename T>
    unique_ptr<BinaryNode<T>> CopyBinaryTree(const unique_ptr<BinaryNode<T>> &root)
    {
        if (!root)
            return nullptr;
        BinaryNode<T> *newNode = new BinaryNode<T>{root->Value, nullptr, nullptr};
        newNode->Left = CopyBinaryTree(root->Left);
        if (newNode->Left)
            newNode->Left->Parent = newNode;
        newNode->Right = CopyBinaryTree(root->Right);
        if (newNode->Right)
            newNode->Right->Parent = newNode;
        return newNode;
    }

#pragma endregion

#pragma region Destructors

    template <typename T>
    bool DeleteNodeFromBinarySearchTree(BinaryNode<T> *&root, const T &value)
    {
        if (!root)
            return false;
        if (root->Value == value)
        {
            BinaryNode<T> *temp = root;
            if (root->Left && root->Right)
            {
                BinaryNode<T> *successor = root->Right;
                while (successor->Left)
                    successor = successor->Left;
                root->Value = successor->Value;
                DeleteNodeFromBinarySearchTree(root->Right, successor->Value);
            }
            else
            {
                root = root->Left ? root->Left : root->Right;
                delete temp;
            }
            return true;
        }
        return DeleteNodeFromBinarySearchTree(root->Left, value) || DeleteNodeFromBinarySearchTree(root->Right, value);
    }

#pragma endregion

#pragma region Binary Search Tree

    template <typename T>
    void InsertIntoBinarySearchTree(BinaryNode<T> *&root, const T &value, BinaryNode<T> *parent = nullptr)
    {
        if (!root)
        {
            root = new BinaryNode<T>{value, nullptr, nullptr};
            root->Parent = parent;
            return;
        }
        if (value < root->Value)
            InsertIntoBinarySearchTree(root->Left, value, root);
        else
            InsertIntoBinarySearchTree(root->Right, value, root);
    }

    template <typename T>
    unique_ptr<BinaryNode<T>> GenerateBinarySearchTree(const initializer_list<T> &elements)
    {
        BinaryNode<T> *root{nullptr};
        for (const T &element : elements)
            InsertIntoBinarySearchTree(root, element);
        return unique_ptr<BinaryNode<T>>(root);
    }

    template <typename T>
    unique_ptr<BinaryNode<T>> GenerateBinarySearchTree(const BinaryNode<T> *node)
    {
        BinaryNode<T> *root = nullptr;
        node->VisitInOrder([&](const T &value)
                           { InsertIntoBinarySearchTree(root, value); });
        return unique_ptr<BinaryNode<T>>(root);
    }

    template <typename T>
    unique_ptr<BinaryNode<T>> GenerateBinarySearchTree(const unique_ptr<BinaryNode<T>> &node)
    {
        return GenerateBinarySearchTree(node.get());
    }

    template <typename T>
    bool IsBinarySearchTree(const BinaryNode<T> *node)
    {
        if (!node)
            return true;
        if (node->Left && node->Left->Value > node->Value)
            return false;
        if (node->Right && node->Right->Value < node->Value)
            return false;
        return IsBinarySearchTree(node->Left) && IsBinarySearchTree(node->Right);
    }

    template <typename T>
    bool IsBinarySearchTree(const unique_ptr<BinaryNode<T>> &node)
    {
        return IsBinarySearchTree(node.get());
    }

    template <typename T>
    unique_ptr<BinaryNode<T>> BinarySearch(unique_ptr<BinaryNode<T>> &root, const T &value)
    {
        if (!root)
            return nullptr;
        if (root->Value == value)
            return root;
        return value < root->Value
                   ? BinarySearch(root->Left, value)
                   : BinarySearch(root->Right, value);
    }

#pragma endregion
}