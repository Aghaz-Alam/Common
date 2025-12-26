/* 
27. Expression Evaluator (Parsing, recursion)

Problem: Write an arithmetic expression evaluator for + - * / and parentheses. Support integer operands and operator precedence.

Requirements / Features:
Implement using recursive descent parser.
Throw exceptions on invalid expression or division by zero.
Provide function int evaluate(const std::string& expr).

Sample Input: "3 + (2 * 5) - 4 / 2" -> Output: 11.
*/


//Grammar Used
Expression → Term ((+ | -) Term)*
Term       → Factor ((* | /) Factor)*
Factor     → Number | '(' Expression ')'
Number     → [0-9]+



//C++ Program
#include <iostream>
#include <stdexcept>
#include <string>
#include <cctype>

class ExpressionParser {
    const std::string& s;
    size_t pos = 0;

public:
    explicit ExpressionParser(const std::string& str) : s(str) {}

    // Entry point
    int parse() {
        int result = parseExpression();
        skipSpaces();
        if (pos != s.length())
            throw std::runtime_error("Unexpected characters at end of expression");
        return result;
    }

private:
    // Utility: skip whitespace
    void skipSpaces() {
        while (pos < s.size() && std::isspace(s[pos])) pos++;
    }

    // Expression → Term ((+ | -) Term)*
    int parseExpression() {
        int value = parseTerm();
        while (true) {
            skipSpaces();
            if (pos < s.size() && (s[pos] == '+' || s[pos] == '-')) {
                char op = s[pos++];
                int rhs = parseTerm();
                if (op == '+') value += rhs;
                else value -= rhs;
            } else break;
        }
        return value;
    }

    // Term → Factor ((* | /) Factor)*
    int parseTerm() {
        int value = parseFactor();
        while (true) {
            skipSpaces();
            if (pos < s.size() && (s[pos] == '*' || s[pos] == '/')) {
                char op = s[pos++];
                int rhs = parseFactor();
                if (op == '*') value *= rhs;
                else {
                    if (rhs == 0) throw std::runtime_error("Division by zero");
                    value /= rhs;
                }
            } else break;
        }
        return value;
    }

    // Factor → Number | '(' Expression ')'
    int parseFactor() {
        skipSpaces();

        if (pos >= s.size())
            throw std::runtime_error("Unexpected end of expression");

        // Parentheses
        if (s[pos] == '(') {
            pos++;
            int value = parseExpression();
            skipSpaces();
            if (pos >= s.size() || s[pos] != ')')
                throw std::runtime_error("Missing closing parenthesis");
            pos++;
            return value;
        }

        // Number
        if (std::isdigit(s[pos])) {
            int value = 0;
            while (pos < s.size() && std::isdigit(s[pos])) {
                value = value * 10 + (s[pos] - '0');
                pos++;
            }
            return value;
        }

        throw std::runtime_error("Unexpected character in expression");
    }
};

// Public API
int evaluate(const std::string& expr) {
    ExpressionParser parser(expr);
    return parser.parse();
}


// ------------------------
// Demonstration
// ------------------------
int main() {
    std::string input = "3 + (2 * 5) - 4 / 2";

    try {
        int result = evaluate(input);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
/* 
✅ Sample Input
3 + (2 * 5) - 4 / 2

✅ Expected Output
Result: 11
*/