#include <iostream>
#include <cmath>

#include "target_function.cpp"

using namespace std;

// Defining the mathmatical function
string mathmatical_function = "";

// Trapezoidal rule for numerical integration
double get_integration(int n, float a, float b)
{
  float h = 0;
  double sum = 0, I = 0;

  h = abs((a - b) / n); // Calculate step size

  // Calculate the integral using the trapezoidal rule
  for (int i = 1; i < n; i++)
  {
    sum += target_function(mathmatical_function, a + i * h); // Accumulate function values
  }

  I = (target_function(mathmatical_function, a) + (sum * 2) + target_function(mathmatical_function, b)) * (h / 2); // Final integral estimation

  return I; // Return the estimated integral value
}

// Richardson extrapolation to estimate error percentage
double estimateError(int n, double a, double b)
{
  // Calculating integrals with different step sizes
  double I_h = get_integration(n, a, b);      // Result with step size h
  double I_h2 = get_integration(2 * n, a, b); // Result with step size h/2
  double I_h4 = get_integration(4 * n, a, b); // Result with step size h/4

  // Richardson extrapolation formula to estimate error
  double error = (1.0 / 15.0) * (I_h4 - 16 * I_h2 + 15 * I_h);

  return fabs(error) * 100; // Return absolute value of the error as a percentage
}

int main()
{
  int n = 1, max_n = 99999;
  float a = 0, b = 0;
  double I = 0, estimated_error = 0;

  // Input User's mathmatical function
  cout << "Enter f(x)=";
  cin >> mathmatical_function;

  do
  {
    // Validate the interval input
    if (n <= 0)
      cout << "The interval can't be less than 1." << endl;

    if (n > max_n)
      cout << "You can't exceed " << max_n << "." << endl;

    cout << "Enter the interval: ";
    cin >> n;
  } while (n > max_n || n <= 0);

  // Input lower and upper limits for integration
  cout << "Enter the lower limit: ";
  cin >> a;

  cout << "Enter the upper limit: ";
  cin >> b;

  // Calculate integral and estimated error
  I = get_integration(n, a, b);
  estimated_error = estimateError(n, a, b);

  // Display results
  cout << "Integral is approximately: " << I << endl;
  cout << "Estimated error percentage: " << estimated_error << "%" << endl;

  system("pause"); // Pause the console before exiting
  return 0;
}
// (1+x^(3))^(1/3)