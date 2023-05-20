#include <iostream>
#include <gtest/gtest.h>

#include "q1.h"
#include "q2.h"
#include "q3.h"
#include "q4.h"

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {   
    auto flights = q3::gather_flights("/mnt/d/practice/h_programming_basis/AP1400-2/AP1400-2-HW6/resources/flights.txt");

        return 0;
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