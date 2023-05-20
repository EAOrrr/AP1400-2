#ifndef Q1_H
#define Q1_H
#include<functional>

namespace q1{

    template<typename inputValue, typename Function>
    inline inputValue gradient_descent(inputValue start, inputValue step, Function func = Function{}){
        inputValue parameter = start, oldParameter = parameter+step;
        while(parameter != oldParameter){
            oldParameter = parameter;
            inputValue derivative = (func(parameter+step) - func(parameter)) / step; 
            parameter = parameter - derivative * step;
            // std::cout << derivative << std::endl;
        }
        std::cout << parameter << std::endl;
        return parameter;
    }
}

#endif //Q1_H