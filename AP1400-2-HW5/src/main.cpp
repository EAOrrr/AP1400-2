#include <iostream>
#include <gtest/gtest.h>
#include "ingredient.h"
#include "sub_ingredients.h"
#include "espresso_based.h"
#include "cappuccino.h"
#include "mocha.h"

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        // debug section
        Cappuccino cappuccino;
        cappuccino.add_side_item(new Chocolate{2});
        Cappuccino copy{cappuccino};
        std::cout << copy.get_name() << std::endl;
        std::vector<Ingredient*> ingredient = cappuccino.get_ingredients();
        for(const auto& i: ingredient){
            std::cout << i->get_name() << ' ' << i->get_price_unit( ) <<' '<<  i->get_units() << std::endl;
        }
        Water *w = new Water(3);
        Ingredient* i = new Ingredient(*w);
        std::cout << i->get_name() << ' ' << i->get_price_unit( ) <<' '<<  i->get_units() << std::endl;
        delete w;   delete i;
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