#include <iostream>
#include <iomanip>

struct Node {
    int _data{0};
    Node *_left{nullptr};
    Node *_right{nullptr};
};

class BST {
    Node *_root{nullptr};
public:
    // recursive insert function
    void insert(int data) {
        insert(data, _root);
    }

    // non-recursive remove function
    void remove(int data) {
        auto node = _root;
        auto parent = (Node *) nullptr;

        // find node to delete
        while (node != nullptr) {
            if (data < node->_data) {
                parent = node;
                node = node->_left;
            } else if (data > node->_data) {
                parent = node;
                node = node->_right;
            } else {
                // found the node we want to delete!
                break;
            }
        }

        // if we didn't find the node, no reason to stay!
        if (node == nullptr) return;

        // if the node has two children
        // use right-most node of the left tree as the successor
        if (node->_left != nullptr && node->_right != nullptr) {

            // take the left path
            auto successor = node->_left;

            // then go as far right as possible
            parent = node;
            while (successor->_right != nullptr) {
                parent = successor;
                successor = successor->_right;
            }

            // swap values with the successor
            node->_data = successor->_data;

            // the successor will now be the node to delete
            node = successor;
        }

        // assume node has a left child
        auto subtree = node->_left;

        // was that assumption correct?
        if (subtree == nullptr) {
            subtree = node->_right;
        }

        // which child of my parent am I?
        if (parent == nullptr) {
            // we are deleting the root node
            _root = subtree;
        } else if (parent->_left == node) {
            // we are on the left side of the parent
            parent->_left = subtree;
        } else if (parent->_right == node) {
            // we are on the right side of the parent
            parent->_right = subtree;
        }

        delete node;
    }

private:
    void insert(int data, Node *&node) {
        if (node == nullptr) {
            node = new Node({data});
        } else if (data < node->_data) {
            insert(data, node->_left);
        } else if (data > node->_data) {
            insert(data, node->_right);
        } else {
            std::cout << "Node value " << node->_data << " already exists." << std::endl;
        }
    }

    void print_tree(std::ostream &output, Node *&node, int indent) {
        if (node != nullptr) {
            print_tree(output, node->_right, indent + 8);
            output << std::setw(indent) << node->_data << std::endl;
            print_tree(output, node->_left, indent + 8);
        }
    }

    friend std::ostream &operator<<(std::ostream &output, BST &bst);
};

std::ostream &operator<<(std::ostream &output, BST &bst) {
    bst.print_tree(output, bst._root, 0);
    return output;
}

int main() {

    BST bst;

    // Test 1 - insert some nodes
    std::cout << "Test 1 - insert some nodes" << std::endl;
    std::cout << "--------------------------" << std::endl;

    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);
    std::cout << bst << std::endl;

    // Test 2 - delete a node with no children
    std::cout << "Test 2 - delete a node with no children" << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    bst.remove(2);
    std::cout << bst << std::endl;

    // Test 3 - delete a node with one child
    std::cout << "Test 3 - delete a node with one child" << std::endl;
    std::cout << "-------------------------------------" << std::endl;

    bst.remove(3);
    std::cout << bst << std::endl;

    // Test 4 - delete a node with two children
    std::cout << "Test 4 - delete a node with two children" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    bst.remove(7);
    std::cout << bst << std::endl;

    // Test 5 - delete the root node
    std::cout << "Test 5 - delete the root node" << std::endl;
    std::cout << "-----------------------------" << std::endl;

    bst.remove(5);
    std::cout << bst << std::endl;
    std::cout << "-----" << std::endl;
    bst.remove(4);
    std::cout << bst << std::endl;
    std::cout << "-----" << std::endl;
    bst.remove(6);
    std::cout << bst << std::endl;
//    bst.remove(8);
//    std::cout << bst << std::endl;

    return 0;
}