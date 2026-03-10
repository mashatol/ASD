#include <gtest/gtest.h>
#include <string>
#include "UnsortedTableOnArr.h"
#include "SortedTableOnArr.h"
#include "UnsortedTableOnList.h"

// Тест 1: Создание пустой таблицы
TEST(UnsortedTableOnArrTest, EmptyTable) {
    UnsortedTableOnArr<std::string, std::string> table;
    EXPECT_TRUE(table.IsEmpty());
    EXPECT_EQ(table.Size(), 0);
}

// Тест 2: Вставка элементов
TEST(UnsortedTableOnArrTest, Insert) {
    UnsortedTableOnArr<std::string, std::string> table;

    EXPECT_TRUE(table.Insert("p1", "x^2+1"));
    EXPECT_TRUE(table.Insert("p2", "x^3-2x"));
    EXPECT_TRUE(table.Insert("p3", "5"));

    EXPECT_FALSE(table.IsEmpty());
    EXPECT_EQ(table.Size(), 3);
}

// Тест 3: Поиск существующего элемента
TEST(UnsortedTableOnArrTest, FindExisting) {
    UnsortedTableOnArr<std::string, std::string> table;
    table.Insert("p1", "x^2+1");
    table.Insert("p2", "x^3-2x");

    std::string value;
    EXPECT_TRUE(table.Find("p2", value));
    EXPECT_EQ(value, "x^3-2x");
}

// Тест 4: Поиск несуществующего элемента
TEST(UnsortedTableOnArrTest, FindNonExisting) {
    UnsortedTableOnArr<std::string, std::string> table;
    table.Insert("p1", "x^2+1");

    std::string value;
    EXPECT_FALSE(table.Find("p4", value));
}

// Тест 5: Обновление существующего элемента
TEST(UnsortedTableOnArrTest, UpdateExisting) {
    UnsortedTableOnArr<std::string, std::string> table;
    table.Insert("p1", "x^2+1");
    table.Insert("p2", "x^3-2x");

    EXPECT_FALSE(table.Insert("p2", "x^4+x^2")); // false = обновление
    EXPECT_EQ(table.Size(), 2);

    std::string value;
    EXPECT_TRUE(table.Find("p2", value));
    EXPECT_EQ(value, "x^4+x^2");
}

// Тест 6: Удаление существующего элемента
TEST(UnsortedTableOnArrTest, DeleteExisting) {
    UnsortedTableOnArr<std::string, std::string> table;
    table.Insert("p1", "x^2+1");
    table.Insert("p2", "x^3-2x");
    table.Insert("p3", "5");

    EXPECT_TRUE(table.Delete("p2"));
    EXPECT_EQ(table.Size(), 2);

    std::string value;
    EXPECT_FALSE(table.Find("p2", value));
}

// Тест 7: Удаление несуществующего элемента
TEST(UnsortedTableOnArrTest, DeleteNonExisting) {
    UnsortedTableOnArr<std::string, std::string> table;
    table.Insert("p1", "x^2+1");

    EXPECT_FALSE(table.Delete("p4"));
    EXPECT_EQ(table.Size(), 1);
}

// Тест 8: Очистка таблицы
TEST(UnsortedTableOnArrTest, Clear) {
    UnsortedTableOnArr<std::string, std::string> table;
    table.Insert("p1", "x^2+1");
    table.Insert("p2", "x^3-2x");

    table.Clear();
    EXPECT_TRUE(table.IsEmpty());
    EXPECT_EQ(table.Size(), 0);
}

// Тест 9: Порядок вставки сохраняется
TEST(UnsortedTableOnArrTest, InsertionOrder) {
    UnsortedTableOnArr<std::string, std::string> table;
    table.Insert("c", "3");
    table.Insert("a", "1");
    table.Insert("b", "2");

    const auto& rows = table.GetRows();
    EXPECT_EQ(rows[0].first, "c");
    EXPECT_EQ(rows[1].first, "a");
    EXPECT_EQ(rows[2].first, "b");
}

//////


// Тест 1: Вставка сохраняет порядок
TEST(SortedTableOnArrTest, InsertMaintainsOrder) {
    SortedTableOnArr<int, std::string> table;
    table.Insert(5, "five");
    table.Insert(2, "two");
    table.Insert(8, "eight");
    table.Insert(1, "one");
    table.Insert(9, "nine");

    EXPECT_EQ(table.Size(), 5);
    const auto& rows = table.GetRows();
    EXPECT_EQ(rows[0].first, 1);
    EXPECT_EQ(rows[1].first, 2);
    EXPECT_EQ(rows[2].first, 5);
    EXPECT_EQ(rows[3].first, 8);
    EXPECT_EQ(rows[4].first, 9);
}

// Тест 2: Поиск элемента
TEST(SortedTableOnArrTest, Find) {
    SortedTableOnArr<int, std::string> table;
    table.Insert(5, "five");
    table.Insert(2, "two");

    std::string value;
    EXPECT_TRUE(table.Find(5, value));
    EXPECT_EQ(value, "five");

    EXPECT_FALSE(table.Find(3, value));
}

// Тест 3: Обновление элемента
TEST(SortedTableOnArrTest, Update) {
    SortedTableOnArr<int, std::string> table;
    table.Insert(5, "five");

    EXPECT_FALSE(table.Insert(5, "FIVE")); // false = обновление
    EXPECT_EQ(table.Size(), 1);

    std::string value;
    EXPECT_TRUE(table.Find(5, value));
    EXPECT_EQ(value, "FIVE");
}

// Тест 4: Удаление элемента
TEST(SortedTableOnArrTest, Delete) {
    SortedTableOnArr<int, std::string> table;
    table.Insert(5, "five");
    table.Insert(2, "two");
    table.Insert(8, "eight");

    EXPECT_TRUE(table.Delete(2));
    EXPECT_EQ(table.Size(), 2);

    std::string value;
    EXPECT_FALSE(table.Find(2, value));
}

// Тест 5: Вставка после удаления
TEST(SortedTableOnArrTest, InsertAfterDelete) {
    SortedTableOnArr<int, std::string> table;
    table.Insert(5, "five");
    table.Insert(8, "eight");
    table.Delete(5);
    table.Insert(3, "three");

    const auto& rows = table.GetRows();
    EXPECT_EQ(rows[0].first, 3);
    EXPECT_EQ(rows[1].first, 8);
}

// Тест 6: Пользовательский компаратор
TEST(SortedTableOnArrTest, CustomComparator) {
    SortedTableOnArr<int, std::string> reverseTable(
        [](const int& a, const int& b) { return a > b; }
    );

    reverseTable.Insert(5, "five");
    reverseTable.Insert(2, "two");
    reverseTable.Insert(8, "eight");

    const auto& rows = reverseTable.GetRows();
    EXPECT_EQ(rows[0].first, 8);
    EXPECT_EQ(rows[1].first, 5);
    EXPECT_EQ(rows[2].first, 2);
}

// Тест 7: Очистка таблицы
TEST(SortedTableOnArrTest, Clear) {
    SortedTableOnArr<int, std::string> table;
    table.Insert(5, "five");
    table.Insert(2, "two");

    table.Clear();
    EXPECT_TRUE(table.IsEmpty());
    EXPECT_EQ(table.Size(), 0);
}

//////

#include <gtest/gtest.h>
#include "UnsortedTableOnList.h"
#include <string>

// Тест 1: Базовая вставка и поиск
TEST(UnsortedTableOnListTest, InsertAndFind) {
    UnsortedTableOnList<int, std::string> table;

    EXPECT_TRUE(table.Insert(1, "one"));
    EXPECT_TRUE(table.Insert(2, "two"));
    EXPECT_TRUE(table.Insert(3, "three"));

    EXPECT_EQ(table.Size(), 3);

    std::string value;
    EXPECT_TRUE(table.Find(2, value));
    EXPECT_EQ(value, "two");

    EXPECT_FALSE(table.Find(4, value));
}

// Тест 2: Обновление существующего ключа
TEST(UnsortedTableOnListTest, UpdateExistingKey) {
    UnsortedTableOnList<int, std::string> table;

    EXPECT_TRUE(table.Insert(1, "one"));
    EXPECT_TRUE(table.Insert(1, "ONE")); // Обновление

    EXPECT_EQ(table.Size(), 1);

    std::string value;
    EXPECT_TRUE(table.Find(1, value));
    EXPECT_EQ(value, "ONE");
}

// Тест 3: Удаление элементов
TEST(UnsortedTableOnListTest, DeleteElements) {
    UnsortedTableOnList<int, std::string> table;

    table.Insert(1, "one");
    table.Insert(2, "two");
    table.Insert(3, "three");

    EXPECT_TRUE(table.Delete(2));
    EXPECT_EQ(table.Size(), 2);

    std::string value;
    EXPECT_FALSE(table.Find(2, value));
    EXPECT_TRUE(table.Find(1, value));
    EXPECT_TRUE(table.Find(3, value));

    EXPECT_TRUE(table.Delete(1));
    EXPECT_EQ(table.Size(), 1);
    EXPECT_FALSE(table.Find(1, value));
    EXPECT_TRUE(table.Find(3, value));

    EXPECT_TRUE(table.Delete(3));
    EXPECT_TRUE(table.IsEmpty());

    // Удаление несуществующего ключа
    EXPECT_FALSE(table.Delete(5));
}

// Тест 4: IsEmpty и Size
TEST(UnsortedTableOnListTest, EmptyAndSize) {
    UnsortedTableOnList<int, std::string> table;

    EXPECT_TRUE(table.IsEmpty());
    EXPECT_EQ(table.Size(), 0);

    table.Insert(1, "one");
    EXPECT_FALSE(table.IsEmpty());
    EXPECT_EQ(table.Size(), 1);

    table.Insert(2, "two");
    EXPECT_EQ(table.Size(), 2);
}

// Тест 5: Clear метод
TEST(UnsortedTableOnListTest, ClearMethod) {
    UnsortedTableOnList<int, std::string> table;

    table.Insert(1, "one");
    table.Insert(2, "two");
    table.Insert(3, "three");

    EXPECT_FALSE(table.IsEmpty());
    EXPECT_EQ(table.Size(), 3);

    table.Clear();

    EXPECT_TRUE(table.IsEmpty());
    EXPECT_EQ(table.Size(), 0);

    std::string value;
    EXPECT_FALSE(table.Find(1, value));
}

// Тест 6: Конструктор копирования
TEST(UnsortedTableOnListTest, CopyConstructor) {
    UnsortedTableOnList<int, std::string> table1;
    table1.Insert(1, "one");
    table1.Insert(2, "two");

    UnsortedTableOnList<int, std::string> table2(table1);

    EXPECT_EQ(table2.Size(), 2);

    std::string value;
    EXPECT_TRUE(table2.Find(1, value));
    EXPECT_EQ(value, "one");
    EXPECT_TRUE(table2.Find(2, value));
    EXPECT_EQ(value, "two");

    // Изменение копии не влияет на оригинал
    table2.Insert(3, "three");
    EXPECT_EQ(table1.Size(), 2);
    EXPECT_EQ(table2.Size(), 3);
}

// Тест 7: Оператор присваивания
TEST(UnsortedTableOnListTest, AssignmentOperator) {
    UnsortedTableOnList<int, std::string> table1;
    table1.Insert(1, "one");
    table1.Insert(2, "two");

    UnsortedTableOnList<int, std::string> table2;
    table2.Insert(3, "three");

    table2 = table1;

    EXPECT_EQ(table2.Size(), 2);

    std::string value;
    EXPECT_TRUE(table2.Find(1, value));
    EXPECT_EQ(value, "one");
    EXPECT_TRUE(table2.Find(2, value));
    EXPECT_EQ(value, "two");
    EXPECT_FALSE(table2.Find(3, value));

    // Самоприсваивание
    table2 = table2;
    EXPECT_EQ(table2.Size(), 2);
}

// Тест 8: Работа с разными типами
TEST(UnsortedTableOnListTest, DifferentTypes) {
    UnsortedTableOnList<std::string, int> table;

    table.Insert("apple", 5);
    table.Insert("banana", 3);
    table.Insert("orange", 8);

    EXPECT_EQ(table.Size(), 3);

    int value;
    EXPECT_TRUE(table.Find("banana", value));
    EXPECT_EQ(value, 3);

    EXPECT_FALSE(table.Find("grape", value));
}

// Тест 9: Пустая таблица
TEST(UnsortedTableOnListTest, EmptyTable) {
    UnsortedTableOnList<int, std::string> table;

    EXPECT_TRUE(table.IsEmpty());
    EXPECT_EQ(table.Size(), 0);

    std::string value;
    EXPECT_FALSE(table.Find(1, value));
    EXPECT_FALSE(table.Delete(1));
}

// Тест 10: Множественные операции
TEST(UnsortedTableOnListTest, MultipleOperations) {
    UnsortedTableOnList<int, int> table;

    // Вставка 100 элементов
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(table.Insert(i, i * i));
    }

    EXPECT_EQ(table.Size(), 100);

    // Проверка всех элементов
    for (int i = 0; i < 100; ++i) {
        int value;
        EXPECT_TRUE(table.Find(i, value));
        EXPECT_EQ(value, i * i);
    }

    // Удаление половины элементов
    for (int i = 0; i < 50; ++i) {
        EXPECT_TRUE(table.Delete(i));
    }

    EXPECT_EQ(table.Size(), 50);

    // Проверка оставшихся
    for (int i = 0; i < 50; ++i) {
        int value;
        EXPECT_FALSE(table.Find(i, value));
    }
    for (int i = 50; i < 100; ++i) {
        int value;
        EXPECT_TRUE(table.Find(i, value));
        EXPECT_EQ(value, i * i);
    }
}