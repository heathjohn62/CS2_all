/**
 * @file qfsolve.cpp
 * @author John Heath
 *
 * @brief Defines and tests a function that solves for the largest real
 * part of the solution to a given quadratic equation. 
 */

#include <cmath>
#include <iostream>
using namespace std;

double qfsolve(double a, double b, double c)
/**
 * @brief Solves the given quadratic equation.
 *
 * This function, given real coefficients A, B, C to the equation
 * A*x*x + B*x + C = 0, returns the real part of a solution to the
 * equation thus defined. Where two real solutions exist, the one
 * closer to positive infinity is chosen.
 *
 * @param a the quadratic coefficient.
 * @param b the linear coefficient.
 * @param c the constant coefficient.
 *
 * @return the real part of a solution to the defined quadratic equation,
 *         as described.
 */
{
    if (pow(b, 2) - 4 * a * c >= 0) // The solution is entirely real
    {
        return (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
    }
    else // The solution has an imaginary part
    {
        return -b / (2 * a);
    }
    return 0;
}

int main(int argc, char ** argv)
{
    cout << qfsolve(1.0, 2.0, -3.0) << " is 1" << endl; // has solution
    cout << qfsolve(-1.0, -3.0, -10.0) << " is -1.5" << endl; // no solution: 
                                                     // real is: -3/2
    cout << qfsolve(0.0, 0.0, 0.0) << endl; // 0 case is not a qudratic
                                            // and fails. 
    cout << qfsolve(100.0, 3.0, -19.0) << " is ~.421" << endl;
    cout << qfsolve(1, 0, 0) << " is 0" << endl;
    return 0;
}
