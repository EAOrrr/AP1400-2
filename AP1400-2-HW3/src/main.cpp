#include <iostream>
#include <gtest/gtest.h>
#include "bst.h"

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        // debug section
    BST bst1{16, 4, 25, 2, 13, 38, 14, 27, 40, 39};
    // std::cout << bst1;
    BST::Node** node_p = bst1.find_successor(25);
    // BST::Node** node_p = bst1.find_parrent(1);
    std::cout << node_p<< std::endl;
    BST::Node* node = *node_p;
    std::cout << node_p;
    std::cout << "node->value: " << node->value << std::endl;
    std::cout << "node->left: " << node->left << std::endl;
    std::cout << "node->right: " << node->right << std::endl;
    if(node->left != nullptr)
    std::cout << "node->left->value: " << node->left->value << std::endl;
    if(node->right != nullptr)
    std::cout << "node->right->value: " << node->right->value << std::endl;
    // std::cout << bst1;
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;   
}