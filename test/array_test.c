//
// Created by dawids21 on 4/29/21.
//

#include <unity.h>
#include <array.h>

void setUp() {

}

void tearDown() {

}

void when_added_two_items_return_two_items() {
    Array array = new_array(INT);

    append(array, (ArrayItem) 5);
    append(array, (ArrayItem) 8);
    ArrayItem *items = get_all_items(array);

    TEST_ASSERT_EQUAL(5, items[0].int_item);
    TEST_ASSERT_EQUAL(8, items[1].int_item);

    free(items);
    delete_array(array);
}


void when_added_three_items_return_size_of_three() {
    Array array = new_array(INT);

    append(array, (ArrayItem) 5);
    append(array, (ArrayItem) 8);
    append(array, (ArrayItem) 9);
    int size = get_size(array);

    TEST_ASSERT_EQUAL(3, size);

    delete_array(array);
}

void when_delete_at_index_the_size_is_reduced_by_one() {
    Array array = new_array(INT);

    append(array, (ArrayItem) 5);
    append(array, (ArrayItem) 8);
    append(array, (ArrayItem) 9);

    delete_at_index(array, 2);

    TEST_ASSERT_EQUAL(2, get_size(array));

    delete_array(array);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(when_added_two_items_return_two_items);
    RUN_TEST(when_added_three_items_return_size_of_three);
    RUN_TEST(when_delete_at_index_the_size_is_reduced_by_one);

    return UNITY_END();
}
