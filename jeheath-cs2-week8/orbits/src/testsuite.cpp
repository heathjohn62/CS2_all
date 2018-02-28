/**
 * @file test_solver.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright see License section
 *
 * @brief Simple test suite for Solver.
 *
 * @section License
 * Copyright (c) 2013-2014 California Institute of Technology.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the California Institute of Technology.
 *
 */

#include "Solver.hpp"
#include <cstdio>
#include <iostream> 
#include <cmath>

using namespace Solver;

double f1(double x)
{
    return (x - 3.141592653589) * (x - 1) * (x - 1);
}

double f1p(double x)
{
    return 3 * (2.427728435726 - 3.427728435726 * x + x * x);
}

double f2(double x)
{
    return pow(2., x) - 10;
}

double f2p(double x)
{
    return log(2) * pow(2., x);
}

double f3(double x)
{
    return cos(pow(7., x)); 
}

double f3p(double x)
{
    return -sin(pow(7., x)) * log(7) * pow(7., x); 
}

int main()
{
    // Testing bisection
    std::cout << "Testing Bisection" << std::endl
    << "Function: (x - 3.141592653589) * (x - 1) * (x - 1)" << std::endl 
    << "Expected: 3.141592653589 " << std::endl
    << "Result:   ";
    printf("%.12f", bisection(f1, 2, 4.));
    std::cout << std::endl;
    
    std::cout << "Function: 2^x - 10" << std::endl 
    << "Expected: 3.321928094887 " << std::endl
    << "Result:   ";
    printf("%.12f", bisection(f2, 0, 10.));
    std::cout << std::endl;
    
    std::cout << "Function: cos(7^x)" << std::endl 
    << "Expected: 0.232067603691 " << std::endl
    << "Result:   ";
    printf("%.12f", bisection(f3, 0, .5));
    std::cout << std::endl;
    
    // Testing newton
    std::cout << "Testing Newton Raphson" << std::endl
    << "Function: (x - 3.141592653589) * (x - 1) * (x - 1)" << std::endl 
    << "Expected: 3.141592653589 " << std::endl
    << "Result:   ";
    printf("%.12f", newton_raphson(f1, f1p, 4));
    std::cout << std::endl;
    
    std::cout << "Function: 2^x - 10" << std::endl 
    << "Expected: 3.321928094887 " << std::endl
    << "Result:   ";
    printf("%.12f", newton_raphson(f2, f2p, 5.));
    std::cout << std::endl;
    
    std::cout << "Function: cos(7^x)" << std::endl 
    << "Expected: 0.232067603691 " << std::endl
    << "Result:   ";
    printf("%.12f", newton_raphson(f3, f3p, .4));
    std::cout << std::endl;
    return 0;
}
