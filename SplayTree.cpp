#include<iostream>

using namespace std;

class SplayTree {
private:
    // Define the Node structure
    struct Node {
        int key;
        Node *left, *right;
        Node(int key) : key(key), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr; // Root pointer

    // Splay method
    // This method takes a key and the root of the tree. Based on the key, it makes some rotations
    // and makes the key the new root if the key exists. If not, the nearby keys of that key will
    // be now closer to the root.

    Node* rightRotate(Node* node) {
        if (!node) {
            return node;
        }
        Node* y = node->left;
        node->left = y->right;
        y->right = node;
        return y;
    }

    Node* leftRotate(Node* node) {
        if (!node) {
            return node;
        }
        Node* y = node->right;
        node->right = y->left;
        y->left = node;
        return y;
    }

    Node* splay(Node* root, int key) {
        // This method will splay the tree based on the key and then return the new tree
        if (!root || root->key == key) {
            // If root is null or key is already root, simply return
            return root;
        } else if (key < root->key) {
            // Key is in the left subtree
            if (!root->left) return root;

            if (root->left->key == key) {
                // If root->left child has that key, just right rotate the root and return 
                return rightRotate(root);
            }

            if (key < root->left->key) {
                // Key is in the left of the root->left child
                // Key may be in root->left->left subtree 
                root->left->left = splay(root->left->left, key); // Splay the root->left->left subtree based on the key
                // Now simply right rotate root 
                // Check if the root->left->left child is not null 
                if (root->left->left)
                    root->left = rightRotate(root->left);
            } else if (key > root->left->key) {
                root->left->right = splay(root->left->right, key);
                if (root->left->right) {
                    root->left = leftRotate(root->left);
                }
            }
            return root->left ? rightRotate(root) : root;
        } else {
            if (!root->right) return root;
            // When key is greater than root->key
            if (root->right->key == key) {
                // Key found
                return leftRotate(root);
            } else if (key > root->right->key) {
                // Key is in root->right->right
                root->right->right = splay(root->right->right, key);
                // Check if root->right->right subtree is not null
                if (root->right->right) {
                    root->right = leftRotate(root->right);
                }
            } else if (key < root->right->key) {
                root->right->left = splay(root->right->left, key);
                // Check if root->right->left subtree is not null, then right rotate 
                if (root->right->left) {
                    root->right = rightRotate(root->right);
                }
            }
            return root->right ? leftRotate(root) : root;
        }
    }

    // Preorder traversal method
    void preorder(Node* root) {
        if (!root) {
            return;
        }
        cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
    }

    // Find the minimum node
    Node* min(Node* root) {
        if (!root) {
            return root;
        }
        while (root->left) {
            root = root->left;
        }
        return root;
    }

    // Find the maximum node
    Node* max(Node* root) {
        if (!root) {
            return root;
        }
        while (root->right) {
            root = root->right;
        }
        return root;
    }

public:

    // Insert method
    void insert(int key) {
        if (!root) {
            // If tree is null or empty then create a new node
            root = new Node(key);
        } else {
            root = splay(root, key);
            // Splay the root based on the key
            // Now root may now contain key 
            if (key < root->key) {
                // If key < root->key
                // So root now belongs to the right part of key
                Node* newnode = new Node(key);
                newnode->right = root;
                newnode->left = root->left;
                root->left = nullptr;
                root = newnode;
            } else if (key > root->key) {
                Node* newnode = new Node(key);
                newnode->left = root;
                newnode->right = root->right;
                root->right = nullptr;
                root = newnode;
            }
            // If key exists, we don't need to do anything
        }
    }

    void preorder() {
        preorder(root);
    }

    // Public search method
    bool search(int key) {
        // This method will return true if key exists
        if (!root) {
            return false;
        }
        root = splay(root, key);
        // If root contains the key 
        if (root->key == key) {
            return true;
        }
        return false;
    }

    // Remove method
    void remove(int key) {
        if (!root) {
            return;
        }
        root = splay(root, key);
        if (key == root->key) {
            if (!root->left && !root->right) {
                delete root;
                root = nullptr;
            } else if (!root->left) {
                Node* rightChild = root->right;
                delete root;
                root = rightChild;
            } else if (!root->right) {
                Node* leftChild = root->left;
                delete root;
                root = leftChild;
            } else {
                // Both children are present
                Node* temp = root;
                root = splay(root->left, key);
                root->right = temp->right;
                delete temp;
            }
        }
    }
};

// Test the implementation
int main() {
    SplayTree tree;
    tree.insert(11);
    tree.insert(9);
    tree.insert(10);
    tree.insert(8);
    tree.insert(12);
    tree.insert(13);
    // After insertion, the last inserted value will be the root 
    // This tree is used for cache implementation
    // The search method will also make the searched key the root or recently inserted key
    tree.preorder();
    cout << endl;
    tree.remove(13);
    cout << tree.search(13); // Should print 0 (false) since 13 was removed
    cout << endl;
    tree.preorder();
    return 0;
}
