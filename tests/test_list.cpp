#include <gtest/gtest.h>
#include "list.h"
#include <vector>
#include <algorithm>

TEST(ListIteratorTest, ReadingWithIterators) {
    List<int> list;

    for (int i = 0; i < 4; i++) {
        list.push_back(i * 3 + 1);
    }

    std::vector<int> result_postfix;
    for (auto it = list.begin(); it != list.end(); it++) {
        result_postfix.push_back(*it);
    }
    EXPECT_EQ(result_postfix, std::vector<int>({ 1, 4, 7, 10 }));

    std::vector<int> result_prefix;
    for (auto it = list.begin(); it != list.end(); ++it) {
        result_prefix.push_back(*it);
    }
    EXPECT_EQ(result_prefix, std::vector<int>({ 1, 4, 7, 10 }));
}


TEST(ListIteratorTest, WritingWithIterators) {
    List<int> list;

    for (int i = 1; i <= 4; i++) {
        list.push_back(i);
    }

    for (auto it = list.begin(); it != list.end(); it++) {
        *it = *it * 2;
    }

    std::vector<int> result;
    for (auto it = list.begin(); it != list.end(); ++it) {
        result.push_back(*it);
    }
    EXPECT_EQ(result, std::vector<int>({ 2, 4, 6, 8 }));


    for (auto it = list.begin(); it != list.end(); ++it) {
        *it = 0;
    }

    std::vector<int> result_zero;
    for (auto it = list.begin(); it != list.end(); it++) {
        result_zero.push_back(*it);
    }
    EXPECT_EQ(result_zero, std::vector<int>({ 0, 0, 0, 0 }));
}


TEST(ListIteratorTest, EmptyListOperations) {
    List<int> list;

 
    EXPECT_EQ(list.begin(), list.end());


    auto it = list.end();
    it++; 
    ++it; 
    EXPECT_EQ(it, list.end());

  
    int counter_postfix = 0;
    for (auto it = list.begin(); it != list.end(); it++) {
        counter_postfix++;
    }
    EXPECT_EQ(counter_postfix, 0);

    int counter_prefix = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        counter_prefix++;
    }
    EXPECT_EQ(counter_prefix, 0);
}

TEST(ListIteratorTest, STLAlgorithmsCompatibility) {
    List<int> list;

    for (int i = 0; i < 10; i++) {
        list.push_back(i * 3 + 1);
    }


    auto it_find = std::find(list.begin(), list.end(), 10);
    EXPECT_NE(it_find, list.end());
    EXPECT_EQ(*it_find, 10);

 
    int count_seven = std::count(list.begin(), list.end(), 7);
    EXPECT_EQ(count_seven, 1);

    int count_nonexistent = std::count(list.begin(), list.end(), 100);
    EXPECT_EQ(count_nonexistent, 0);

 
    std::for_each(list.begin(), list.end(), [](int& n) { n += 1; });


    std::vector<int> result;
    for (auto it = list.begin(); it != list.end(); ++it) {
        result.push_back(*it);
    }
    EXPECT_EQ(result, std::vector<int>({ 2, 5, 8, 11, 14, 17, 20, 23, 26, 29 }));
}

TEST(ListBasicTest, BasicOperations) {
    List<int> list;

  
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.get_size(), 0);


    list.push_back(1);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 1);

    list.push_front(0);
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list.front(), 0);
    EXPECT_EQ(list.back(), 1);


    list.push_back(2);
    EXPECT_EQ(list.get_size(), 3);
    EXPECT_EQ(list.front(), 0);
    EXPECT_EQ(list.back(), 2);
}

TEST(ListBasicTest, ElementRemoval) {
    List<int> list;

 
    for (int i = 0; i < 5; i++) {
        list.push_back(i);
    }


    list.pop_front();
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.get_size(), 4);

 
    list.pop_back();
    EXPECT_EQ(list.back(), 3);
    EXPECT_EQ(list.get_size(), 3);

   
    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.get_size(), 0);
}


TEST(ListBasicTest, CopyAndAssignment) {
    List<int> original;
    for (int i = 0; i < 3; i++) {
        original.push_back(i * 10);
    }

   
    List<int> copy(original);
    EXPECT_EQ(copy.get_size(), original.get_size());

    std::vector<int> original_vec, copy_vec;
    for (auto it = original.begin(); it != original.end(); ++it) {
        original_vec.push_back(*it);
    }
    for (auto it = copy.begin(); it != copy.end(); ++it) {
        copy_vec.push_back(*it);
    }
    EXPECT_EQ(original_vec, copy_vec);

   
    List<int> assigned;
    assigned = original;
    EXPECT_EQ(assigned.get_size(), original.get_size());

    std::vector<int> assigned_vec;
    for (auto it = assigned.begin(); it != assigned.end(); ++it) {
        assigned_vec.push_back(*it);
    }
    EXPECT_EQ(original_vec, assigned_vec);
}

