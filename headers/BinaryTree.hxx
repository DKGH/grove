#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <vector>

#include "Node.hxx"

using namespace std;

namespace Grove
{
#pragma region Binary Tree Creators

    template <typename T, typename InputIt>
    Node<T> *GenerateBinaryTree(InputIt first, InputIt last)
    {
        vector<Node<T> *> nodes;
        for (; first != last; ++first)
            nodes.push_back(new Node<T>{*first, nullptr, nullptr});

        const size_t n{nodes.size()};
        if (n == 0)
            return nullptr;

        for (size_t i{0}; i < n; ++i)
        {
            if (const size_t leftIndex = 2 * i + 1; leftIndex < n)
                nodes[i]->left = nodes[leftIndex];
            if (const size_t rightIndex = 2 * i + 2; rightIndex < n)
                nodes[i]->right = nodes[rightIndex];
        }

        return nodes[0];
    }

    template <typename T>
    Node<T> *GenerateBinaryTree(initializer_list<T> &&elements)
    {
        return GenerateBinaryTree<T>(elements.begin(), elements.end());
    }

    template <typename T>
    Node<T> *GenerateBinaryTree(const vector<T> &elements)
    {
        return GenerateBinaryTree<T>(elements.begin(), elements.end());
    }

    template <typename T>
    Node<T> *CopyBinaryTree(const Node<T> *root)
    {
        if (!root)
            return nullptr;
        Node<T> *newNode = new Node<T>{root->data, nullptr, nullptr};
        newNode->left = CopyBinaryTree(root->left);
        newNode->right = CopyBinaryTree(root->right);
        return newNode;
    }

#pragma endregion

#pragma region Destructors
    template <typename T>
    void DeleteBinaryTree(Node<T> *root)
    {
        if (root)
        {
            DeleteBinaryTree(root->left);
            DeleteBinaryTree(root->right);
            delete root;
        }
    }

    template <typename T>
    bool DeleteNodeFromBinarySearchTree(Node<T> *&root, const T &value)
    {
        if (!root)
            return false;
        if (root->data == value)
        {
            Node<T> *temp = root;
            if (root->left && root->right)
            {
                Node<T> *successor = root->right;
                while (successor->left)
                    successor = successor->left;
                root->data = successor->data;
                DeleteNodeFromBinarySearchTree(root->right, successor->data);
            }
            else
            {
                root = root->left ? root->left : root->right;
                delete temp;
            }
            return true;
        }
        return DeleteNodeFromBinarySearchTree(root->left, value) || DeleteNodeFromBinarySearchTree(root->right, value);
    }

#pragma endregion

#pragma region Binary Search Tree

    template <typename T>
    void InsertIntoBinarySearchTree(Node<T> *&root, const T &value)
    {
        if (!root)
        {
            root = new Node<T>{value, nullptr, nullptr};
            return;
        }
        if (value < root->data)
            InsertIntoBinarySearchTree(root->left, value);
        else
            InsertIntoBinarySearchTree(root->right, value);
    }

    template <typename T>
    Node<T> *GenerateBinarySearchTree(const initializer_list<T> &elements)
    {
        Node<T> *root = nullptr;
        for (const T &element : elements)
            InsertIntoBinarySearchTree(root, element);
        return root;
    }

    template <typename T>
    Node<T> *GenerateBinarySearchTree(const Node<T> *node)
    {
        Node<T> *root = nullptr;
        node->VisitInOrder([&](const T &value)
                           { InsertIntoBinarySearchTree(root, value); });
        return root;
    }

    template <typename T>
    bool IsBinarySearchTree(const Node<T> *node)
    {
        if (!node)
            return true;
        if (node->left && node->left->data > node->data)
            return false;
        if (node->right && node->right->data < node->data)
            return false;
        return IsBinarySearchTree(node->left) && IsBinarySearchTree(node->right);
    }

    template <typename T>
    Node<T> *BinarySearch(const Node<T> *root, const T &value)
    {
        if (!root)
            return nullptr;
        if (root->data == value)
            return const_cast<Node<T> *>(root);
        return value < root->data
                   ? BinarySearch(root->left, value)
                   : BinarySearch(root->right, value);
    }

#pragma endregion
}