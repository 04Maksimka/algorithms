#include <iostream>
#include <vector>

struct Node {
    int value;
    Node* left = nullptr;
    Node* right = nullptr;
};

class BST {
public:
    void insert(int value) {
        if (!root) {
            root = new Node{value};
            return;
        }

        Node* current = root;
        while (true) {
            if (value < current->value) {
                if (!current->left) {
                    current->left = new Node{value};
                    break;
                }
                current = current->left;
            } else {
                if (!current->right) {
                    current->right = new Node{value};
                    break;
                }
                current = current->right;
            }
        }
    }

private:
    Node* root = nullptr;
};

int main() {

}