#include "cappuccino.h"
Cappuccino::Cappuccino(){
    name = "Cappuccino";
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
}

Cappuccino::~Cappuccino(){
    for(const auto& i: side_items){
        delete i;
    }
    side_items.clear();
}

Cappuccino::Cappuccino(const Cappuccino& cap):EspressoBased(cap){
    for(const auto& i: cap.side_items){
        side_items.push_back(new Ingredient(*i));
    }

}

void Cappuccino::operator=(const Cappuccino& cap){
    if(this == &cap) return 
    EspressoBased::operator=(cap);
    for(const auto& i: side_items){
        delete i;
    }
    side_items.clear();
    for(const auto& i: cap.side_items){
        side_items.push_back(new Ingredient(*i));
    }
}

std::string Cappuccino::get_name(){
    return name;
}

double Cappuccino::price(){
    double sumPrice = 0;
    for(const auto& i: ingredients){
        sumPrice += i->price();
    }
    for(const auto& i: side_items){
        sumPrice += i->price();
    }
    return sumPrice;
}

void Cappuccino::add_side_item(Ingredient* side){
    side_items.push_back(side);
}

std::vector<Ingredient*>& Cappuccino::get_side_items(){
    return side_items;
}