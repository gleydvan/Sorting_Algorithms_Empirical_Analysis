/**
* @file fill_manager.cpp
* @brief Arquivo com as implementações das funções de preenchimento do vetor.
*
* @author	Gleydvan Macedo
* @since	01/10/2017
* @date		16/10/2017
*/

#include <iostream>
#include <algorithm> 
#include <random>		//	std::random_device	std::default_random_engine	std::uniform_int_distribution
#include <functional>	//	std::bind
#include "fill_manager.h"

/**
* @brief Função que serve para preencher o vetor, com elementos inteiros positivos, de forma não decrescente
* @param secundario - Um vector passado por referência, que sera o vector preenchido pela função.
*/
void preencher_nao_decrescente (u_vector &secundario){

	/*	Usando random para dar um pouco de aleatoriedade ao preenchimento,
		nesse caso está servindo só para selecionar aleatoriamente aonde terá elementos repetidos, ou não.	*/
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0,1);

	int numeros = 1;

	for (auto it = secundario.begin(); it != secundario.end(); ++it){

		if( distribution(generator) == 0){
			*it = numeros;
		} else {
			*it = ++numeros;
		}

	}

}

/**
* @brief Função que serve para preencher o vetor, com elementos inteiros positivos, de forma não crescente
* @param secundario - Um vector passado por referência, que sera o vector preenchido pela função.
* @param quantidade_elementos - Um variável inteira positiva, que diz a quantidade total de elementos do vector.
*/
void preencher_nao_crescente (u_vector &secundario, unsigned int quantidade_elementos){

	/*	Usando random para dar um pouco de aleatoriedade ao preenchimento,
		nesse caso está servindo só para selecionar aleatoriamente aonde terá elementos repetidos, ou não.	*/
	std::random_device rnd_device;
	std::default_random_engine generator(rnd_device());
	std::uniform_int_distribution<int> distribution(0,1);

	unsigned int numeros = quantidade_elementos;

	for (auto it = secundario.begin(); it != secundario.end(); ++it){

		if( distribution(generator) == 0){
			*it = numeros;
		} else {
			*it = --numeros;
		}

	}

}


/**
* @brief Função que serve para preencher o vetor, com elementos inteiros positivos, de forma aleatória
* @param secundario - Um vector passado por referência, que sera o vector preenchido pela função.
* @param quantidade_elementos - Um variável que diz a quantidade total que o vector terá de elementos.
*/
void preencher_aleatorio (u_vector &secundario, unsigned int quantidade_elementos){

	/*	Usando random para gerar números aleatórios para o preenchimento do vector	*/
	std::random_device rnd_device;
	std::default_random_engine generator(rnd_device());
	std::uniform_int_distribution<int> distribution(1, quantidade_elementos);

	//	Gerar numeros aleatorios para usos repetidos
	auto gen = std::bind(distribution, generator);

	//	Preenche o vetor do inicio ao fim, com números gerados aleátoriamente, baseado na distribuição
	std::generate(secundario.begin(), secundario.end(), gen);

}