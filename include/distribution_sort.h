#ifndef DISTRIBUTION_SORT_H
#define DISTRIBUTION_SORT_H

#include <vector>
#include <iterator>

//	Definindo um tipo para o vector 
typedef std::vector<unsigned int> u_vector;

//	Definindo um tipo para o iterator
typedef std::vector<unsigned int>::iterator u_iterator;

unsigned int get_max (u_iterator first, u_iterator last);

void radix_sort (u_iterator first, u_iterator last);

#endif