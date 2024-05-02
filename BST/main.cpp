#include <bits/stdc++.h>
using namespace std;

// Node structure for BST
struct Node
{
  int value;
  Node *left;
  Node *right;

  Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Function to insert a new value into the BST
/**
 * Inserts a new node with the given value into the binary search tree.
 * If the tree is empty, the new node becomes the root.
 * If the value is less than the root's value, it is inserted into the left subtree.
 * If the value is greater than or equal to the root's value, it is inserted into the right subtree.
 *
 * @param root A reference to the root node of the binary search tree.
 * @param value The value to be inserted into the tree.
 */
void treeInsert(Node *&root, int value)
{
  if (root == nullptr)
  {
    root = new Node(value);
  }
  else if (value < root->value)
  {
    treeInsert(root->left, value);
  }
  else
  {
    treeInsert(root->right, value);
  }
}

// Function to search for a value in the BST
/**
 * Searches for a value in a binary search tree.
 *
 * @param root The root node of the binary search tree.
 * @param value The value to search for.
 * @return True if the value is found, false otherwise.
 */
bool treeSearch(Node *root, int value)
{
  if (root == nullptr)
  {
    cout << "not found" << endl;
    return false;
  }
  cout << root->value << " "; // Print node's value as we search
  if (value == root->value)
  {
    cout << "found" << endl;
    return true;
  }
  else if (value < root->value)
  {
    return treeSearch(root->left, value);
  }
  else
  {
    return treeSearch(root->right, value);
  }
}

// Function to perform a preorder traversal of the BST
/**
 * Performs a preorder traversal of a binary tree rooted at the given node.
 * Prints the values of the nodes in the order they are visited.
 *
 * @param root A pointer to the root node of the binary tree.
 */
void preorderTraversal(Node *root)
{
  if (root != nullptr)
  {
    cout << root->value << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
  }
}

/**
 * Performs an inorder traversal of a binary tree rooted at the given node.
 * Prints the values of the nodes in ascending order.
 *
 * @param root A pointer to the root node of the binary tree.
 */
void inorderTraversal(Node *root)
{
  if (root != nullptr)
  {
    inorderTraversal(root->left);
    cout << root->value << " ";
    inorderTraversal(root->right);
  }
}

/**
 * Performs a postorder traversal of a binary tree rooted at the given node.
 *
 * @param root A pointer to the root node of the binary tree.
 */
void postorderTraversal(Node *root)
{
  if (root != nullptr)
  {
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->value << " ";
  }
}

// Function to clear the BST
/**
 * Deletes the entire binary tree rooted at the given node.
 * This function recursively deletes the left and right subtrees
 * before deleting the current node.
 *
 * @param root A reference to the root node of the binary tree.
 */
void deleteTree(Node *&root)
{
  if (root == nullptr)
    return;
  deleteTree(root->left);  // Recursively delete left subtree
  deleteTree(root->right); // Recursively delete right subtree
  delete root;             // Delete the current node
  root = nullptr;
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    cerr << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }

  ifstream ifs(argv[1]);
  if (!ifs.is_open())
  {
    cerr << "Could not open file: " << argv[1] << endl;
    return 1;
  }

  string length;
  getline(ifs, length);
  Node *bstRoot = nullptr; // Correct initialization for a pointer
  string command;
  string value;

  for (int i = 0; i < stoi(length); i++)
  {
    ifs >> command;
    if (command == "ADD")
    {
      ifs >> value;
      cout << "Adding " << value << endl;
      int input = stoi(value);
      treeInsert(bstRoot, input);
    }
    else if (command == "FIND")
    {
      ifs >> value;
      int input = stoi(value);
      cout << "Looking for " << value << "... ";
      treeSearch(bstRoot, input);
    }
    else if (command == "CLEAR")
    {
      cout << "(tree deleted!)" << endl;
      deleteTree(bstRoot);
    }
    else if (command == "PREORDER")
    {
      cout << "PREORDER: ";
      preorderTraversal(bstRoot);
      cout << endl;
    }
    else if (command == "INORDER")
    {
      cout << "INORDER: ";
      inorderTraversal(bstRoot);
      cout << endl;
    }
    else if (command == "POSTORDER")
    {
      cout << "POSTORDER: ";
      postorderTraversal(bstRoot);
      cout << endl;
    }
  }

  // Cleanup
  deleteTree(bstRoot);
  return 0;
}
