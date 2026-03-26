# Binary Tree

- Binary Tree has no fixed rule for insertion.
- In my implementation, I have used BFS for locating insert position.
> Scanning for empty nodes from left to right ensuring that first available position in level-order is always filled.

# Why Is A Queue Required ?

- A Queue Preserves Processing Order.
- Traversal starts from the root node and expands level-by-level in order. Nodes discovered are enqueued in that order.
- A Queue ensures that later nodes aren't processed unless earlier nodes are fully checked i.e. leaving no empty insertion spot behind.
> Example : 'C' won't be processed unless 'B' (Node earlier than 'C' in queue) is processed.
