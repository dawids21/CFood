//
// Created by dawids21 on 4/29/21.
//

#include <unity.h>
#include <array.h>
#include <stdbool.h>

static bool not_in_array(ArrayItem item, Array array, int size);

void setUp() {

}

void tearDown() {

}

void when_added_two_items_return_two_items() {
    Array array = new_array();

    append(array, (ArrayItem) 5);
    append(array, (ArrayItem) 8);
    ArrayItem *items = get_all_items(array);

    TEST_ASSERT_EQUAL(5, items[0].int_item);
    TEST_ASSERT_EQUAL(8, items[1].int_item);

    free(items);
    delete_array(&array);
}


void when_added_three_items_return_size_of_three() {
    Array array = new_array();

    append(array, (ArrayItem) 5);
    append(array, (ArrayItem) 8);
    append(array, (ArrayItem) 9);
    int size = get_size(array);

    TEST_ASSERT_EQUAL(3, size);

    delete_array(&array);
}

void when_delete_at_index_the_size_is_reduced_by_one() {
    Array array = new_array();

    append(array, (ArrayItem) 5);
    append(array, (ArrayItem) 8);
    append(array, (ArrayItem) 9);

    delete_at_index(array, 2, NULL);

    TEST_ASSERT_EQUAL(2, get_size(array));

    delete_array(&array);
}

void after_deleting_item_should_not_be_in_data() {
    Array array = new_array();

    append(array, (ArrayItem) 5);
    append(array, (ArrayItem) 8);
    append(array, (ArrayItem) 9);

    delete_at_index(array, 0, NULL);

    TEST_ASSERT_TRUE(not_in_array((ArrayItem) 5, array, get_size(array)));

    delete_array(&array);
}

void returns_false_when_index_for_delete_is_too_big() {
    Array array = new_array();

    append(array, (ArrayItem) 5);

    bool result = delete_at_index(array, 1, NULL);

    TEST_ASSERT_FALSE(result);

    delete_array(&array);
}

void deleting_array_should_return_current_state() {
    Array array = new_array();

    append(array, (ArrayItem) 5);
    append(array, (ArrayItem) 8);

    ArrayItem *items = delete_array(&array);

    TEST_ASSERT_EQUAL(5, items[0].int_item);
    TEST_ASSERT_EQUAL(8, items[1].int_item);
    TEST_ASSERT_NULL(array);

    free(items);
}

void delete_return_deleted_item() {
    Array array = new_array();

    append(array, (ArrayItem) 5);
    append(array, (ArrayItem) 8);

    ArrayItem deleted;
    bool success = delete_at_index(array, 0, &deleted);

    TEST_ASSERT_TRUE(success);
    TEST_ASSERT_EQUAL(5, deleted.int_item);

    delete_array(&array);
}

void return_item_at_given_index() {
    Array array = new_array();

    append(array, (ArrayItem) 5);
    append(array, (ArrayItem) 8);

    ArrayItem item;

    bool success = get(array, 1, &item);

    TEST_ASSERT_TRUE(success);
    TEST_ASSERT_EQUAL(8, item.int_item);

    delete_array(&array);
}

void return_false_when_index_too_big() {
    Array array = new_array();

    append(array, (ArrayItem) 5);

    ArrayItem item;

    bool success = get(array, 1, &item);

    TEST_ASSERT_FALSE(success);

    delete_array(&array);
}

void return_false_when_index_negative() {
    Array array = new_array();

    ArrayItem item;

    bool success = get(array, -1, &item);

    TEST_ASSERT_FALSE(success);

    delete_array(&array);
}

void array_should_scale_automatically() {
    Array array = new_array();

    for (int i = 0; i < 20; ++i) {
        append(array, (ArrayItem) i);
    }

    for (int i = 0; i < 20; ++i) {
        ArrayItem item;
        bool success = get(array, i, &item);

        TEST_ASSERT_TRUE(success);
        TEST_ASSERT_EQUAL(i, item.int_item);
    }

    delete_array(&array);
}


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(when_added_two_items_return_two_items);
    RUN_TEST(when_added_three_items_return_size_of_three);
    RUN_TEST(when_delete_at_index_the_size_is_reduced_by_one);
    RUN_TEST(after_deleting_item_should_not_be_in_data);
    RUN_TEST(returns_false_when_index_for_delete_is_too_big);
    RUN_TEST(deleting_array_should_return_current_state);
    RUN_TEST(delete_return_deleted_item);
    RUN_TEST(return_item_at_given_index);
    RUN_TEST(return_false_when_index_too_big);
    RUN_TEST(return_false_when_index_negative);
    RUN_TEST(array_should_scale_automatically);

    return UNITY_END();
}

static bool not_in_array(ArrayItem item, Array array, int size) {
    ArrayItem *arrayItem = get_all_items(array);

    for (int i = 0; i < size; ++i) {
        if (arrayItem[i].int_item == item.int_item) {
            return false;
        }
    }

    return true;
}