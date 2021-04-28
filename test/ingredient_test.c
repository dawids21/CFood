//
// Created by dawids21 on 4/28/21.
//

#include <ingredient.h>
#include <unity.h>

void setUp() {

}

void tearDown() {

}

void test_example(void) {
    TEST_ASSERT_EQUAL(16, to_test(4));
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_example);

    return UNITY_END();
}