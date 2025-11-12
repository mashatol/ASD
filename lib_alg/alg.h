#include "stack.h"
#include <string>

bool check_brackets(const std::string& str) {
    Stack<char> brackets;

    for (char c : str) {
        if (c == '(' || c == '[' || c == '{') {
            brackets.push(c);
        }
        else if (c == ')') {
            if (brackets.is_empty() || brackets.top() != '(') {
                return false;
            }
            brackets.pop();
        }
        else if (c == ']') {
            if (brackets.is_empty() || brackets.top() != '[') {
                return false;
            }
            brackets.pop();
        }
        else if (c == '}') {
            if (brackets.is_empty() || brackets.top() != '{') {
                return false;
            }
            brackets.pop();
        }
    }

    return brackets.is_empty();
}