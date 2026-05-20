#pragma once

#include <algorithm>
#include <cstddef>
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

#pragma region Binary Tree Creators

    template <typename T>
    Node<T> *GenerateBinaryTree(const vector<T> &elements)
    {
        const size_t n{elements.size()};
        if (n == 0)
            return nullptr;
        vector<Node<T> *> nodes;
        nodes.reserve(elements.size());
        for (const auto &element : elements)
            nodes.push_back(new Node<T>{element, nullptr, nullptr});
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
    Node<T> *GenerateBinarySearchTree(const initializer_list<T> &elements)
    {
        vector<T> sortedElements{elements};
        sort(sortedElements.begin(), sortedElements.end());
        return GenerateBinaryTree(sortedElements);
    }

    template <typename T>
    Node<T> *GenerateBinarySearchTree(const Node<T> *node)
    {
        if (!node)
            return nullptr;
        vector<T> elements;
        node->VisitInOrder([&elements](const T &value)
                           { elements.push_back(value); });
        return GenerateBinaryTree(elements);
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