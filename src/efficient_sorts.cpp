/**
* @file efficient_sorts.cpp
* @brief Arquivo com as implementações de algumas funções de ordenação.
* @details Neste arquivo contém especificamente as implementações dos algoritmos de ordenação
*			Quick sort, e a função partição, e o Merge sort, e a função merge,
*			classificados como algoritmos de ordenação eficientes, ou seja, Efficient_sorts (segundo a en.wikipedia.org). 
*			Ambos recebem como parâmetro dois iteradores, um deles aponta para o começo e o outro para o fim de um vector,
*			com exceção da função merge, que recebe três iteradores, além dos dois recebidos pelas demais funções,
*			também recebe um que aponta para o meio do vector.
*
* @author	Gleydvan Macedo
* @since	01/10/2017
* @date		16/10/2017
*/

#include <iostream>
#include "efficient_sorts.h"

u_iterator particao(u_iterator first, u_iterator last){
	u_iterator slow = first;
	u_iterator fast = first;
	u_iterator pivot = last-1;

	while(fast != last)
	{
		if (*fast < *pivot)
		{
			std::swap(*slow, *fast);
			++slow;
		}
	++fast;
	}
	std::swap(*slow, *pivot);

	return slow;
}

void quick_sort (u_iterator first, u_iterator last){
	if (first < last)
	{
		u_iterator p = particao(first, last);

		quick_sort(first, p);
		quick_sort(p+1, last);
	}
}

void merge (u_iterator first, u_iterator mid, u_iterator last){
	unsigned int tam_total = std::distance(first, last);
	unsigned int tam_left = std::distance(first, mid );
	unsigned int tam_right = tam_total - tam_left;

	unsigned int* left = new unsigned int[tam_left];
	unsigned int* right = new unsigned int[tam_right];

	std::copy(first, mid, left);
	std::copy(mid, last, right);

	unsigned int i(0); 	// indice do left
	unsigned int j(0); 	// indice do right
	unsigned int k(0); 	// indice do first;

	while(i < tam_left and j < tam_right){
		first[k++] = (left[i] < right[j]) ? left[i++] : right[j++];
	}

	if(i < tam_left)
		std::copy(left+i, left+tam_left, first+k);
	else
		std::copy(right+j, right+tam_right, first+k);

	delete[] left;
	delete[] right;
}

void merge_sort (u_iterator first, u_iterator last){

	unsigned int distance = std::distance(first, last);
	if(!(distance < 2))
	{		
		u_iterator mid = first + distance/2;
		merge_sort(first, mid);
		merge_sort(mid, last);
		merge(first, mid, last);
	}
}