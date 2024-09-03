#include <iostream>
#include <cmath>
#include "helpers.cpp"

using namespace std;

int character_index = 0;

// Function to check if parentheses count matches
bool check_parentheses(string user_function)
{
  int count = 0;

  // Counting opening and closing parentheses
  for (char ch : user_function)
  {
    if (ch == '(')
      count++;
    if (ch == ')')
      count--;
  }

  return count == 0; // Returns true if counts match
}

// Function to check the validity of the user-defined function
bool check_function(string user_function)
{
  bool is_valid = true;

  bool is_x = false;

  bool has_valid_operators = true;
  char invalid_operator = ' ';

  // Check if parentheses count matches
  if (!check_parentheses(user_function))
  {
    cerr << "Error: Opening parentheses count and closing parentheses count don't match.\n";
    is_valid = false;
  }

  for (char ch : user_function)
  {
    // Check if 'x' is present in the function
    if (ch == 'x')
    {
      is_x = true;
      break;
    }

    // Additional checks for valid operators and digits
    if (!is_operator(ch) && !isdigit(ch) && ch != '.' && ch != '(' && ch != ')')
    {
      has_valid_operators = false;
      invalid_operator = ch;
    }
  }

  // Display error messages if conditions fail
  if (!is_x)
  {
    cerr << "Error: Can't find \"x\", make sure you're using small \"x\" not capital \"X\".\n";
    is_valid = false;
  }

  if (!has_valid_operators)
  {
    cerr << "Error: operator \"" << invalid_operator << "\" doesn't have a valid value after.";
    is_valid = false;
  }

  return is_valid; // Return overall validity of the function
}

// Function to evaluate the target function
double target_function(string expression, float x)
{
  bool is_valid = check_function(expression); // Check if the function is valid

  if (!is_valid)
    return NAN; // Return NaN if the function is not valid

  string modified_expression = expression;

  // Modify the expression based on 'x' value and operators
  while (character_index < expression.size())
  {
    char current_character = modified_expression[character_index];
    char next_character = get_next_item(modified_expression, character_index);

    // Replace 'x' with the value of x in the expression
    if (modified_expression[character_index] == 'x')
      modified_expression.replace(character_index, 1, "(" + to_string(x) + ")");

    // Add '*' if a digit is followed by '(' to signify multiplication
    if (current_character == '(' && isdigit(modified_expression[character_index ? character_index - 1 : 0]))
      modified_expression.replace(character_index, 1, "*(");

    // Add '*' if ')' is followed by a digit to signify multiplication
    if (current_character == ')' && isdigit(next_character))
      modified_expression.replace(character_index, 1, ")*");

    character_index++;
  }

  // Reset character_index for the next operation
  character_index = 0;

  return evaluate_expression(modified_expression); // Evaluate the modified expression
}
