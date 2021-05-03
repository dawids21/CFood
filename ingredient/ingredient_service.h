//
// Created by dawids21 on 5/3/21.
//

#ifndef CFOOD_INGREDIENT_SERVICE_H
#define CFOOD_INGREDIENT_SERVICE_H

typedef struct IngredientService *IngredientService;

IngredientService new_ingredient_service();

void delete_ingredient_service(IngredientService service);

#endif //CFOOD_INGREDIENT_SERVICE_H
