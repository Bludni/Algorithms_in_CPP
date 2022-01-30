#include <iostream>
#include <string>
#include <stack>

//arithmetic epression to get evaluated(no parentheses)
int opPrio(char a)
{
    switch(a) {
        case '+' :
        case '-' : return 0;
        case '*' :
        case '/' : return 1;
        default  : return -1;
    }
}

bool isOp(char a)
{
    return a == '+' || a == '-' || a == '*' || a =='/';
}

double eval2(double num1, double num2, char op)
{
    switch(op) {
        case '+' : return num1 + num2;
        case '-' : return num1 - num2;
        case '*' : return num1 * num2;
        case '/' : return num1 / num2;
        default  : return 0;
    }
}

//unfortunately not needed for this task, but will be used in the future
// beautiful function for bool evaluation with parentheses and everything
double arithEval(const char *express, int &pos)
{
    std::stack<char> operations;
    std::stack<double> numbers;
    int i = pos;

    while (express[++i] != 0) { //going through string and evaluating what's possible
        if (isOp(express[i])) {
            if (operations.empty()) operations.push(express[i]);
            else {
                 if (opPrio(express[i]) <= opPrio(operations.top())) {
                     double num2 = numbers.top(); 
                     numbers.pop();
                     double num1 = numbers.top();
                     numbers.pop();
                     char op = operations.top();
                     operations.pop(); // do the op
                     operations.push(express[i]); // put the current lower prio op
                     numbers.push(eval2(num1,num2,op));
                 }
                 else operations.push(express[i]);
            }
            continue;
        }
        if (isdigit(express[i])) { 
            double num;
            sscanf(&express[i], "%lf", &num); //read number
            while (isdigit(express[i+1])) i++; //jump over number
            //i--; //return to last digit so while can increment 
            numbers.push(num);
            continue;
        }
    }

    while (!operations.empty()) { // finishing operations that are left on stack
        double num2 = numbers.top(); 
        numbers.pop();
        double num1 = numbers.top();
        numbers.pop();
        char op = operations.top();
        operations.pop();
        numbers.push(eval2(num1, num2, op));
    }
    return numbers.top(); // 48 converts into bool here and everywhere before
}

int main()
{
    int pos = -1;
    std::cout << arithEval("2*3+5/6*3+15/2", pos) << std::endl;
}