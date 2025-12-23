#pragma once
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

enum Color { RED, BLACK };

class Node {
public:
    int data;
    Node *left, *right, *p;
    Color color;

    Node(int d) : data(d), left(nullptr), right(nullptr), p(nullptr), color(RED) {}
};

class RBTree {
private:
    Node* root;
    Node* Nil;

     // Private Helper Functions

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != Nil) y->left->p = x;
        y->p = x->p;
        if (x->p == Nil) root = y;
        else if (x == x->p->left) x->p->left = y;
        else x->p->right = y;
        y->left = x;
        x->p = y;
    }

    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != Nil) y->right->p = x;
        y->p = x->p;
        if (x->p == Nil) root = y;
        else if (x == x->p->right) x->p->right = y;
        else x->p->left = y;
        y->right = x;
        x->p = y;
    }

    void transplant(Node* u, Node* v) {
        if (u->p == Nil) root = v;
        else if (u == u->p->left) u->p->left = v;
        else u->p->right = v;
        v->p = u->p;
    }

    void deleteFixup(Node* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->p->left) {
                Node* w = x->p->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->p->color = RED;
                    leftRotate(x->p);
                    w = x->p->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->p;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->p->right;
                    }
                    w->color = x->p->color;
                    x->p->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->p);
                    x = root;
                }
            } else {
                Node* w = x->p->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->p->color = RED;
                    rightRotate(x->p);
                    w = x->p->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->p;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->p->left;
                    }
                    w->color = x->p->color;
                    x->p->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->p);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    void insertFixup(Node* z) {
        while (z->p->color == RED) {
            if (z->p == z->p->p->left) {
                Node* y = z->p->p->right;
                if (y->color == RED) {
                    z->p->color = BLACK;
                    y->color = BLACK;
                    z->p->p->color = RED;
                    z = z->p->p;
                } else {
                    if (z == z->p->right) {
                        z = z->p;
                        leftRotate(z);
                    }
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    rightRotate(z->p->p);
                }
            } else {
                Node* y = z->p->p->left;
                if (y->color == RED) {
                    z->p->color = BLACK;
                    y->color = BLACK;
                    z->p->p->color = RED;
                    z = z->p->p;
                } else {
                    if (z == z->p->left) {
                        z = z->p;
                        rightRotate(z);
                    }
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    leftRotate(z->p->p);
                }
            }
        }
        root->color = BLACK;
    }

    void destroyRecursive(Node* node) {
        if (node != Nil) {
            destroyRecursive(node->left);
            destroyRecursive(node->right);
            delete node;
        }
    }

public:
    RBTree() {
        Nil = new Node(0);
        Nil->color = BLACK;
        Nil->left = Nil->right = Nil->p = Nil;
        root = Nil;
    }

    ~RBTree() {
        destroyRecursive(root);
        delete Nil;
    }

    Node* treeMinimum(Node* x) {
        while (x->left != Nil) x = x->left;
        return x;
    }

    Node* search(int k) {
        Node* x = root;
        while (x != Nil && k != x->data) {
            if (k < x->data) x = x->left;
            else x = x->right;
        }
        return x;
    }

    void insert(int data) {
        Node* z = new Node(data);
        Node* y = Nil;
        Node* x = root;
        while (x != Nil) {
            y = x;
            if (z->data < x->data) x = x->left;
            else x = x->right;
        }
        z->p = y;
        if (y == Nil) root = z;
        else if (z->data < y->data) y->left = z;
        else y->right = z;
        z->left = z->right = Nil;
        z->color = RED;
        insertFixup(z);
    }

    void remove(int data) {
        Node* z = search(data);
        if (z == Nil) return;

        Node* x;
        Node* y = z;
        Color y_original_color = y->color;

        if (z->left == Nil) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == Nil) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = treeMinimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->p == z) {
                x->p = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->p = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->p = y;
            y->color = z->color;
        }
        delete z; 
        if (y_original_color == BLACK) {
            deleteFixup(x);
        }
    }

    int getHeight(Node* node) {
        if (node == Nil) return 0;
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }

    Node* getRoot() { return root; }
    Node* getNil() { return Nil; }
};
