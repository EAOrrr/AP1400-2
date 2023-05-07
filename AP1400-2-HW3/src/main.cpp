#include <iostream>
#include <gtest/gtest.h>
#include "bst.h"

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        // debug section
    BST bst{17, 12, 35, 29, 18, 38, 36, 37, 40};
    std::cout << bst;
    std::cout << bst.delete_node(38) << std::endl;
    std::cout << bst; 
    std::cout << bst.delete_node(17) << std::endl;
    std::cout << bst; 
    // BST bst1{5, 1, 10, 2, 8, 50, 4, 60};
    // BST bst2{3, 2, 100, 20, 8, 50, 4, 60, 44, 23};
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