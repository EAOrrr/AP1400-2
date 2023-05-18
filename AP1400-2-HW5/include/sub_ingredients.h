#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H
#include"ingredient.h"

#define DEFCLASS(ingredientName, ingredientPrice)   \
    class ingredientName:public Ingredient{                         \
        public:                                     \
            ingredientName(size_t units): Ingredient((ingredientPrice), units){\
                this->name = #ingredientName;    \
            }                                       \
    };                                              

class Cinnamon: public Ingredient{
    public:
        Cinnamon(size_t units): Ingredient(5, units){
            this->name = "Cinnamon";
        }
};

DEFCLASS(Chocolate, 5);
DEFCLASS(Sugar, 1);
DEFCLASS(Cookie, 10);
DEFCLASS(Espresso, 15);
DEFCLASS(Milk, 10);
DEFCLASS(MilkFoam, 5);
DEFCLASS(Water, 1);

#endif // SUB_INGREDIENTS_H