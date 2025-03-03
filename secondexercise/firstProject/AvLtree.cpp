#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#define TOL 1
using namespace std;

template <typename T>
class AVLNode {
public:
    T key;
    AVLNode<T>* left;
    AVLNode<T>* right;
    int height;
    AVLNode(T key) {
        this->key = key;
        left = right = nullptr;
        height=0;
    }
    int balance_factor(){
        int leftHeight=(this->left)? this->left->height : -1;
        int rightHeight=(this->right)? this->right->height : -1;
        return (leftHeight-rightHeight);
    }
    void updateHeight(){
        int leftHeight=(this->left)? this->left->height : -1;
        int rightHeight=(this->right)? this->right->height : -1;
        this->height=max(leftHeight, rightHeight)+1;
    }
    void left_rotation() {
        if (this->right == nullptr)
            return;
        AVLNode<T>* varA = this->left;
        AVLNode<T>* varB = this->right->left;
        AVLNode<T>* varC = this->right->right;
        T tmp = this->key;
        this->key = this->right->key;
        this->left=new AVLNode<T>(tmp);
        this->left->left = varA;
        this->left->right = varB;
        this->right = varC;
        this->left->updateHeight();
        this->updateHeight();
    }
    void right_rotation() {
        if (this->left == nullptr)
            return;
        AVLNode<T>* varA = this->left->left;
        AVLNode<T>* varB = this->left->right;
        AVLNode<T>* varC = this->right;
        T tmp = this->key;
        this->key = this->left->key;
        this->right=new AVLNode<T>(tmp);
        this->left = varA;
        this->right->left = varB;
        this->right->right = varC;
        this->right->updateHeight();
        this->updateHeight();
    }
    void left_right_rotation() {
        if(this->left){
            this->left->left_rotation();
            this->right_rotation();
        }
    }
    void right_left_rotation() {
        if(this->right){
            this->right->right_rotation();
            this->left_rotation();
        }
    }
};

template <typename T>
class AVLTree {
private:
    AVLNode<T>* root;
    AVLNode<T>*& search(T& elem, AVLNode<T>*& subtree_root) {
        if (subtree_root == nullptr)
            return subtree_root;
        else if (elem == subtree_root->key)
            return subtree_root;
        else if (elem < subtree_root->key)
            return search(elem, subtree_root->left);
        else
            return search(elem, subtree_root->right);
    }
    void balance(AVLNode<T>*& node) {
        if (node == nullptr)
            return;
        else if (node->balance_factor() > TOL) {
            if (node->left && node->left->balance_factor()<0)
                node->left_right_rotation();
            else
                node->right_rotation();

        }
        else if(node->balance_factor() < -TOL){
            if (node->right && node->right->balance_factor()>0)
                node->right_left_rotation();
            else
               node->left_rotation();

        }
    }
    void insert(T& elem, AVLNode<T>*& subtree_root) {
        if (subtree_root == nullptr) {
            subtree_root = new AVLNode<T>(elem);
        }
        else if (elem < subtree_root->key) {
            insert(elem, subtree_root->left);
        }
        else if (elem > subtree_root->key) {
            insert(elem, subtree_root->right);
        }
        balance(subtree_root);
        subtree_root->updateHeight();

    }
    void erase(T& elem, AVLNode<T>*& sub_root){
        if(sub_root){
            if(elem<sub_root->key)
                erase(elem, sub_root->left);
            else if(elem>sub_root->key)
                erase(elem, sub_root->right);
            else{
                if(sub_root->left && sub_root->right){
                    AVLNode<T>* to_swap=findMax(sub_root->left);
                    swap(to_swap->key, sub_root->key);
                    erase(to_swap->key, sub_root->left);
                }
                else if(sub_root->left || sub_root->right){
                    AVLNode<T>*& to_swap=(sub_root->left)? sub_root->left : sub_root->right;
                    swap(to_swap->key, sub_root->key);
                    erase(to_swap->key, to_swap);
                }
                else{
                    delete(sub_root);
                    sub_root=nullptr;
                }
            }
            if(sub_root){
                balance(sub_root);
                sub_root->updateHeight();
            }
        }
    }
    AVLNode<T>* findMax(AVLNode<T>*& subtree_root){
        AVLNode<T>*  roos=subtree_root;
        while(roos->right!=nullptr){
            roos=roos->right;
        }
        return roos;
    }
    AVLNode<T>* findMin(AVLNode<T>*& subtree_root){
        AVLNode<T>*  roos=subtree_root;
        while(roos->left!=nullptr){
            roos=roos->left;
        }
        return roos;
    }
    void preorder(AVLNode<T>*& subtree_root) {
        if (subtree_root != nullptr) {
            cout << subtree_root->key << '\t';
            preorder(subtree_root->left);
            preorder(subtree_root->right);
        }
    }
    void inorder(AVLNode<T>*& subtree_root) {
        if (subtree_root != nullptr) {
            inorder(subtree_root->left);
            cout << subtree_root->key << '\t';
            inorder(subtree_root->right);
        }
    }
    void postorder(AVLNode<T>*& subtree_root) {
        if (subtree_root != nullptr) {
            postorder(subtree_root->left);
            postorder(subtree_root->right);
            cout << subtree_root->key << '\t';
        }
    }
public:
    AVLTree() {
        root = nullptr;
    }
    AVLNode<T>*& look_up(T& elem) {
        return search(elem, this->root);
    }
    bool is_empty(){
		return root==nullptr;
	}
    T getRoot(){
		return root->key;
	}
    void add_node(T& elem) {
        insert(elem, root);
    }
    void remove_node(T& elem){
        erase(elem, root);
    }
    T maximum(){
		return findMax(root)->key;
	}
	T minimum(){
		return findMin(root)->key;
	}
    void preorder() {
        preorder(root);
    }
    void inorder() {
        inorder(root);
    }
    void postorder() {
        postorder(root);
    }
};

