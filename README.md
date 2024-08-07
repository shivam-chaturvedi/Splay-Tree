# Splay Tree Implementation

## Overview

A **Splay Tree** is a type of self-adjusting binary search tree. The key feature of a splay tree is its ability to reorganize itself using a process called "splaying" to move frequently accessed elements closer to the root, thereby reducing the time complexity of subsequent accesses to these elements.

## What is Splaying?

**Splaying** is the process of moving a specific node to the root of the tree through a series of tree rotations. When a node is accessed (through search, insertion, or deletion), the splay operation brings that node to the root, which ensures that recently accessed nodes can be accessed quickly in the future.

### Types of Rotations in Splaying:

1. **Zig Rotation:** Single rotation, performed when the accessed node is the left or right child of the root.
2. **Zig-Zig Rotation:** Double rotation, performed when the accessed node and its parent are either both left children or both right children.
3. **Zig-Zag Rotation:** Double rotation, performed when the accessed node is a left child of a right child or a right child of a left child.

## Why Use a Splay Tree?

1. **Amortized Efficiency:** While individual operations may take linear time, the amortized time complexity for a sequence of operations is logarithmic.
2. **Simpler Implementation:** Compared to other balanced trees like AVL or Red-Black Trees, splay trees have a simpler implementation due to the lack of strict balancing rules.
3. **Good Cache Performance:** Frequently accessed nodes are moved closer to the root, which can improve cache performance.

## Where is a Splay Tree Used?

- **Memory Management:** Used in garbage collection algorithms and memory allocators.
- **Data Compression:** Used in algorithms such as the splay tree variant of the move-to-front heuristic.
- **Network Routers:** Employed to keep track of frequently accessed routes.
- **Cache Implementations:** Useful in scenarios where the access pattern is highly skewed, as it adapts to the access pattern over time.

## Splay Method Explanation

The following code snippet illustrates the splay method in a Splay Tree implementation.

```cpp
Node* splay(Node* root, int key) {
    // Base cases: root is null or key is present at root
    if (!root || root->key == key)
        return root;

    // Key lies in the left subtree
    if (key < root->key) {
        // Key is not in the tree, we are done
        if (!root->left) return root;

        // Zig-Zig (Left Left)
        if (key < root->left->key) {
            // Recursively bring the key as root of left-left
            root->left->left = splay(root->left->left, key);

            // Perform first rotation for root, 
            // if root->left is not null
            root = rightRotate(root);
        } else if (key > root->left->key) { // Zig-Zag (Left Right)
            // Recursively bring the key as root of left-right
            root->left->right = splay(root->left->right, key);

            // Perform first rotation for root->left
            if (root->left->right)
                root->left = leftRotate(root->left);
        }

        // Perform second rotation for root
        return (root->left == nullptr) ? root : rightRotate(root);
    } else { // Key lies in the right subtree
        // Key is not in the tree, we are done
        if (!root->right) return root;

        // Zig-Zig (Right Right)
        if (key > root->right->key) {
            // Recursively bring the key as root of right-right
            root->right->right = splay(root->right->right, key);

            // Perform first rotation for root
            root = leftRotate(root);
        } else if (key < root->right->key) { // Zig-Zag (Right Left)
            // Recursively bring the key as root of right-left
            root->right->left = splay(root->right->left, key);

            // Perform first rotation for root->right
            if (root->right->left)
                root->right = rightRotate(root->right);
        }

        // Perform second rotation for root
        return (root->right == nullptr) ? root : leftRotate(root);
    }
}
```

### Detailed Explanation:

1. **Base Case:** The function first checks if the `root` is `nullptr` or if the `key` is already the `root`. In such cases, it simply returns the `root`.

2. **Key in Left Subtree:**
   - If the `key` is less than the `root`'s key, it means the `key` is in the left subtree.
   - If the `root`'s left child is `nullptr`, the `key` is not in the tree, and it returns the `root`.
   - **Zig-Zig (Left Left):** If the `key` is less than the left child's key, it recursively brings the `key` to the root of the left-left subtree and performs a right rotation on the `root`.
   - **Zig-Zag (Left Right):** If the `key` is greater than the left child's key, it recursively brings the `key` to the root of the left-right subtree and performs a left rotation on the left child.
   - Finally, it performs a right rotation on the `root`.

3. **Key in Right Subtree:**
   - If the `key` is greater than the `root`'s key, it means the `key` is in the right subtree.
   - If the `root`'s right child is `nullptr`, the `key` is not in the tree, and it returns the `root`.
   - **Zig-Zig (Right Right):** If the `key` is greater than the right child's key, it recursively brings the `key` to the root of the right-right subtree and performs a left rotation on the `root`.
   - **Zig-Zag (Right Left):** If the `key` is less than the right child's key, it recursively brings the `key` to the root of the right-left subtree and performs a right rotation on the right child.
   - Finally, it performs a left rotation on the `root`.

### Example:

Consider the following splay operation sequence:

1. Initial Tree: `10 -> 20 -> 30`
2. Splay with key `20`:
   - `20` becomes the new root through a series of rotations.

## Contact

For any questions or further information, feel free to contact me on LinkedIn: [Shivam Chaturvedi](https://www.linkedin.com/in/shivam-chaturvedi-77629321a).