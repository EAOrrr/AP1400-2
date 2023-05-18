#include "mocha.h"
Mocha::Mocha(){
    name = "Mocha";
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
    ingredients.push_back(new Chocolate(1));
}

Mocha::~Mocha(){
    for(const auto& i: side_items){
        delete i;
    }
    side_items.clear();
}

Mocha::Mocha(const Mocha& cap):EspressoBased(cap){
    for(const auto& i: cap.side_items){
        side_items.push_back(new Ingredient(*i));
    }

}

void Mocha::operator=(const Mocha& cap){
    if(this == &cap) return;
    EspressoBased::operator=(cap);
    for(const auto& i: side_items){
        delete i;
    }
    side_items.clear();
    for(const auto& i: cap.side_items){
        side_items.push_back(new Ingredient(*i));
    }
}

std::string Mocha::get_name(){
    return name;
}

double Mocha::price(){
    double sumPrice = 0;
    for(const auto& i: ingredients){
        sumPrice += i->price();
    }
    for(const auto& i: side_items){
        sumPrice += i->price();
    }
    return sumPrice;
}

void Mocha::add_side_item(Ingredient* side){
    side_items.push_back(side);
}

std::vector<Ingredient*>& Mocha::get_side_items(){
    return side_items;
}