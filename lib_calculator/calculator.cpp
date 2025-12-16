#include "Calculator.h"
#include <iostream>
#include <sstream>
#include <limits>
#include <cctype>

using namespace std;

void Calculator::showAll() const {
    cout << "+---------------------------------------------------+\n";
    cout << "| ID  | EXPRESSION               | VARIABLES        |\n";
    cout << "+---------------------------------------------------+\n";

    for (int i = 0; i < exprs.size(); i++) {
        const Expression& e = exprs[i];
        cout << "| " << e.getId() << " ";

        string expr = e.getExpression();
        if (expr.length() > 25) expr = expr.substr(0, 22) + "...";
        cout.width(27);
        cout << left << ("| " + expr) << "| ";

        const auto& vars = e.getVariables();
        if (vars.empty()) cout << "none";
        else {
            bool first = true;
            for (const auto& v : vars) {
                if (!first) cout << ", ";
                cout << v.first << "=" << v.second;
                first = false;
            }
        }
        cout << " |\n";
    }
    cout << "+---------------------------------------------------+\n";
}

void Calculator::createExpr() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter expression: ";
    string expr;
    getline(cin, expr);

    if (expr.empty()) {
        cout << "Empty!\n";
        return;
    }

    try {
        Expression e(nextId++, expr);
        exprs.push(e);
        cout << "Created with ID " << (nextId - 1) << "\n";
    }
    catch (const exception& ex) {
        cout << "Error: " << ex.what() << "\n";
    }
}

void Calculator::deleteExpr() {
    cout << "Enter ID to delete: ";
    int id;
    cin >> id;

    if (!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Bad input\n";
        return;
    }

    int idx = -1;
    for (int i = 0; i < exprs.size(); i++) {
        if (exprs[i].getId() == id) { idx = i; break; }
    }

    if (idx == -1) {
        cout << "Not found\n";
        return;
    }

    for (int i = idx; i < exprs.size() - 1; i++) {
        exprs[i] = exprs[i + 1];
    }
    exprs.pop();
    cout << "Deleted\n";
}

void Calculator::setVars() {
    cout << "Enter expression ID: ";
    int id;
    cin >> id;

    if (!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Bad input\n";
        return;
    }

    int idx = -1;
    for (int i = 0; i < exprs.size(); i++) {
        if (exprs[i].getId() == id) { idx = i; break; }
    }

    if (idx == -1) {
        cout << "Not found\n";
        return;
    }

    Expression& e = exprs[idx];
    e.clearVariables();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter name=value (empty line to stop):\n";

    while (true) {
        cout << "> ";
        string line;
        getline(cin, line);
        if (line.empty()) break;

        size_t eq = line.find('=');
        if (eq == string::npos) {
            cout << "Format: name=value\n";
            continue;
        }

        string name = line.substr(0, eq);
        string valStr = line.substr(eq + 1);

        bool ok = !name.empty() && (isalpha(name[0]) || name[0] == '_');
        for (char c : name) {
            if (!isalnum(c) && c != '_') { ok = false; break; }
        }

        if (!ok) {
            cout << "Bad var name\n";
            continue;
        }

        try {
            double val = stod(valStr);
            e.setVariable(name, val);
            cout << "Set " << name << " = " << val << "\n";
        }
        catch (...) {
            cout << "Bad number\n";
        }
    }
}

void Calculator::evalExpr() {
    cout << "Enter expression ID: ";
    int id;
    cin >> id;

    if (!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Bad input\n";
        return;
    }

    int idx = -1;
    for (int i = 0; i < exprs.size(); i++) {
        if (exprs[i].getId() == id) { idx = i; break; }
    }

    if (idx == -1) {
        cout << "Not found\n";
        return;
    }

    try {
        double res = exprs[idx].evaluate();
        cout << "Result: " << res << "\n";
    }
    catch (const exception& ex) {
        cout << "Error: " << ex.what() << "\n";
    }
}

void Calculator::run() {
    while (true) {
        cout << "\n1. Create\n2. Delete\n3. Set vars\n4. Evaluate\n5. Show all\n0. Exit\nChoice: ";
        int choice;
        cin >> choice;

        if (!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Bad input\n";
            continue;
        }

        switch (choice) {
        case 0: return;
        case 1: createExpr(); break;
        case 2: deleteExpr(); break;
        case 3: setVars(); break;
        case 4: evalExpr(); break;
        case 5: showAll(); break;
        default: cout << "Bad choice\n";
        }
    }
}