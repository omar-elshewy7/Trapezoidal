#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <cctype>

using namespace std;

// Function to get the next character in the string
char get_next_item(string original_string, int i)
{
  if (i + 1 > original_string.size() - 1)
    return ' ';

  return original_string[i + 1];
}

// Function to check if a character is an operator (+, -, *, /, ^)
bool is_operator(char c)
{
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Function to get the precedence of an operator
int get_precedence(char op)
{
  if (op == '^')
    return 3;
  if (op == '*' || op == '/')
    return 2;
  if (op == '+' || op == '-')
    return 1;
  return 0;
}

// Function to perform arithmetic operations
double apply_operation(double a, double b, char op)
{
  switch (op)
  {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
    return a / b;
  case '^':
    return pow(a, b);
  default:
    return 0;
  }
}

// Function to evaluate the given expression
double evaluate_expression(string expression)
{
  stack<double> values;  // Stack to store operands
  stack<char> operators; // Stack to store operators

  // Loop through the expression
  for (int i = 0; i < expression.length(); ++i)
  {
    char c = expression[i];

    // Ignore whitespaces
    if (isspace(c))
      continue;

    else if (isdigit(c)) // If the character is a digit
    {
      string num_str;

      // Extract the complete number from the expression
      while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.'))
      {
        num_str += expression[i];
        ++i;
      }

      values.push(stod(num_str)); // Push the extracted number onto the stack
      --i;
    }

    else if (c == '(') // If the character is an opening parenthesis
      operators.push(c);

    else if (c == ')') // If the character is a closing parenthesis
    {
      // Perform operations until an opening parenthesis is found
      while (!operators.empty() && operators.top() != '(')
      {
        char op = operators.top();
        operators.pop();

        double val2 = values.top();
        values.pop();

        double val1 = values.top();
        values.pop();

        values.push(apply_operation(val1, val2, op)); // Apply the operation and push result onto the stack
      }

      operators.pop(); // Pop the opening parenthesis
    }

    else if (is_operator(c)) // If the character is an operator
    {
      // Perform operations based on operator precedence
      while (!operators.empty() && get_precedence(c) <= get_precedence(operators.top()))
      {
        char op = operators.top();
        operators.pop();

        double val2 = values.top();
        values.pop();

        double val1 = values.top();
        values.pop();

        values.push(apply_operation(val1, val2, op)); // Apply the operation and push result onto the stack
      }

      operators.push(c); // Push the current operator onto the stack
    }
  }

  // Perform remaining operations
  while (!operators.empty())
  {
    char op = operators.top();
    operators.pop();

    double val2 = values.top();
    values.pop();

    double val1 = values.top();
    values.pop();

    values.push(apply_operation(val1, val2, op)); // Apply the operation and push result onto the stack
  }

  return values.top(); // Return the final result
}
