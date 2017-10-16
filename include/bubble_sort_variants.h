#ifndef BUBBLE_SORT_VARIANTS_H
#define BUBBLE_SORT_VARIANTS_H

#include <vector>
#include <iterator>

//	Definindo um tipo para o vector
typedef std::vector<unsigned int> u_vector;

//	Definindo um tipo para o iterator
typedef std::vector<unsigned int>::iterator u_iterator;

void bubble_sort ( u_iterator first, u_iterator last);

void shell_sort (u_iterator first, u_iterator last);

#endif