//
// Created by dawids21 on 4/28/21.
//

#ifndef CFOOD_INGREDIENT_H
#define CFOOD_INGREDIENT_H

typedef struct Ingredient *Ingredient;
typedef struct IngredientService *IngredientService;

IngredientService newIngredientService();

void deleteIngredientService(IngredientService service);

#endif //CFOOD_INGREDIENT_H
