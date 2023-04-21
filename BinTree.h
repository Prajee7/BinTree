/**
 * |-------------------------------------------------------------|
 * BinTree.h
 * Prajeet Pounraj
 * CSS 343 - Prof. Rahman
 * April 20, 2023
 * |-------------------------------------------------------------|
 * Description:
 * Implementation of a binary search tree class that includes functions to create, manipulate
 * and display a binary search tree. The program can read data from a file with lines of strings
 * to construct binary search trees. The program includes functions to manipulate the binary search
 * tree, including inserting nodes, retrieving NodeData*, checking if the tree is empty, emptying
 * the tree, and displaying the tree sideways with the help of other methods. 
 * |-------------------------------------------------------------|
 * Assume:
 * A statically allocated array of 100 NULL elements for the bstreeToArray function and builds a 
 * balanced BinTree recursively by finding the root at (low+high)/2, where low is the lowest subscript 
 * of the array range and high is the highest.
*/

#ifndef BINTREE_H
#define BINTREE_H

#include "nodedata.h"

class BinTree {
    // Overloading << to display the tree using inorder traversal.
    friend std::ostream& operator<<(std::ostream &outStream, const BinTree &binTree);

    private:
        // Creating struct to help create a tree.
        struct Node {
            NodeData *data; // pointer to data object
            Node *leftNode; // left subtree pointer
            Node *rightNode; 
            
 
        };
        Node *root; // root of the tree

        // helper for overloader << .
        void inOrderHelper(Node *currNode) const;

        // helper for displaying the tree sideways.
        void sideways(Node *currNode, int loc) const; // helper for displaySideways()

        // helper for make empty public method.
        void makeEmptyHelper(Node *&currNode);

        // helper for = public method.
        void copyTreeHelper(Node *currNode, Node *other);

        // helper for == public method through recursion.
        bool equalAssignmentHelper(Node *currTree, Node *otherTree) const;

        // helper for insert method for the tree in public. 
        bool insertHelper(Node *&currNode, NodeData *newNode);

        // helper for retrieve method for the tree in public. 
        bool retrieveHelper(Node *&currNode, const NodeData &node, NodeData *&otherNode) const;

        // helper to get height method.
        int heightHelper(Node *node) const;

        // helper method to transfer data from the BSTree to an array.
        void bstreeToArrayHelper(int &arrSize, NodeData *bst2arr[], Node *currNode);

        // helper method to transfer data from an Array to a BSTree.
        void arrayToBSTreeHelper(NodeData *bst2arr[], int low, int high);


    public:

    BinTree(); // constructor
	BinTree(const BinTree &binTree); // copy constructor
	~BinTree();	// destructor, calls makeEmpty	

	bool isEmpty() const; // true if tree is empty, otherwise false
	void makeEmpty(); // make the tree empty so isEmpty returns true

    // Operators
	BinTree& operator=(const BinTree &other);
	bool operator==(const BinTree &other) const;
	bool operator!=(const BinTree &other) const;

    // inserts nodes into a tree.
	bool insert(NodeData *newNode);

    // To get the NodeData* of a given object in the tree (via pass-by-reference parameter) and reports whether the object is found (true or false).
	bool retrieve(const NodeData &fNode, NodeData *&valNode);

    // displays the tree sideways.
	void displaySideways() const;	

    // To find the height of a given value in the tree.
    /**
     * you do not get to know that the tree is a binary search tree.
     * You must solve the problem for a general binary tree where data could be stored anywhere
    */
    int getHeight (const NodeData &node) const;

    // To fill an array of Nodedata* by using an inorder traversal of the tree. It leaves the tree empty.
    /**
     * Assume a statically allocated array of 100 NULL elements. No size error checking necessary.
    */
    void bstreeToArray(NodeData *bst2arr[]);

    /**
     * To builds a balanced BinTree from a sorted array of NodeData* leaving the array filled with NULLs. 
     * The root (recursively) is at (low+high)/2 where low is the lowest subscript of the array range and high is the highest.
    */
    void arrayToBSTree(NodeData *bst2arr[]);

};

#endif
 