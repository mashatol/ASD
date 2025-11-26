#include "Calculator.h"
#include <iostream>
#include <limits>

void Calculator::run() {
    while (true) {
        show_menu();
        int choice = get_choice();

        switch (choice) {
        case 1:
            create_expression();
            break;
        case 2:
            delete_expression();
            break;
        case 3:
            set_variables();
            break;
        case 4:
            evaluate_expression();
            break;
        case 5:
            show_expressions();
            break;
        case 0:
            std::cout << "Выход из программы." << std::endl;
            return;
        default:
            std::cout << "Неверный выбор!" << std::endl;
        }
    }
}

void Calculator::show_menu() {
    std::cout << "\n=== КАЛЬКУЛЯТОР АРИФМЕТИЧЕСКИХ ВЫРАЖЕНИЙ ===" << std::endl;
    std::cout << "1. Создать новое выражение" << std::endl;
    std::cout << "2. Удалить выражение" << std::endl;
    std::cout << "3. Задать переменные" << std::endl;
    std::cout << "4. Вычислить значение выражения" << std::endl;
    std::cout << "5. Показать все выражения" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Ваш выбор: ";
}

int Calculator::get_choice() {
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

void Calculator::add_expression(const Expression& expr) {
    // Создаем новый вектор с увеличенным размером
    TVector<Expression> new_expressions(expressions.size() + 1);

    // Копируем старые выражения
    for (int i = 0; i < expressions.size(); ++i) {
        new_expressions[i] = expressions[i];
    }

    // Добавляем новое выражение
    new_expressions[expressions.size()] = expr;

    // Заменяем старый вектор новым
    expressions = new_expressions;
}

void Calculator::create_expression() {
    std::cout << "Введите выражение: ";
    std::string expr;
    std::getline(std::cin, expr);

    try {
        Expression new_expr(next_id++, expr);

        // Парсим выражение
        List<Lexem> infix = Parser::parse(expr);
        new_expr.set_infix_notation(infix);

        // Преобразуем в обратную польскую запись
        List<Lexem> postfix = Parser::to_postfix(infix);
        new_expr.set_postfix_notation(postfix);

        add_expression(new_expr);
        std::cout << "Выражение создано с ID: " << new_expr.get_id() << std::endl;

    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void Calculator::delete_expression() {
    if (expressions.size() == 0) {
        std::cout << "Нет выражений для удаления." << std::endl;
        return;
    }

    show_expressions();
    std::cout << "Введите ID выражения для удаления: ";
    int id;
    std::cin >> id;

    // Создаем новый вектор без удаляемого выражения
    TVector<Expression> new_expressions(expressions.size() - 1);
    int new_index = 0;
    bool found = false;

    for (int i = 0; i < expressions.size(); ++i) {
        if (expressions[i].get_id() != id) {
            new_expressions[new_index++] = expressions[i];
        }
        else {
            found = true;
        }
    }

    if (found) {
        expressions = new_expressions;
        std::cout << "Выражение удалено." << std::endl;
    }
    else {
        std::cout << "Выражение с ID " << id << " не найдено." << std::endl;
    }
}

void Calculator::set_variables() {
    if (expressions.size() == 0) {
        std::cout << "Нет выражений." << std::endl;
        return;
    }

    show_expressions();
    std::cout << "Введите ID выражения: ";
    int id;
    std::cin >> id;

    Expression* expr = nullptr;
    for (int i = 0; i < expressions.size(); ++i) {
        if (expressions[i].get_id() == id) {
            expr = &expressions[i];
            break;
        }
    }

    if (!expr) {
        std::cout << "Выражение не найдено." << std::endl;
        return;
    }

    expr->clear_variables();

    std::cout << "Введите переменные (формат: имя значение). Для завершения введите 'end':" << std::endl;
    while (true) {
        std::string name;
        double value;

        std::cout << "> ";
        std::cin >> name;

        if (name == "end") break;

        if (std::cin >> value) {
            expr->set_variable(name, value);
            std::cout << "Переменная " << name << " = " << value << " установлена." << std::endl;
        }
        else {
            std::cout << "Ошибка ввода значения!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void Calculator::evaluate_expression() {
    if (expressions.size() == 0) {
        std::cout << "Нет выражений." << std::endl;
        return;
    }

    show_expressions();
    std::cout << "Введите ID выражения: ";
    int id;
    std::cin >> id;

    Expression* expr = nullptr;
    for (int i = 0; i < expressions.size(); ++i) {
        if (expressions[i].get_id() == id) {
            expr = &expressions[i];
            break;
        }
    }

    if (!expr) {
        std::cout << "Выражение не найдено." << std::endl;
        return;
    }

    try {
        double result = Parser::evaluate(expr->get_postfix_notation(), expr->get_variables());
        std::cout << "Результат: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка вычисления: " << e.what() << std::endl;
    }
}

void Calculator::show_expressions() {
    if (expressions.size() == 0) {
        std::cout << "Нет выражений." << std::endl;
        return;
    }

    std::cout << "\n=== ВСЕ ВЫРАЖЕНИЯ ===" << std::endl;
    for (int i = 0; i < expressions.size(); ++i) {
        const Expression& expr = expressions[i];
        std::cout << "ID: " << expr.get_id() << " | Выражение: " << expr.get_expression() << std::endl;

        // Показываем переменные
        const auto& vars = expr.get_variables();
        if (!vars.empty()) {
            std::cout << "  Переменные: ";
            for (const auto& var : vars) {
                std::cout << var.first << "=" << var.second << " ";
            }
            std::cout << std::endl;
        }
    }
}