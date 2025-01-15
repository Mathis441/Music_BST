#include "music.hpp"
#include <iostream>
#include <algorithm>
// Node constructor
Node::Node(const Music &music) : data(music), left(nullptr), right(nullptr), height(1) {}
// MusicBST constructor
MusicBST::MusicBST() : root(nullptr) {}
// Destructor helper to delete all nodes
MusicBST::~MusicBST() {
    while (root) {
        root = deleteNode(root, root->data.title);
    }
}
// Helper function to get the height of a node
int MusicBST::getHeight(Node *node) {
    return node ? node->height : 0;
}
// Helper function to get the balance factor of a node
int MusicBST::getBalanceFactor(Node *node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}
// Helper function to perform a right rotation
Node *MusicBST::rotateRight(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}
// Helper function to perform a left rotation
Node *MusicBST::rotateLeft(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}
// Helper function to insert a music into the AVL tree
Node *MusicBST::insert(Node *node, const Music &music) {
    if (!node)
        return new Node(music);
    if (music.title < node->data.title)
        node->left = insert(node->left, music);
    else if (music.title > node->data.title)
        node->right = insert(node->right, music);
    else
        return node;
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalanceFactor(node);
    if (balance > 1 && music.title < node->left->data.title)
        return rotateRight(node);
    if (balance < -1 && music.title > node->right->data.title)
        return rotateLeft(node);
    if (balance > 1 && music.title > node->left->data.title) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && music.title < node->right->data.title) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}
// Helper function to find the node with the minimum value
Node *MusicBST::minValueNode(Node *node) {
    while (node->left)
        node = node->left;
    return node;
}
// Helper function to delete a music from the AVL tree
Node *MusicBST::deleteNode(Node *node, const std::string &title) {
    if (!node)
        return node;
    if (title < node->data.title)
        node->left = deleteNode(node->left, title);
    else if (title > node->data.title)
        node->right = deleteNode(node->right, title);
    else {
        if (!node->left || !node->right) {
            Node *temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }
        Node *temp = minValueNode(node->right);
        node->data = temp->data;
        node->right = deleteNode(node->right, temp->data.title);
    }
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalanceFactor(node);
    if (balance > 1 && getBalanceFactor(node->left) >= 0)
        return rotateRight(node);
    if (balance > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && getBalanceFactor(node->right) <= 0)
        return rotateLeft(node);
    if (balance < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}
// Helper function to perform an inorder traversal of the AVL tree
void MusicBST::inorder(Node *node, std::vector<Music> &musicList) {
    if (node) {
        inorder(node->left, musicList);
        musicList.push_back(node->data);
        inorder(node->right, musicList);
    }
}
// Function to add a music to the AVL tree
void MusicBST::addMusic(const Music &music) {
    root = insert(root, music);
}
// Function to remove a music from the AVL tree
void MusicBST::removeMusic(const std::string &title) {
    root = deleteNode(root, title);
}
// Function to display all music in the AVL tree
void MusicBST::displayMusic() {
    std::vector<Music> musicList;
    inorder(root, musicList);
    for (const auto &music : musicList) {
        std::cout << "Title: " << music.title << ", Artist: " << music.artist << std::endl;
    }
}