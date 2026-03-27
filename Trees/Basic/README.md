# Binary Tree

## Overview

This is a generic binary tree implementation in C++.

The tree does not follow any ordering rules (unlike BST).
Insertion is performed using **level-order traversal (BFS)** to maintain a complete structure.

---

## Insertion Strategy

Insertion is done using a queue:

* Traverse the tree level-by-level
* Find the first node with an empty left or right child
* Insert the new node at that position

This ensures:

* The tree remains as compact as possible
* No gaps are left in earlier levels

---

## Why a Queue?

A queue is required to preserve **level-order processing**:

* Nodes are processed in the order they are discovered
* Each level is fully explored before moving to the next
* Ensures correct placement of new nodes

Example:
A node discovered earlier (e.g., B) is always processed before a later node (e.g., C)

---

## Features

* Level-order insertion (BFS)
* Tree printing (level-order)
* Height calculation:
  * BFS (iterative)
  * DFS (recursive)

* Recursive operations:
  * Total number of nodes
  * Sum of all node values
  * Count of leaf nodes

* Safe memory deallocation using BFS

---

## Notes

* Height = The number of **edges** in the longest path
* Recursive functions follow **postorder pattern** (left → right → node)
