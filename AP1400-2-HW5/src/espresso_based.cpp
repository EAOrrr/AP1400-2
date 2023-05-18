#include "espresso_based.h"

EspressoBased::EspressoBased()=default;

EspressoBased::EspressoBased(const EspressoBased& esp){
    name = esp.name;
    for(const auto& i: esp.ingredients){
        ingredients.push_back(new Ingredient(* i));
    }
}  
void EspressoBased::operator=(const EspressoBased& esp){
    if(this == &esp) return; 
    name = esp.name;
    for(const auto& i: ingredients){
        delete i;
    }
    ingredients.clear();
    for(const auto& i: esp.ingredients){
        ingredients.push_back(new Ingredient(* i));
    }
}

EspressoBased::~EspressoBased(){
    for(const auto& i: ingredients){
        delete i;
    }
    ingredients.clear();
}

std::vector<Ingredient*>& EspressoBased::get_ingredients(){
    return ingredients;
}

void EspressoBased::brew(){

}