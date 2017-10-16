#ifndef EFFICIENT_SORTS_H
#define EFFICIENT_SORTS_H

#include <vector>
#include <iterator>

//	Definindo um um tipo para o vector
typedef std::vector<unsigned int> u_vector;

//	Definindo um tipo para o iterator
typedef std::vector<unsigned int>::iterator u_iterator;

u_iterator particao(u_iterator first, u_iterator last);

void quick_sort (u_iterator first, u_iterator last);

void merge (u_iterator first, u_iterator last, u_iterator mid);

void merge_sort (u_iterator first, u_iterator last);

#endif