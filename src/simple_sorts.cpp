/**
* @file simple_sorts.cpp
* @brief Arquivo com as implementações de algumas funções de ordenação.
* @details Neste arquivo contém especificamente as implementações dos algoritmos de ordenação
*			Insertion sort e Selection sort, classificados como algoritmos de ordenação simples,
*			ou seja, Simple sorts (segundo a en.wikipedia.org). Ambos recebem como parâmetro dois iteradores
*			um deles aponta para o começo e o outro para o fim de um vector.
*
* @author	Gleydvan Macedo
* @since	01/10/2017
* @date		16/10/2017
*/

#include <iostream>
#include "simple_sorts.h"

void insertion_sort ( u_iterator first, u_iterator last){
	u_iterator it = first+1;
	u_iterator escolhido;

	//	Percorre a parte não ordenada do vetor e no final de cada iteração diminui a parte não ordenada, aumentando a ordenada.
	while(it != last){
		escolhido = it;

		//	Percorre a parte ordenada do vetor e compara os elementos ordenados com o elemento escolhido da parte não ordenada 
		while(escolhido != first and *escolhido < *(escolhido-1)){
			std::swap(*escolhido, *(escolhido-1));
			--escolhido;
		}

		++it;

	}

}


void selection_sort ( u_iterator first, u_iterator last){
	u_iterator nao_ordenado = first;
	u_iterator menor_elemento;

	//	Percorre todo o vetor e a cada iteração aumenta a parte ordenada e diminui a parte desordenada do vetor.
	while (first != last){
		menor_elemento = nao_ordenado;

		//	Percorre a parte não ordenada do vetor.
		while(nao_ordenado != last){

			//	Compara os elementos da parte não ordenada do vetor e guarda o menor elemento.
			if(*nao_ordenado < *(menor_elemento))
				menor_elemento = nao_ordenado;

			++nao_ordenado;

		}

		//	Coloca o menor elemento da parte não ordenada do vetor no final da parte ordenada.
		std::swap(*first, *menor_elemento);

		++first;	
		nao_ordenado = first;

	}
	
}