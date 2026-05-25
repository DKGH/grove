# Grove

Generic C++ header only library for trees and tries. Requires C++ 20 or higher.

## Overview

`Grove` provides header-only implementations for tree and trie data structures in C++.

## Supports

- Binary Trees
- Binary Search Trees
- Segment Trees
- Fenwick Trees
- Red Black Trees

## Usage

Include the headers from the `headers/` directory in your project. For example:

```cpp
#include "headers/BinaryTree.hxx"

const shared_ptr<Grove::BinaryNode<int>> &root =
    shared_ptr<Grove::BinaryNode<int>>(Grove::GenerateBinaryTree({1, 2, 3, 4, 5, 6, 7}));
return root->GetPreOrder();
```

Then use the library types and functions directly in your code.
