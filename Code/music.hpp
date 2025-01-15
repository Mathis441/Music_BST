#ifndef MUSIC_HPP
#define MUSIC_HPP
#include <string>
#include <vector>
// Music structure
struct Music {
    std::string title;
    std::string artist;
};
// Node structure
struct Node {
    Music data;
    Node *left;
    Node *right;
    int height;
    Node(const Music &music);
};
// AVL Tree Class
class MusicBST {
private:
    Node *root;
    int getHeight(Node *node);
    int getBalanceFactor(Node *node);
    Node *rotateRight(Node *y);
    Node *rotateLeft(Node *x);
    Node *insert(Node *node, const Music &music);
    Node *minValueNode(Node *node);
    Node *deleteNode(Node *node, const std::string &title);
    void inorder(Node *node, std::vector<Music> &musicList);
public:
    MusicBST();
    ~MusicBST();
    void addMusic(const Music &music);
    void removeMusic(const std::string &title);
    void displayMusic();
};
#endif // MUSIC_HPP