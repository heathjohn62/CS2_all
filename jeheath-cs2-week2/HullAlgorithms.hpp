/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The gift wrapping and Graham scan convex hull algorithms
 * (header file).
 *
 */

#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include "ConvexHullApp.hpp"
#include "structs.hpp"
#include <forward_list>

using namespace std;

void DoGiftWrap(vector<Tuple*> points, ConvexHullApp *app);
void DoGrahamScan(vector<Tuple*> points, ConvexHullApp *app);
void swap_elements(int i, int j, vector<double> &v, 
vector<Tuple*> &points);
void sort(vector<Tuple*> &points, vector<double> &angles,
int left, int right);
unsigned int leftmost(vector<Tuple*> points);
int left_turn(Tuple p_1, Tuple p_2, Tuple p_3);
unsigned int bottom(vector<Tuple*> points);

