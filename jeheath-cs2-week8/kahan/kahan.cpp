/**
 * @file kahan.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Functions for the FourierTransform namespace.
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
 */


#include <iostream>
#include <vector>

using namespace std;

#define HUGE	(1e8)
#define TINY	(1./((float) HUGE))


/**
 * @brief Sums the vector `vec`, by adding the elements up one at a
 * time.
 */
float naive_sum(vector<float> vec)
{
	float sum = 0.;

	for (unsigned int i = 0; i < vec.size(); i++)
		sum += vec[i];

	return sum;
}

/**
 * @brief Re-implementation of naive sum that sums over a specified interval
 */
float naive_sum_2(vector<float> vec, unsigned int start, unsigned int end)
{
    float sum = 0;
    for (unsigned int i = start; i < end; i++)
    {
        sum += vec[i];
    }
    return sum;
}
    

/**
 * @brief Sums the elements in the vector vec through the kahan summation
 * method. 
 * 
 * @param vec The vector of floats whose elements are summed. 
 * @returns the sum
 * This was pretty copied verbatum from recitation slides. 
 */
float stable_sum(vector<float> vec)
{
    float sum = 0.0;
    float comp = 0.0;
    for (unsigned int i = 0; i < vec.size(); i++)
    {
        float y = vec[i] - comp;
        float t = sum + y;
        comp = (t - sum) - y;
        sum = t;
    }
    return sum;
}

/**
 * @brief Sums the elements in the vector vec via the pairwise summation
 * method. 
 * 
 * @param vec The vector of floats whose elements are summed. 
 * @returns the sum
 */
float pairwise_sum(vector<float> vec, 
                   unsigned int start, 
                   unsigned int end)
{
    if (end - start <= 100000000.)
    {
        return naive_sum_2(vec, start, end);
    }
    return pairwise_sum(vec, start, (end - start) / 2) 
         + pairwise_sum(vec, (end - start) / 2, end);
}



int main()
{
	// Make a nice vector to sum up.
	vector<float> vec;
	vec.push_back(1.);

	for (int i = 0; i < HUGE; i++)
    {
		vec.push_back(TINY);
    }
	// Try out our summation algorithms!
	cout << "Result of naive summation: " << naive_sum(vec) << endl;
    cout << "Result of stable summation: " << stable_sum(vec) << endl;
    cout << "Result of pairwise summation: " 
         << pairwise_sum(vec, 0, vec.size()) << endl;
}
