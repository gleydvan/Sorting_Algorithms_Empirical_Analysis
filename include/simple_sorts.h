#ifndef SIMPLE_SORTS_H
#define SIMPLE_SORTS_H

#include <vector>
#include <iterator>

//	Definindo um um tipo para o vector
typedef std::vector<unsigned int> u_vector;

//	Definindo um tipo para o iterator
typedef std::vector<unsigned int>::iterator u_iterator;

void insertion_sort ( u_iterator first, u_iterator last);

void selection_sort ( u_iterator first, u_iterator last);

#endif
