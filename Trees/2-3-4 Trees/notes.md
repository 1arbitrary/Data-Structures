# 2-3-4 Tree Observations

These notes capture the core structural invariants and implementation details of a 2-3-4 Tree. The focus is on understanding how nodes are represented, how search space is partitioned, and why top-down insertion works.

---

## Storage Layout

A node stores its keys and child pointers in fixed-size arrays.

```cpp
T keys[4];
Node<T>* children[5];
```

At first glance, allowing four keys may seem unusual because a valid
2-3-4 tree node can only contain up to three keys.

The extra slot exists to support insertion. A node may temporarily
overflow to four keys before being split into smaller nodes.

This distinction leads to an important observation:

> Physical storage capacity and legal occupancy are different invariants.

---

## Occupancy Rules

Under normal circumstances, a node contains between one and three keys.

```text
key_count ∈ {1, 2, 3}
```

During insertion, a node may temporarily enter an overflow state:

```text
key_count = 4
```

An overflow is never permanent and must be resolved by splitting the
node.

---

## Child Count Invariants

### Internal Nodes

For every internal node:

```text
child_count = key_count + 1
```

Examples:

| Keys | Children |
| ---- | -------- |
| 1    | 2        |
| 2    | 3        |
| 3    | 4        |

This relationship is what allows the keys to partition the search space
into non-overlapping intervals.

### Leaf Nodes

Leaf nodes contain no children.

```text
child_count = 0
```

A leaf stores data only and represents the termination point of a search.

---

## Active Key Region

Only part of the key array is logically active.

```text
keys[0 ... key_count - 1]
```

These keys participate in:

* Search
* Comparisons
* Traversal
* Insertion
* Splitting

Any storage beyond this interval should be treated as unused.

For example:

```text
keys = [10, 20, 30, _]
key_count = 3
```

Only the first three positions belong to the node.

---

## Search Space Partitioning

A 2-3-4 tree should be viewed as a collection of intervals rather than
a collection of left and right branches.

Consider the node:

```text
[15 | 30 | 50]
```

Its children represent the following ranges:

```text
child0 : (-∞, 15)
child1 : (15, 30)
child2 : (30, 50)
child3 : (50, +∞)
```

Searching is therefore not a binary decision.

Instead, traversal consists of determining which interval contains the
target value and following the corresponding child pointer.

This viewpoint becomes increasingly important when implementing search
and insertion.

---

## Height Growth

One of the defining characteristics of a 2-3-4 tree is that growth
occurs at the root.

When the root overflows:

1. The root is split.
2. A new root is created.
3. Tree height increases by one.

No other split changes the height of the tree.

As a result, the tree grows upward rather than downward.

---

## Top-Down Insertion

Top-down insertion follows a simple but powerful rule:

> Never descend into a full node.

Before moving to a child:

1. Check whether the child is full.
2. Split it if necessary.
3. Continue traversal.

By enforcing this rule on every descent, the algorithm guarantees that
the destination leaf always has room for the new key.

This eliminates the need to backtrack after insertion.

---

# Helper Functions

## `shift_arr`

During insertion, keys often need to be shifted to create room for a new
value while maintaining sorted order.

The `shift_arr` helper performs a right shift on an active interval.

### Implementation

```cpp
void shift_arr(T (&arr)[4], std::size_t start, std::size_t end) {
    for (std::size_t i{end}; i > start; --i) {
        arr[i] = arr[i - 1];
    }
}
```

### Parameters

| Parameter | Meaning                                |
| --------- | -------------------------------------- |
| `start`   | Position where space should be created |
| `end`     | First free slot in the active region   |

The interval being shifted is:

```text
[start, end)
```

### Why Right-to-Left?

Consider:

```text
[10 | 20 | 30 | _]
```

Suppose we want to insert a value at index `1`.

If elements are moved left-to-right, values would be overwritten before
they are copied.

Instead, movement occurs from right-to-left:

```text
Before:
[10 | 20 | 30 | _]

After shift:
[10 | 20 | 20 | 30]
```

The new value can now be inserted safely:

```text
[10 | 15 | 20 | 30]
```

This preserves all existing elements while creating a free slot for the
incoming key.

---

## Key Takeaways

* Nodes use fixed-size arrays to accommodate temporary overflow.
* Legal occupancy and physical capacity are separate concepts.
* Internal nodes satisfy `child_count = key_count + 1`.
* Leaves satisfy `child_count = 0`.
* Only `keys[0 ... key_count - 1]` belong to the active node state.
* Search is interval-based, not binary-tree based.
* Tree height increases only when the root splits.
* Top-down insertion never descends into a full node.
* Right-to-left shifting prevents accidental overwrites during insertion.
