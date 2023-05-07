#ifndef BST_H
#define BST_H
#include<iostream>
#include<iomanip>
#include<functional>
#include<queue> 
class BST
{
public:

    class Node
    {
    public:
        Node(int value, Node* left, Node* right);
        Node();
        Node(const Node& node);
        // ~Node(){std::cout << "deconstructor for "<< value <<"called" << std::endl;}

        int value;
        Node* left;
        Node* right;
        Node operator=(const Node& node);
        friend std::ostream& operator<<(std::ostream& os, const Node& node);
        friend bool operator<(const Node& node, int val);
        friend bool operator>(const Node& node, int val);
        friend bool operator<=(const Node& node, int val);
        friend bool operator>=(const Node& node, int val);
        friend bool operator==(const Node& node, int val);
        friend bool operator!=(const Node& node, int val);
        friend bool operator<(int val, const Node& node);
        friend bool operator>(int val, const Node& node);
        friend bool operator<=(int val, const Node& node);
        friend bool operator>=(int val, const Node& node);
        friend bool operator==(int val, const Node& node);
        friend bool operator!=(int val, const Node& node);
    };
    BST();
    BST(std::initializer_list<int>&& init);
    BST(const BST& another);
    BST(BST&& another);

    ~BST();

    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func)const;
    size_t length()const;

    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);

    BST operator++();
    BST operator++(int);
    BST operator=(const BST& bst);
    BST operator=(BST&& bst);
    friend std::ostream& operator<<(std::ostream& os, BST& bst);
    

private:
    Node* root;
};
#endif //BST_H