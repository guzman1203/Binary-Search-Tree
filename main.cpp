#include "LinkedBinaryTree.hpp"


int main() {
    
    LinkedBinaryTree tree;
    tree.addRoot();
    auto root = tree.root();
    cout << "Tree Root Element (Initial): " << *root << endl;

    tree.expandExternal(root);
    auto leftChild = root.left();
    *leftChild = 10;

    cout << "Left Child of Root: " << *leftChild << endl;

    return 0;
}
