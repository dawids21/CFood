//
// Created by dawids21 on 4/29/21.
//

#include <unity.h>

void setUp() {

}

void tearDown() {

}

void acceptance_test(void) {
    TEST_IGNORE_MESSAGE("Acceptance test not implemented yet");
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(acceptance_test);

    return UNITY_END();
}
