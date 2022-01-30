#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <unordered_map>

int opPrio(char a)
{
    switch(a) {
        case '|' : return 0;
        case '^' : return 1;
        case '&' : return 2;
        default : return -1;
    }
}

bool isOp(char a)
{
    return a == '&' || a == '^' || a == '|';
}

bool eval2(char num1, char num2, char op)
{
    switch(op) {
        case '|' : return (num1 - 48) | (num2 - 48);
        case '^' : return (num1 - 48) ^ (num2 - 48);
        case '&' : return (num1 - 48) & (num2 - 48);
        default : return 0;
    }
}

//unfortunately not needed for this task, but will be used in the future
// beautiful function for bool evaluation with parentheses and everything
bool boolEval(const char *express, int &pos)
{
    std::stack<char> operations, numbers;
    int i = pos;

    while (express[++i] != 0) { //going through string and evaluating what's possible
        if (isOp(express[i])) {
            if (operations.empty()) operations.push(express[i]);
            else {
                 if (opPrio(express[i]) <= opPrio(operations.top())) {
                     char num1 = numbers.top(); 
                     numbers.pop();
                     char num2 = numbers.top();
                     numbers.pop();
                     char op = operations.top();
                     operations.pop(); // do the op
                     operations.push(express[i]); // put the current lower prio op
                     numbers.push(eval2(num1,num2,op) + 48);
                 }
                 else operations.push(express[i]);
            }
            continue;
        }
        if (isdigit(express[i])) {
            numbers.push(express[i]);
            continue;
        }
        if (express[i] == '(') {
            pos = i;
            numbers.push(boolEval(express, pos) + 48);
            i = pos;
            continue;
        }
        if (express[i] == ')') {
            while (!operations.empty()) {
                char num1 = numbers.top(); 
                numbers.pop();
                char num2 = numbers.top();
                numbers.pop();
                char op = operations.top();
                operations.pop();
                numbers.push(eval2(num1, num2, op) + 48);
            }
            pos = i;
            return numbers.top() - 48;
        }
    }

    while (!operations.empty()) { // finishing operations that are left on stack
        char num1 = numbers.top(); 
        numbers.pop();
        char num2 = numbers.top();
        numbers.pop();
        char op = operations.top();
        operations.pop();
        numbers.push(eval2(num1, num2, op) + 48);
    }
    return numbers.top() - 48; // 48 converts into bool here and everywhere before
}


// updates result with new number of true and false
void update(std::vector<int> &v1, std::vector<int> &v2, 
            std::vector<int> &res, char op)
{
    for (int i = 0; i < v1.size(); i++)
        for (int j = 0; j < v2.size(); j++)
            res[eval2(i + 48, j + 48, op)] += v1[i] * v2[j];
}

// vec[0] is for false, and vec[1] for true
std::vector<int> parenExp(std::string &expr, int beg, int end,
        std::unordered_map<std::string, std::vector<int>> &memo)
{
    if (memo.find(expr.substr(beg, end - beg + 1)) != memo.end())
        return memo[expr.substr(beg, end - beg + 1)];
    std::vector<int> res = {0,0};
    if (beg == end) {
        res[expr[beg] - 48]++;
        return res;
    }
    if (end - beg == 2) {
        res[eval2(expr[beg], expr[end], expr[beg+1])]++;
        return res;
    }

    int pos = -1;
    //expression need to be fully parenthesized, so middle results dont count,
    // thats why next line is commented
   /* res[boolEval(expr.substr(beg, end - beg + 1).c_str(), pos)]++; */
    for (int i = beg + 1; i < end; i += 2) {
        auto temp1 = parenExp(expr, beg, i-1, memo);
        auto temp2 = parenExp(expr, i + 1, end, memo);
        update(temp1, temp2, res, expr[i]);
    }
    memo[expr.substr(beg, end - beg + 1)] = res;   
    return res;    
}

int parenExp(std::string &expr, bool val)
{
    std::unordered_map<std::string, std::vector<int>> memo;
    return parenExp(expr, 0, expr.length() - 1, memo)[val]; // number of outcomes with value val
}

int main()
{
    int pos = -1; // needs to be -1 for the start
    std::string expr("0&0&0&1^1|0");
    std::cout << boolEval(expr.c_str(), pos) << std::endl;
    std::cout << parenExp(expr,true) << std::endl;
}

