//
// Created by Jason Watson on 21/01/2016.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdio.h>

/*
 * This document will act as a guide for programming with C++ and root in OxTools.
 * It will cover a few techniques beginners will be unaware of, and show examples of how
 * to use the Class structure of OxTools.
 */

// Vectors, Sets, and Maps
/*
 * These are very useful containers in C++, and should almost always be used instead of arrays. You
 * should read up about them on the internet. But a basic description:
 * - Vectors
 *     Essentially an array with a variable size
 * - Sets
 *     Similar to a vector, but each entry is unique and sorted.
 *     e.g. vector=[2,1,6,3,4,2,1,1]
 *          set=[1,2,3,5,6]
 * - Map
 *     Where vectors are indexed by an integer (vector[i]), maps can be indexed by any type.
 *     e.g. map["Jason"]=23.5
 */


// Looping through maps (iterators)
/*
 * Normally to loop through an array (or a vector), you would use an integer that you increment.
 * Instead, with maps (or also possible with vectors) you use an iterator.
 * http://www.cprogramming.com/c++11/c++11-ranged-for-loop.html
 */
void a() {
	std::vector<int> vec = {2, 3, 5, 6};
	for (int i : vec) {
		std::cout << i << std::endl;
	}
}
/*
 * The output of this script is:
 * 2
 * 3
 * 5
 * 6
 * You can see how essentially i becomes the value in the vector that is iterated to.
 * NOTE: this loop is C++11, there exists a more complicated form of iterating using an iterator
 * type.
 * When iterating through maps it is important to remember the iterator is a pair.
 */
void b() {
	std::map<std::string, int> map1;
	map1["Jason"] = 23;
	map1["PHD"] = 3;
	for (auto i : map1) {
		auto key = i.first;
		auto value = i.second;
		std::cout << key << " , " << value << std::endl;
	}
}
/*
 * The output of this script is:
 * Jason , 23
 * PHD , 3
 * The auto type is a useful C++11 feature, the actual type of i is
 *
 * std::__map_iterator<std::__1::__tree_iterator<std::__1::__value_type<std::__1::basic_string<char,
 * std::__1::char_traits<char>, std::__1::allocator<char>>, int>, std::__1::__tree_node<std::__1::__
 * value_type<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>,
 * int>, void *> *, long>>::value_type
 *
 * so it is very useful not having to know, or even write that. key and value are correctly set to
 * types string and int respectively.
 */


// Public/Private
/*
 * http://www.learncpp.com/cpp-tutorial/83-public-vs-private-access-specifiers/
 */


// Macros
/*
 * Macros are useful when there is a bit of code that are identical in format, but are concerned
 * with different variables. This is especially useful for Class attribute getters, which are
 * mainly used to only return a private member variable. Take a look at the macros defined in
 * macros.h and how they are used in Run.h.
 * For example 	 GET(RunId, mRunId, uint32_t);    - This simply creates the function GetRunId
 * which returns the member variable mRunId (which is of type uint32_t).
 */

/* A simple camera image plotter can be found in camera_image_plotter.cpp
 * called basic_camera_image_plotter */
