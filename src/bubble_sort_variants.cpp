/**
* @file bubble_sort_variants.cpp
* @brief Arquivo com as implementações de algumas funções de ordenação.
* @details Neste arquivo contém especificamente as implementações dos algoritmos de ordenação
*			Bubble sort e Shell sort, são algoritmos de ordenação simples e pouco eficientes,
*			classificados apenas como Bubble sort and variants, devido ao Shell sort poder utilizar 
*			parte da ideia do Bubble, (segundo a en.wikipedia.org). 
*			Ambos recebem como parâmetro dois iteradores,
*			um deles aponta para o começo e o outro para o fim de um vector.
*
* @author	Gleydvan Macedo
* @since	01/10/2017
* @date		16/10/2017
*/

#include <iostream>
#include "bubble_sort_variants.h"

void bubble_sort ( u_iterator first, u_iterator last){
	u_iterator it;
	bool changed;

	//	Laço mais externo verifica se a sequência de elementos ja está ordenada.
	do{
		it = first;
		changed = false;

		//	Laço mais interno percorre toda a sequência de elementos	
		while( it != last-1){

			//	Condição para saber se o elementos da frente é menor que o atual, caso sim então os dois trocam de lugar.
			if (*(it+1) < *it){
				std::swap(*it, *(it+1));
				changed = true;
				
			}

			++it;
		}

		--last;

	} while (changed);

}

void shell_sort (u_iterator first, u_iterator last){
	unsigned int i;
	bool changed = true;
	unsigned int inc_seq = std::distance(first, last);

	//	Laço mais externo para verificar se os elementos foram trocados de lugar ou se o incremento sequencial é maior que 1.
	while (changed or (inc_seq > 1)) {
		changed = false;
		inc_seq = (inc_seq+1)/2;

		//	Laço que percorre o vetor, com base no incremento sequencial.
		for(i = 0; i < (std::distance(first, last) - inc_seq); ++i){

			//	Condição para saber se um elemento é menor que outro e troca-los.
			if(*(first + i + inc_seq) < *(first + i)){
				std::swap(*(first + i), *(first + i + inc_seq));
				changed = true;

			}

		}

	}

}
