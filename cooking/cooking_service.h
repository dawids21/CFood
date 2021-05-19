//
// Created by dawids21 on 5/19/21.
//

#ifndef CFOOD_COOKING_SERVICE_H
#define CFOOD_COOKING_SERVICE_H

typedef struct CookingService *CookingService;

void cooking_service_prepare(CookingService service, int recipe_id);

#endif //CFOOD_COOKING_SERVICE_H
