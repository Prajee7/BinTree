/**
 * |-------------------------------------------------------------|
 * BinTree.cpp
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

#include "bintree.h"

using namespace std;

/**
 * Default Constructor
 */
BinTree::BinTree()
{
    this->root = nullptr;
}

/**
 * Copy Contructor
 */
BinTree::BinTree(const BinTree &binTree)
{
    this->root = nullptr;
    if (binTree.root != nullptr)
        *this = binTree;
}



/**
 * Destructor
 */
BinTree::~BinTree()
{
    makeEmpty();
}

/**
 * Check if tree is empty, if so returns true else false.
 * Does this by checking to see if root is nullptr, in which case the tree is empty.
 */
bool BinTree::isEmpty() const
{
    if (this->root == nullptr)
        return true;

    return false;
}

/**
 * Makes the entire tree empty and deletes it by calling the private helper method, makeEmptyHelper.
 */
void BinTree::makeEmpty()
{
    makeEmptyHelper(root);
}

/**
 * Recursive method that helps delete the entire BSTree.
 */
void BinTree::makeEmptyHelper(Node *&currNode)
{
    if (currNode == nullptr)
    {
        return;
    }
    makeEmptyHelper(currNode->leftNode);
    makeEmptyHelper(currNode->rightNode);
    delete currNode->data;
    currNode->data = nullptr;
    delete currNode;
    currNode = nullptr;
}

/**
 * = Operators that returns the same BinTree with the exact values of the tree within the parameter.
 */
BinTree &BinTree::operator=(const BinTree &other)
{
    if (this != &other)
    {
        this->makeEmpty();
        if (other.root != nullptr) {
            this->root = new Node();
            this->root->data = new NodeData(*other.root->data);
            copyTreeHelper(this->root, other.root);
        }
    }
    return *this;
}

/**
 * Recursive method that helps operator= method set one tree equal the other, essentialy copying the
 * one tree with the other.
 */
void BinTree::copyTreeHelper(Node *newNode, Node *otherNode)
{
    if (otherNode->leftNode != nullptr)
    {
        newNode->leftNode = new Node();
        newNode->leftNode->data = new NodeData(*otherNode->leftNode->data);
        copyTreeHelper(newNode->leftNode, otherNode->leftNode);
    }
    if (otherNode->rightNode != nullptr)
    {
        newNode->rightNode = new Node();
        newNode->rightNode->data = new NodeData(*otherNode->rightNode->data);
        copyTreeHelper(newNode->rightNode, otherNode->rightNode);
    }
}

/**
 * == operator checks if two trees equal each other and returns true if so, else false. and calls
 * a private recursive helper method equalAssigmentHelper().
 */
bool BinTree::operator==(const BinTree &other) const
{
    return equalAssignmentHelper(this->root, other.root);
}

/**
 * Recursive method that compares the nodes in both trees, starting from the root nodes, and returns
 * true or false depending on whether they are equal.
 */
bool BinTree::equalAssignmentHelper(Node *currNode, Node *otherNode) const
{
    if(currNode == nullptr && otherNode == nullptr){
        return true;
    }
    if (currNode == nullptr || otherNode == nullptr)
    {
        return false;
    }
        return *currNode->data == *otherNode->data 
        &&equalAssignmentHelper(currNode->leftNode, otherNode->leftNode) 
            && equalAssignmentHelper(currNode->rightNode, otherNode->rightNode);
}

/**
 * != operator checks to see if two trees are not equal, does this by returning the opposite of the ==
 * operator.
 */
bool BinTree::operator!=(const BinTree &other) const
{
    return !(this->operator==(other));
}

/**
 * Inserts a node into the tree by calling the private method insertHelper().
 */
bool BinTree::insert(NodeData *newNode)
{
    return insertHelper(this->root, newNode);
}

/**
 * Insert helper uses recursive functionality to be able to insert the node in the correct
 * place on the BinTree.
 */
bool BinTree::insertHelper(Node *&currNode, NodeData *newNode)
{
    if (currNode == nullptr)
    {
        currNode = new Node(); // create a new node in the tree to be able to insert.
        currNode->data = newNode;
        currNode->leftNode = nullptr;
        currNode->rightNode = nullptr;
        return true; // returns true after the new node has been added.
    }
    else if (*newNode < *currNode->data)
    {
        return insertHelper(currNode->leftNode, newNode);
    }
    else if (*newNode > *currNode->data)
    {
        return insertHelper(currNode->rightNode, newNode);
    }
    return false; // item is already present before inserting
}

/**
 * retreive function calls on a private method retrieveHelper() to check for NodeData in the
 * tree and returns the pointer when found.
 */
bool BinTree::retrieve(const NodeData &currNode, NodeData *&valNode)
{
    return retrieveHelper(this->root, currNode, valNode);
}

/**
 * a private recursive method that helps the retrieve method to find the node in the tree and
 * returning true when found.
 */
bool BinTree::retrieveHelper(Node *&currNode, const NodeData &node, NodeData *&valNode) const
{
    if (currNode == nullptr)
    {
        return false;
    }
    else if (*currNode->data == node)
    {
        valNode = currNode->data;
        return true;
    }
    else if (*currNode->data < node)
    {
        return retrieveHelper(currNode->rightNode, node, valNode);
    }
    else
    {
        return retrieveHelper(currNode->leftNode, node, valNode);
    }
}

/**
 * A display method that invokes a private helper method that recursivily prints the tree sideways.
 */
void BinTree::displaySideways() const
{
    sideways(root, 0);
}

/**
 * Recursive private method that helps print the BSTree sideways using the height and child nodes.
 */
void BinTree::sideways(Node *currNode, int loc) const
{
    if (currNode != nullptr)
    {
        sideways(currNode->rightNode, loc + 1);
        for (int i = 0; i < loc; i++)
        {
            cout << "    ";
        }
        cout << *currNode->data << endl;
        sideways(currNode->leftNode, loc + 1);
    }
}

/**
 * Traverses the tree to find the node with the given data, incrementing the height variable along
 * the way. If the node is not found, it returns a height of 0. Once the node is found, it calls a
 * recursive private method heightHelper on its left and right children to get their heights, and
 * returns the maximum height.
 */
int BinTree::getHeight(const NodeData &node) const
{
    Node *currNode = root;
    int height = 0;
    bool found = false;

    while (currNode != nullptr && !found)
    {
        if (node == *currNode->data)
        {
            found = true;
        }
        else if (node > *currNode->data)
        {
            currNode = currNode->rightNode;
        }
        else
        {
            currNode = currNode->leftNode;
        }
        height++;
    }

    if (!found)
    {
        return 0;
    }

    int leftHeight = heightHelper(currNode->leftNode);
    int rightHeight = heightHelper(currNode->rightNode);

    return 1 + max(leftHeight, rightHeight);
}

/**
 * recursive helper method that calculates the height of a given node by recursively calling itself on
 * its left and right children, and returning the maximum height.
 */
int BinTree::heightHelper(Node *node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    int leftHeight = heightHelper(node->leftNode);
    int rightHeight = heightHelper(node->rightNode);

    return 1 + max(leftHeight, rightHeight);
}

/**
 * This moves all the data from the BST to the array but calling upon the private method bstreeToArrayHelper
 * and deletes the tree onces its done.
 */
void BinTree::bstreeToArray(NodeData *bst2arr[])
{
    int arrSize = 0;
    this->bstreeToArrayHelper(arrSize, bst2arr, this->root);
    this->makeEmpty();
}

/**
 * Traverses the BST in-order and adds the data elements to the array. When node is nullptr returns.
 * else, the method recursively calls itself on the left subtree, adds the current node's data to
 * the array, increments the array size, and then recursively calls itself on the right subtree.
 */
void BinTree::bstreeToArrayHelper(int &arrSize, NodeData *bst2arr[], Node *currNode)
{
    if (currNode == nullptr)
    {
        return;
    }
    bstreeToArrayHelper(arrSize, bst2arr, currNode->leftNode);
    bst2arr[arrSize] = currNode->data;
    currNode->data = nullptr;
    arrSize++;
    bstreeToArrayHelper(arrSize, bst2arr, currNode->rightNode);
}

/**
 * This moves all the data from the array to a BSTree but calling upon the private method
 * arrayToBSTreeHelper.
 */
void BinTree::arrayToBSTree(NodeData *bst2arr[])
{
    this->makeEmptyHelper(this->root);
    int low = 0;
    int high = 0;
    for (int i = 0; i < 100; ++i)
    {
        if (bst2arr[i] != nullptr)
        {
            high++;
        }
    }
    high--;
    this->root = nullptr;
    arrayToBSTreeHelper(bst2arr, low, high);
}

/**
 * Recursive method that creates a new NodeData at the starting index and calculates
 * the middle index to build the left and right subtrees by using the correct indices
 * of the array. Return a new Node.
 */
void BinTree::arrayToBSTreeHelper(NodeData *bst2arr[], int low, int high)
{
    if (low > high)
    {
        return;
    }
    int mid = (low + high) / 2;
    NodeData *temp = bst2arr[mid];
    bst2arr[mid] = nullptr;
    insert(temp);
    arrayToBSTreeHelper(bst2arr, low, mid - 1);
    arrayToBSTreeHelper(bst2arr, mid + 1, high);
}

/**
 * Recursive function that is helper method for the << overloader. This method prints the
 * tree in-order.
 */
void BinTree::inOrderHelper(Node *currNode) const
{
    if (currNode != nullptr)
    {
        inOrderHelper(currNode->leftNode);
        cout << *(currNode->data) << " ";
        inOrderHelper(currNode->rightNode);
    }
}

/**
 * Overloading << to display the tree using inorder traversal.
 */
ostream &operator<<(std::ostream &outStream, const BinTree &binTree)
{
    binTree.inOrderHelper(binTree.root);
    outStream << endl;
    return outStream;
}


//OLD CODE:
//Implementation fixed. 
//
//  * == operator checks if two trees equal each other and returns true if so, else false. and calls
//  * a private recursive helper method equalAssigmentHelper().
//  */
// bool BinTree::operator==(const BinTree &other) const
// {
//     if(this->root == nullptr && other.root == nullptr){
//         return true;
//     }
//     Node *otherNode = other.root;
//     return equalAssignmentHelper(this->root->rightNode, otherNode->rightNode)
//         &&equalAssignmentHelper(this->root->leftNode, otherNode->leftNode);
// }

// /**
//  * Recursive method that compares the nodes in both trees, starting from the root nodes, and returns
//  * true or false depending on whether they are equal.
//  */
// bool BinTree::equalAssignmentHelper(Node *currNode, Node *otherNode) const
// {
//     if (currNode == nullptr && otherNode == nullptr)
//     {
//         return true;
//     }
//     else if (currNode != nullptr || otherNode == nullptr)
//     {
//         return false;
//     }
//     else if (currNode == nullptr && otherNode != nullptr)
//     {
//         return false;
//     }
//     else if (*currNode->data != *otherNode->data)
//     {
//         return false;
//     }
//     else
//     {
//         return equalAssignmentHelper(currNode->leftNode, otherNode->leftNode) 
//             && equalAssignmentHelper(currNode->rightNode, otherNode->rightNode);
//     }
// }
