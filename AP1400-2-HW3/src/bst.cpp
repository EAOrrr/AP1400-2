#include "bst.h"
/*for class Node*/
BST::Node::Node(int value, Node* left, Node* right):value(value), left(left), right(right){};
BST::Node::Node():value{0}, left{nullptr}, right{nullptr}{};
BST::Node::Node(const Node& node):value(node.value), left(node.left), right(node.right){std::cout << "copy constructor for Node called" << std::endl;};
BST::Node BST::Node::operator=(const BST::Node& node){
    std::cout << "copy assignment called"<< std::endl;
    value = node.value;
    if(node.left != nullptr) delete node.left;
    left = node.left;
    if(node.right != nullptr) delete node.right;
    right = node.right;
    std::cout << *this;
    return *this;
}
std::ostream& operator<<(std::ostream& os, const BST::Node& node){
    os << std::setw(16) << std::left << &node << 
        "=>value:" << std::setw(16) << std::left << node.value 
        << "left:" << std::setw(16)<< std::left << node.left 
        << "right:" << std::setw(16) <<  std::left << node.right 
        << std::endl;
    return os;
}

bool operator<(const BST::Node& node, int val){
    return node.value < val;
}
bool operator>(const BST::Node& node, int val){
    return node.value > val;
}
bool operator<=(const BST::Node& node, int val){
    return node.value <= val;
}
bool operator>=(const BST::Node& node, int val){
    return node.value >= val;
}
bool operator==(const BST::Node& node, int val){
    return node.value == val;
}
bool operator!=(const BST::Node& node, int val){
    return node.value != val;
}
bool operator<(int val, const BST::Node& node){
    return val < node.value;
}
bool operator>(int val, const BST::Node& node){
    return val > node.value;
}
bool operator<=(int val, const BST::Node& node){
    return val <= node.value;
}
bool operator>=(int val, const BST::Node& node){
    return val >= node.value;
}
bool operator==(int val, const BST::Node& node){
    return val == node.value;
}
bool operator!=(int val, const BST::Node& node){
    return val != node.value;
}

BST::BST():root(nullptr){};
BST::BST(const BST& another):root(nullptr){
    // need to constuct a new bst, or will result in segmention fault when deconstrucing 
     std::queue<Node*> allNodesOfAnother{};
    another.bfs([&allNodesOfAnother](Node*& node){
        allNodesOfAnother.push(node);
    });

    while(!allNodesOfAnother.empty()){
        this->add_node(allNodesOfAnother.front()->value);
        allNodesOfAnother.pop();
    }
}
BST::BST(BST&& another):root(nullptr){
    // use std::move will result in double free when deconstructing 
    // root = std::move(another.root);
    root = std::exchange(another.root, nullptr);
}
BST::BST(std::initializer_list<int>&& init):root(nullptr){
    for(int value: init){
        this->add_node(value);
    }
}
BST::~BST()
{
	std::vector<Node*> nodes;
	bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
	for(auto& node: nodes)
		delete node;
}
BST::Node*& BST::get_root(){
    return root;
}
void BST::bfs(std::function<void(BST::Node*& node)> func) const{
    std::queue<Node*> allNode;
    if(root != nullptr)
        allNode.push(root);
    while (!allNode.empty()){
        Node* currentNode = allNode.front();
        allNode.pop();
        if(currentNode->left != nullptr){
            allNode.push(currentNode->left);
        }
        if(currentNode->right != nullptr){
            allNode.push(currentNode->right);
        }
        func(currentNode);
    }
}
size_t BST::length()const{
    int size = 0;
    bfs([&size](Node*&node){size += 1;});
    return size;
}
bool BST::add_node(int value){
    if(root == nullptr){
        root = new Node(value, nullptr, nullptr);
        return true;
    }
    std::function<bool(BST::Node*& node)> add_helper = [&add_helper, value](Node*& node){
        if(node->value == value)
            return false;
        if(value < node->value){
            if(node->left == nullptr){
                node->left = new Node(value, nullptr, nullptr);
                return true;
            }
            else{
                return add_helper(node->left);
            }
        }
        if(node->right == nullptr){
            node->right = new Node(value, nullptr, nullptr);
            return true;
        }
        else{
            return add_helper(node->right);
        }
        
    };
    return add_helper(root);
}
BST::Node** BST::find_node(int value){
    std::function<Node**(Node*& node)> findNodeHelper = [value, &findNodeHelper](Node*& node)->Node**{
        if(node == nullptr) return nullptr;
        if(node->value == value){
            return &node;
        }
        if(value < node->value){
            return findNodeHelper(node->left);
        }
        return findNodeHelper(node->right);
    };
    return  findNodeHelper(root);
}
BST::Node** BST::find_parrent(int value){
    std::function<Node**(Node*& node)> findParrentHelper = 
        [value, &findParrentHelper](Node*& node)->Node**{
        if(node == nullptr || node->value == value) return nullptr;
        
        // Node* next = nullptr;
        // if(value < node->value){
        //     next = node->left;
        // }
        // else{
        //     next = node->right;
        // }
        // if(next == nullptr){
        //     return nullptr;
        // }
        // if(next->value == value){
        //     std::cout <<"return pointer: "<< &node << std::endl;
        //     std::cout << "dereference: "<<node << std::endl;
        //     std::cout << node->left->value << node->right->value << std::endl;
        //     Node** return_value = new Node*{node};
        //     std::cout << *node;
        //     return return_value;
        // }
        // return findParrentHelper(next);
        if(value < node->value){
            if(node->left == nullptr) return nullptr;
            if(node->left->value == value) return &node;
            return findParrentHelper(node->left);
        }
        if(node->right == nullptr) return nullptr;
        if(node->right->value == value) return &node;
        return findParrentHelper(node->right);
    };
    return findParrentHelper(root);
}
BST::Node** BST::find_successor(int value){
    Node** node = find_node(value);
    if(node == nullptr) return nullptr;
    std::function<Node**(Node*& node)> find_successor_helpter= [&find_successor_helpter](Node*& node)->Node**{
        if(node == nullptr) return nullptr;
        if(node->right == nullptr) return &node;
        return find_successor_helpter(node->right);
    };
    return find_successor_helpter((*node)->left);
}
bool BST::delete_node(int value){
    Node ** deleteNode_p = find_node(value);
    Node ** parent_p = find_parrent(value);
    if(deleteNode_p == nullptr) return false;
    Node* deleteNode = *deleteNode_p;
    // if deleteNode is leaf
    if(deleteNode->left == nullptr && deleteNode->right == nullptr){
        // if deleteNode is root
        if(parent_p == nullptr){
            delete deleteNode;
            root = nullptr;
        }
        else{
            Node* parent = *parent_p;
            if(parent->left == deleteNode){
                delete parent->left;
                parent->left = nullptr;
            }
            else{
                delete parent->right;
                parent->right = nullptr;
            }
        }
    }
    // else if deleteNode has only one branch
    else if(deleteNode->left == nullptr || deleteNode->right == nullptr){
        // if deleteNode is root;
        if(parent_p == nullptr){
            if(deleteNode->left != nullptr){
                // Node* deleteNode = deleteNode;
                root = deleteNode->left;
                delete deleteNode;
            }
            else{
                // Node* deleteNode = deleteNode;
                root = deleteNode->right;
                delete deleteNode;
            }
        }
        else{
            Node* parent = *parent_p;
            if(parent->left == deleteNode){
                if(deleteNode->left != nullptr){
                    parent->left = deleteNode->left;
                }
                else{
                    parent->left = deleteNode->right;
                }
            }
            else{
                if(deleteNode->left != nullptr){
                    parent->right = deleteNode->left;
                }
                else{
                    parent->right = deleteNode->right;
                }
            }
            delete deleteNode;
        }
    }
    // else deleteNode has 2 branches
    else{
        Node** successor_p = find_successor(value);
        Node* successor = *successor_p;
        // remove successor
        Node** successorParent_p = find_parrent(successor->value);
        Node* successorParent = *successorParent_p;
        if(successorParent->left == successor){
            successorParent->left = successor->left;
        }
        else{
            successorParent->right = successor->left;
        }
        deleteNode->value = successor->value;
        delete successor;

    }
    return true;
}
BST BST::operator=(const BST& another){
    // delete current nodes
    if(this == &another) return *this;
    std::vector<Node*> nodes;
    bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
    for(auto& node: nodes)
        delete node;
    // record the node of another(using bfs)
    std::queue<Node*> allNodesOfAnother{};
    another.bfs([&allNodesOfAnother](Node*& node){
        allNodesOfAnother.push(node);
    });
    while(!allNodesOfAnother.empty()){
        this->add_node(allNodesOfAnother.front()->value);
        allNodesOfAnother.pop();
    }
    return *this;
}
BST BST::operator=(BST&& bst){
    std::vector<Node*> nodes;
    bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
    for(auto& node: nodes)
        delete node;

    root = std::exchange(bst.root, nullptr);
    return *this;
}

BST BST::operator++(){
    bfs([](BST::Node *& node){node->value += 1;});
    return *this;
}

BST BST::operator++(int){
    BST temp = *this;
    bfs([](BST::Node *& node){node->value += 1;});
    return temp;
}

std::ostream& operator<<(std::ostream& os, BST& bst){
    os << std::string(80, '*') << std::endl;
    bst.bfs([&os](BST::Node*& node){os << *node;});
    os << "binary search tree size: " << bst.length() << std::endl;
    os << std::string(80, '*') << std::endl;
    return os;
}