//
// Created by dawids21 on 4/29/21.
//

#include <unity.h>
#include <array.h>

void setUp() {

}

void tearDown() {

}

void test_when_added_two_items_return_two_items() {
    Array array = new_array(INT);

    append(array, (ArrayItem) 5);
    append(array, (ArrayItem) 8);
    ArrayItem *items = get_all_items(array);

    TEST_ASSERT_EQUAL(5, items[0].int_item);
    TEST_ASSERT_EQUAL(8, items[1].int_item);

    delete_array(array);

    TEST_FAIL();
}


void test_when_added_three_items_return_size_of_three() {

}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_when_added_two_items_return_two_items);
    RUN_TEST(test_when_added_three_items_return_size_of_three);

    return UNITY_END();
}
