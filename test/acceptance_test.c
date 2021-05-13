//
// Created by dawids21 on 4/29/21.
//

#include <unity.h>
#include <ingredient_service.h>
#include <recipe_service.h>
#include <recipe.h>
#include <string.h>
#include <recommendation_service.h>

static IngredientService ingredient_service;

static RecipeService recipe_service;

static RecommendationService recommendation_service;

void setUp() {
    ingredient_service = new_ingredient_service("");
    recipe_service = new_recipe_service("", ingredient_service);
    recommendation_service = new_recommendation_service(recipe_service, ingredient_service);
}

void tearDown() {
    delete_recommendation_service(recommendation_service);
    delete_recipe_service(recipe_service);
    delete_ingredient_service(ingredient_service);
}

static void add_recipe_for_standard_breakfast(RecipeService service);

static void add_recipe_for_premium_breakfast(RecipeService service);

void standard_acceptance_test(void) {

    // when I add 2 bread, 3 cheese, 1000 ml of water
    add_ingredient(ingredient_service, "Bread", 2, SOLID);
    add_ingredient(ingredient_service, "Cheese", 3, SOLID);
    add_ingredient(ingredient_service, "Water", 1000, LIQUID);
    add_ingredient(ingredient_service, "Tomato", 0, SOLID);
    // then on the list of ingredients I see 2 bread, 3 cheese, 1000 ml of water
    IngredientReadModel ingredients[get_num_of_ingredients(ingredient_service)];
    get_all_ingredients(ingredient_service, ingredients);
    TEST_ASSERT_EQUAL_STRING("Bread", ingredients[0].name);
    TEST_ASSERT_EQUAL(2, ingredients[0].amount);
    TEST_ASSERT_EQUAL(SOLID, ingredients[0].type);
    TEST_ASSERT_EQUAL_STRING("Cheese", ingredients[1].name);
    TEST_ASSERT_EQUAL(3, ingredients[1].amount);
    TEST_ASSERT_EQUAL(SOLID, ingredients[1].type);
    TEST_ASSERT_EQUAL_STRING("Water", ingredients[2].name);
    TEST_ASSERT_EQUAL(1000, ingredients[2].amount);
    TEST_ASSERT_EQUAL(LIQUID, ingredients[2].type);
    TEST_ASSERT_EQUAL_STRING("Tomato", ingredients[3].name);
    TEST_ASSERT_EQUAL(0, ingredients[3].amount);
    TEST_ASSERT_EQUAL(SOLID, ingredients[3].type);

    // when I change the amount of cheese to 2
    modify_ingredient(ingredient_service, ingredients[1].id, ingredients[1].name, 2, ingredients[1].type);
    // then on the list of ingredients I see 2 bread and 2 cheese, 1000 ml of water.
    get_all_ingredients(ingredient_service, ingredients);
    TEST_ASSERT_EQUAL_STRING("Bread", ingredients[0].name);
    TEST_ASSERT_EQUAL(2, ingredients[0].amount);
    TEST_ASSERT_EQUAL(SOLID, ingredients[0].type);
    TEST_ASSERT_EQUAL_STRING("Cheese", ingredients[1].name);
    TEST_ASSERT_EQUAL(2, ingredients[1].amount);
    TEST_ASSERT_EQUAL(SOLID, ingredients[1].type);
    TEST_ASSERT_EQUAL_STRING("Water", ingredients[2].name);
    TEST_ASSERT_EQUAL(1000, ingredients[2].amount);
    TEST_ASSERT_EQUAL(LIQUID, ingredients[2].type);
    TEST_ASSERT_EQUAL_STRING("Tomato", ingredients[3].name);
    TEST_ASSERT_EQUAL(0, ingredients[3].amount);
    TEST_ASSERT_EQUAL(SOLID, ingredients[3].type);

    // when I add recipe for standard breakfast and premium breakfast
    add_recipe_for_standard_breakfast(recipe_service);
    add_recipe_for_premium_breakfast(recipe_service);
    // then on the list of recipes I see the recipes for standard breakfast and premium breakfast
    RecipeReadModel recipes[2];
    get_all_recipes(recipe_service, recipes);
    TEST_ASSERT_EQUAL(0, recipes[0].id);
    TEST_ASSERT_EQUAL_STRING("Standard breakfast", recipes[0].name);
    TEST_ASSERT_FALSE(check_if_recipe_is_possible(recipe_service, recipes[0].id));
    TEST_ASSERT_EQUAL(1, recipes[1].id);
    TEST_ASSERT_EQUAL_STRING("Premium breakfast", recipes[1].name);
    TEST_ASSERT_FALSE(check_if_recipe_is_possible(recipe_service, recipes[1].id));

    // when I open recommendations for meal
    int num_of_available_recipes = get_number_of_available_recipes(recommendation_service);
    int recipes_id[num_of_available_recipes];
    get_available_recipes(recommendation_service, recipes_id, num_of_available_recipes);
    TEST_ASSERT_EQUAL(1, num_of_available_recipes);
    TEST_ASSERT_EQUAL(0, recipes_id[0]);
    // then I can see the recipe for standard breakfast

    // when I click the option to prepare standard breakfast
    // then on the list of ingredients I see 1 bread and 1 cheese, 750 ml of water.

    TEST_FAIL_MESSAGE("Standard acceptance test not implemented yet");
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(standard_acceptance_test);

    return UNITY_END();
}

static void add_recipe_for_standard_breakfast(RecipeService service) {
    char *steps[4];
    for (int i = 0; i < 4; ++i) {
        steps[i] = malloc(sizeof(char) * 100);
    }
    strcpy(steps[0], "Take one bread");
    strcpy(steps[1], "Take one cheese");
    strcpy(steps[2], "Put cheese on the bread");
    strcpy(steps[3], "Pour water to the glass");

    RecipeIngredient ingredients[3];
    for (int i = 0; i < 3; ++i) {
        ingredients[i] = malloc(sizeof(struct RecipeIngredient));
    }
    ingredients[0]->id = 0;
    ingredients[0]->amount = 1;
    ingredients[1]->id = 1;
    ingredients[1]->amount = 1;
    ingredients[2]->id = 2;
    ingredients[2]->amount = 250;
    add_recipe(service, "Standard breakfast", steps, 4, ingredients, 3);
    for (int i = 0; i < 3; ++i) {
        free(ingredients[i]);
    }
    for (int i = 0; i < 4; ++i) {
        free(steps[i]);
    }
}

static void add_recipe_for_premium_breakfast(RecipeService service) {
    char *steps[5];
    for (int i = 0; i < 5; ++i) {
        steps[i] = malloc(sizeof(char) * 100);
    }
    strcpy(steps[0], "Take one bread");
    strcpy(steps[1], "Take one cheese");
    strcpy(steps[2], "Take one tomato");
    strcpy(steps[3], "Put cheese and tomato on the bread");
    strcpy(steps[4], "Pour water to the glass");
    RecipeIngredient ingredients[4];
    for (int i = 0; i < 4; ++i) {
        ingredients[i] = malloc(sizeof(struct RecipeIngredient));
    }
    ingredients[0]->id = 0;
    ingredients[0]->amount = 1;
    ingredients[1]->id = 1;
    ingredients[1]->amount = 1;
    ingredients[2]->id = 3;
    ingredients[2]->amount = 1;
    ingredients[3]->id = 2;
    ingredients[3]->amount = 250;
    add_recipe(service, "Premium breakfast", (char **) steps, 5, ingredients, 4);
    for (int i = 0; i < 4; ++i) {
        free(ingredients[i]);
    }
    for (int i = 0; i < 5; ++i) {
        free(steps[i]);
    }
}