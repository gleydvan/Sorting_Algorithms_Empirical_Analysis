/**
* @file distribution_sort.cpp
* @brief Arquivo implementação de algoritmo de ordenação.
* @details Neste arquivo contém especificamente a implementação do algoritmo de ordenação
*			Radix sort, e uma função para pegar o maior valor. O Radix sort é classificado
*			como um algoritmo de ordenação de distribuição,	ou seja, Distribution sort (segundo a en.wikipedia.org).
*			Ambas as funções, radix e get max, recebem como parâmetro dois iteradores
*			onde um deles aponta para o começo e o outro para o fim de um vector.
*
* @author	Gleydvan Macedo
* @since	01/10/2017
* @date		16/10/2017
*/

#include <iostream>
#include "distribution_sort.h"

//	Função que retorna o maior valor
unsigned int get_max (u_iterator first, u_iterator last){
	unsigned int max = *first;

	for (u_iterator it = first; it != last; ++it)
	{
		if (*it > max)
		{
			max = *it;
		}
	}
	return max;
}

void radix_sort (u_iterator first, u_iterator last)
{
	unsigned int max = get_max(first, last);
	unsigned int size = std::distance(first, last);
	unsigned int *sorted;

	try{

		sorted = new unsigned int [size];

	}

	catch(std::bad_alloc& ba){

		std::cerr << "bad_alloc caught: " << ba.what() << std::endl;
		std::cout << "Ocorreu um erro. Não é possivel continuar. " << std::endl;
		return;

	}

	
	for (int exp = 1; max/exp > 0; exp *= 10) // radix = 10
	{	
		unsigned int count[10] = {0};
	 
		for (u_iterator it = first; it != last; ++it)
		{
			count[ (*it/exp)%10 ]++;
		}
		for (int i = 1; i < 10; i++)
		{
			count[i] += count[i - 1];
		}
		for (u_iterator it = last-1; it != first-1; --it)
		{
			sorted[count[ (*it/exp)%10 ] - 1] = *it;
			count[ (*it/exp)%10 ]--;
		}

		std::copy(sorted, sorted+(size), first);
	}
	
	delete[] sorted;
}