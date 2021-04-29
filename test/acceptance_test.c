//
// Created by dawids21 on 4/29/21.
//

#include <unity.h>

void setUp() {

}

void tearDown() {

}

void standard_acceptance_test(void) {
    TEST_FAIL_MESSAGE("Standard acceptance test not implemented yet");

    // when I add 2 bread, 3 cheese, 1000 ml of water
    // then on the list of ingredients I see 2 bread, 3 cheese, 1000 ml of water

    // when I change the amount of cheese to 2
    // then on the list of ingredients I see 2 bread and 2 cheese, 1000 ml of water.

    // when I add recipe for standard breakfast and premium breakfast
    // then on the list of recipes I see the recipes for standard breakfast and premium breakfast

    // when I open recommendations for meal
    // then I can see the recipe for standard breakfast

    // when I click the option to prepare standard breakfast
    // then I can see the recipe

    // when I click the meal is ready and ask for the list of ingredients
    // then on the list of ingredients I see 1 bread and 1 cheese, 750 ml of water.
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(standard_acceptance_test);

    return UNITY_END();
}
