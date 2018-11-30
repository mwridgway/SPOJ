#include <iostream>
#include <queue>
#include <stack>

using namespace std;

// +, -, *, /, ^
bool isOperator(char token) {
    if (token == 43 ||  // +
        token == 45 ||  // -
        token == 42 ||  // *
        token == 47 ||  // /
        token == 94) {  // ^
        return true;
    }
    return false;
}

// a through z
bool isNumber(char token) {
    if (97 <= token && token <= 122) {
        return true;
    }
    return false;
}

bool isFunction(char token) { return false; }

int getPrecedence(char operatorToken) {
    if (operatorToken == '^') return 4;
    if (operatorToken == '*') return 3;
    if (operatorToken == '/') return 3;
    if (operatorToken == '+') return 2;
    if (operatorToken == '-') return 2;
    return NULL;
}

bool isLeftAssociative(char operatorToken) {
    if (operatorToken == '^') return false;
    if (operatorToken == '*') return true;
    if (operatorToken == '/') return true;
    if (operatorToken == '+') return true;
    if (operatorToken == '-') return true;
    return NULL;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("sample.in", "r", stdin);
#endif
    
    string ss;
    int T;
    cin >> T;
    getline(cin, ss);
    while (T--) {
        string expression;
        getline(cin, expression);
        
        queue<char> output;
        stack<char> operators;
        
        for (int i = 0; i < expression.size(); i++) {
            char token = expression[i];
            if (isNumber(token)) {
                output.push(token);
                continue;
            }
            if (isFunction(token)) {
                operators.push(token);
                continue;
            }
            if (isOperator(token)) {
                while (isFunction(operators.top()) ||
                       (isOperator(operators.top() && (getPrecedence(operators.top()) >
                                                       getPrecedence(token)))) ||
                       ((isOperator(
                                    operators.top() &&
                                    ((getPrecedence(operators.top()) == getPrecedence(token)) &&
                                     isLeftAssociative(operators.top())))) &&
                        (operators.top() != '('))) {
                           output.push(operators.top());
                           operators.pop();
                       }
                operators.push(token);
                continue;
            }
            if (token == '(') {
                operators.push(token);
                continue;
            }
            if (token == ')') {
                while (operators.top() != '(') {
                    output.push(operators.top());
                    operators.pop();
                }
                operators.pop();
                continue;
            }
        }
        
        while (!operators.empty() && isOperator(operators.top())) {
            output.push(operators.top());
            operators.pop();
        }
        
        while (!output.empty()) {
            cout << output.front();
            output.pop();
        }
        cout << endl;
    }
    
    return 0;
}

/* This implementation does not implement composite functions,functions with
 * variable number of arguments, and unary operators. */
/*
 while there are tokens to be read:
 read a token.
 if the token is a number, then:
 push it to the output queue.
 if the token is a function then:
 push it onto the operator stack
 if the token is an operator, then:
 while ((there is a function at the top of the operator stack)
 or (there is an operator at the top of the operator stack with
 greater precedence) or (the operator at the top of the operator stack has equal
 precedence and is left associative)) and (the operator at the top of the
 operator stack is not a left bracket): pop operators from the operator stack
 onto the output queue. push it onto the operator stack. if the token is a left
 bracket (i.e. "("), then: push it onto the operator stack. if the token is a
 right bracket (i.e. ")"), then: while the operator at the top of the operator
 stack is not a left bracket: pop the operator from the operator stack onto the
 output queue. pop the left bracket from the stack.
 // if the stack runs out without finding a left bracket, then there are
 mismatched parentheses. if there are no more tokens to read: while there are
 still operator tokens on the stack:
 // if the operator token on the top of the stack is a bracket, then
 there are mismatched parentheses. pop the operator from the operator stack onto
 the output queue. exit.
 */

/*
 (a+b)                     => ab+
 ((a+b)*(z+x))             => abc*+
 (a+b)*(z+x)               => ab+zx+*
 ((a+t)*((b+(a+c))^(c+d))) => at+bac++cd+^*
 */
