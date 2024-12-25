#include <iostream>
#include <algorithm>
#include <tuple>
#include <list>
#include <queue>
#include <limits>
#include<map>

using namespace std;

typedef int Elem; // base element type

// a node of the tree

struct Node {         

    Elem    elt;   // element value
    
    Node*   par;   // parent
    
    Node*   left;  // left child
   
    Node*   right; // right child



 // constructor

    Node() : elt(), par(NULL), left(NULL), right(NULL) { } 

};

// position in the tree

class Position { 

    private:

        Node* v; // pointer to the node

    public:

        Position(Node* _v = NULL) : v(_v) { } // constructor

        Elem& operator*() { return v->elt; } // get element



 // get left, right, parent child

 Position left() const { return Position(v->left); } 

 Position right() const { return Position(v->right); }

 Position parent() const { return Position(v->par); } 


 // is root or external/leaf?

 bool isRoot() const { return v->par == NULL; } 

 bool isExternal() const { 

   return v->left == NULL && v->right == NULL; 

 } 
 

 friend class LinkedBinaryTree; // give tree access

};



    typedef std::list<Position> PositionList; // list of positions

    typedef int Elem; // base element type

class LinkedBinaryTree {

    protected: // insert Node declaration here...

    public: // insert Position declaration here...

    public: 

        LinkedBinaryTree(); // constructor
        
        int size() const; // number of nodes
        
        bool empty() const; // is tree empty?
        
        Position root() const; // get the root
        
        void addRoot(); // add root to empty tree
         
        void destroyTree(Node* node); 

        
        PositionList positions() const; // list of nodes
        
         // expand external node
        
        void expandExternal(const Position& p);

         // remove p and parent
        
        Position removeAboveExternal(const Position& p); 
        
         // housekeeping functions omitted...
        
        protected: // local utilities
        
            void preorder(Node* v, PositionList& pl) const; 
        
        private:
        
            Node* _root; // pointer to the root
        
            int n; // number of nodes

};

// constructor

LinkedBinaryTree::LinkedBinaryTree() : _root(NULL), n(0) { }

// destructor
LinkedBinaryTree::~LinkedBinaryTree() {
    if (_root != NULL) {
        destroyTree(_root);
    }
}

void LinkedBinaryTree::destroyTree(Node* node) {
    if (node != NULL) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}
  

// number of nodes

int LinkedBinaryTree::size() const {

 return n;

}



// is tree empty?

bool LinkedBinaryTree::empty() const {

 return size() == 0;

}



// get the root

LinkedBinaryTree::Position LinkedBinaryTree::root() const {

 return Position(_root);

}


// add root to empty tree

void LinkedBinaryTree::addRoot() {

 _root = new Node; n = 1;

}

// list of all nodes

LinkedBinaryTree::PositionList LinkedBinaryTree::positions() const {

 PositionList pl;

 preorder(_root, pl); // preorder traversal

 return PositionList(pl); // return resulting list

}



// preorder traversal

void LinkedBinaryTree::preorder(Node* v, PositionList& pl) const {

 pl.push_back(Position(v)); // add this node

 if (v->left != NULL) { // traverse left subtree


 }

 if (v->right != NULL) { // traverse right subtree

   preorder(v->right, pl);

 }

}

// expand external node

void LinkedBinaryTree::expandExternal(const Position& p) {

 Node* v = p.v;       	  // p's node



 v->left = new Node;         // add a new left child

 v->left->par = v;      	  // v is its parent



 v->right = new Node;        // and a new right child

 v->right->par = v;          // v is its parent


 n += 2;        	         // two more nodes

}

/ remove p and parent

LinkedBinaryTree::Position        

LinkedBinaryTree::removeAboveExternal(const Position& p) {

 // get p's node and parent

 Node* w = p.v;  Node* v = w->par;

 Node* sib = (w == v->left ?  v->right : v->left);



 // child of root?

 if (v == _root) {

   _root = sib; // ...make sibling root

   sib->par = NULL;

 } else {

   Node* gpar = v->par; // w's grandparent

   if (v == gpar->left) {

     gpar->left = sib; // replace parent by sib

   } else {

     gpar->right = sib;

   }

   sib->par = gpar;

 }

 delete w; delete v; // delete removed nodes

 n -= 2; // two fewer nodes

 return Position(sib);

}