/**
* @file analysis_manager.cpp
* @brief Arquivo com as implementações das funções de analises e de medição de tempo.
*
* @author	Gleydvan Macedo
* @since	01/10/2017
* @date		16/10/2017
*/

#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
#include "analysis_manager.h"
#include "fill_manager.h"
#include "bubble_sort_variants.h"
#include "simple_sorts.h"
#include "efficient_sorts.h"
#include "distribution_sort.h"

//	Definição dos ponteiros para funções e atribuição de nomes para os mesmo
using function_type = void ( * ) (u_iterator, u_iterator);
using analysis_type = void ( * ) (u_vector &, u_vector &, std::ofstream &, unsigned int, unsigned int, unsigned int);

/**
* @brief Função que implementa a analise empirica do vetor com elementos em ordem não decrescente.
* @param secundario - Um vector passado por referência, que serve de auxiliar para o vetor principal.
* @param principal - Um vector passado por referência, que contém os elementos a serem ordenados.
* @param quantidade_elementos - Uma variável inteira positiva, que diz a quantidade total de elementos do vector.
* @param quantidade_testes - Uma variável inteira positiva, que diz a quantidade total de testes que serão realizados para medir o tempo.
* @param analise - Um apontador para funções, funções essas que possuem uma determinada assinatura.
* @param arquivo - Um apontador para um arquivo de saída, que guardará no arquivo os resultados das analises.
* @param funcoes_escolhidas - Um vector passado por referência, que contêm o número das funções escolhidas pelo usuário para serem analisadas.
*/
void analise_emp_nao_decrescente (u_vector &secundario , u_vector &principal, unsigned int quantidade_elementos, unsigned int quantidade_testes,
									analysis_type analise, std::ofstream &arquivo, u_vector &funcoes_escolhidas){

	//	tipos das funcoes de ordenação
	std::string nomes_func[] = {
		" ",				//0 - preenchimento necessário para que as funções fiquem dos indices de 1 a 7
		"Insertion sort",	//1
		"Selection sort",	//2
		"Bubble sort",		//3
		"Merge sort",		//4
		"Quick sort",		//5
		"Shell sort",		//6
		"Radix sort"		//7
	};

	std::cout << "\nO Vetor sera preenchido de forma nao decrescente, por favor aguarde ..." << std::endl;
	preencher_nao_decrescente(principal);

	//	Atribui ao vector secundário o vetor principal para poder usar a mesma configuração em outros lugares.
	std::cout << "Vetor preenchido de forma não decrescente, por favor aguarde enquanto esta organização é salva..." << std::endl;
	secundario = principal;

	std::cout << "Vetor salvo, iniciando análises para valores não decrescentes...\n" << std::endl;

	//	Analise para 26 amostras diferentes - taxa de crescimento será linear e dependerá da quantidade de elementos
	unsigned int range = quantidade_elementos/26;

	//	Laço para mudar a quantidade de amostras
	for (unsigned int i = range; i <= quantidade_elementos; i += range ){

		std::cout << ">>>		Analisando para " << i << " elementos		<<<" << std::endl;
		arquivo << i;


		u_iterator it_func_escolhidas = funcoes_escolhidas.begin();

		//	Laço para mudar o tipo do algoritmo de ordenação.
		while(it_func_escolhidas != funcoes_escolhidas.end()){
			unsigned int f = *it_func_escolhidas;

			std::cout << ">>> Analisando a Função " << f << " " << nomes_func[f] << std::endl;

			//	Chamada da função que tratará a execução de cada análise
			analise(secundario, principal, arquivo, i, quantidade_testes, f);

			++it_func_escolhidas;
		}

		arquivo << std::endl;

	}

	arquivo.close();

}

/**
* @brief Função que implementa a analise empirica do vetor com elementos em ordem não crescente.
* @param secundario - Um vector passado por referência, que serve de auxiliar para o vetor principal.
* @param principal - Um vector passado por referência, que contém os elementos a serem ordenados.
* @param quantidade_elementos - Uma variável inteira positiva, que diz a quantidade total de elementos do vector.
* @param quantidade_testes - Uma variável inteira positiva, que diz a quantidade total de testes que serão realizados para medir o tempo.
* @param analise - Um apontador para funções, funções essas que possuem uma determinada assinatura.
* @param arquivo - Um apontador para um arquivo de saída, que guardará no arquivo os resultados das analises.
* @param funcoes_escolhidas - Um vector passado por referência, que contêm o número das funções escolhidas pelo usuário para serem analisadas.
*/
void analise_emp_nao_crescente (u_vector &secundario , u_vector &principal, unsigned int quantidade_elementos, unsigned int quantidade_testes,
									analysis_type analise, std::ofstream &arquivo, u_vector &funcoes_escolhidas){

	//	tipos das funcoes de ordenação
	std::string nomes_func[] = {
		" ",				//0 - preenchimento necessário para que as funções fiquem dos indices de 1 a 7
		"Insertion sort",	//1
		"Selection sort",	//2
		"Bubble sort",		//3
		"Merge sort",		//4
		"Quick sort",		//5
		"Shell sort",		//6
		"Radix sort"		//7
	};

	std::cout << "\nO Vetor será preenchido de forma não crescente, por favor aguarde ..." << std::endl;
	preencher_nao_crescente(principal, quantidade_elementos);

	//	Atribui ao vector secundário o vetor principal para poder usar a mesma configuração em outros lugares.
	std::cout << "Vetor preenchido de forma não crescente, por favor aguarde enquanto esta organização é salva..." << std::endl;
	secundario = principal;

	std::cout << "Vetor salvo, iniciando análises para valores não crescentes...\n" << std::endl;

	//	Analise para 26 amostras diferentes
	unsigned int range = quantidade_elementos/26;

	//	Laço para mudar a quantidade de amostras
	for (unsigned int i = range; i <= quantidade_elementos; i += range ){

		std::cout << ">>> 		Analisando para " << i << " elementos		<<<" << std::endl;
		arquivo << i;

		u_iterator it_func_escolhidas = funcoes_escolhidas.begin();

		//	Laço para mudar o tipo do algoritmo de ordenação.
		while(it_func_escolhidas != funcoes_escolhidas.end()){
			unsigned int f = *it_func_escolhidas;

			std::cout << ">>> Analisando a Função " << nomes_func[f] << std::endl;

			//	Chamada da função que tratará a execução de cada análise
			analise(secundario, principal, arquivo, i, quantidade_testes, f);

			++it_func_escolhidas;
		}


		arquivo << std::endl;

	}

	arquivo.close();

}

/**
* @brief Função que implementa a analise empirica do vetor com elementos em ordem aleatória.
* @param secundario - Um vector passado por referência, que serve de auxiliar para o vetor principal.
* @param principal - Um vector passado por referência, que contém os elementos a serem ordenados.
* @param quantidade_elementos - Uma variável inteira positiva, que diz a quantidade total de elementos do vector.
* @param quantidade_testes - Uma variável inteira positiva, que diz a quantidade total de testes que serão realizados para medir o tempo.
* @param analise - Um apontador para funções, funções essas que possuem uma determinada assinatura.
* @param arquivo - Um apontador para um arquivo de saída, que guardará no arquivo os resultados das analises.
* @param funcoes_escolhidas - Um vector passado por referência, que contêm o número das funções escolhidas pelo usuário para serem analisadas.
*/
void analise_emp_aleatoria (u_vector &secundario , u_vector &principal,	unsigned int quantidade_elementos, unsigned int quantidade_testes,
								analysis_type analise, std::ofstream &arquivo, u_vector &funcoes_escolhidas){

	//	tipos das funcoes de ordenação
	std::string nomes_func[] = {
		" ",				//0 - preenchimento necessário para que as funções fiquem dos indices de 1 a 7
		"Insertion sort",	//1
		"Selection sort",	//2
		"Bubble sort",		//3
		"Merge sort",		//4
		"Quick sort",		//5
		"Shell sort",		//6
		"Radix sort"		//7
	};

	std::cout << "\nO Vetor será preenchido aleatoriamente, por favor aguarde ..." << std::endl;
	preencher_aleatorio(principal, quantidade_elementos);

	//	Atribui ao vector secundário o vetor principal para poder usar a mesma configuração em outros lugares.
	std::cout << "Vetor preenchido aleatoriamente, por favor aguarde enquanto esta organização é salva..." << std::endl;
	secundario = principal;

	std::cout << "Vetor salvo, iniciando análises para valores aleatórios...\n" << std::endl;
	
	//	Analise para 26 amostras diferentes	
	unsigned int range = quantidade_elementos/26;

	//	Laço para mudar a quantidade de amostras
	for (unsigned int i = range; i <= quantidade_elementos; i += range ){

		std::cout << ">>>		Analisando para " << i << " elementos		<<<" << std::endl;
		arquivo << i;
		
		u_iterator it_func_escolhidas = funcoes_escolhidas.begin();

		//	Laço para mudar o tipo do algoritmo de ordenação.
		while(it_func_escolhidas != funcoes_escolhidas.end()){
			unsigned int f = *it_func_escolhidas;

			std::cout << ">>> Analisando a Função " << nomes_func[f] << std::endl;

			//	Chamada da função que tratará a execução de cada análise
			analise(secundario, principal, arquivo, i, quantidade_testes, f);

			++it_func_escolhidas;
		}


		arquivo << std::endl;

	}

	arquivo.close();

}

/**
* @brief Função que implementa a medição do tempo das analises empirica.
* @param first - Um iterador, que aponta para o começo do vetor que será realizada a análise.
* @param last - Um iterador, que aponta para o final do vetor que será realizada a análise.
* @param nome_funcao_ord - Um apontador para funções, funções essas que possuem uma determinada assinatura, nesse caso as funções de ordenação.
* @return Retorna um número do tipo double, que corresponde ao tempo gasto para a ordenação do vetor.
*/
double medicao_tempo (u_iterator first, u_iterator last, function_type nome_funcao_ord){
	auto start = std::chrono::steady_clock::now();

	//	Chamada dos algoritmos de ordenação.
	nome_funcao_ord( first, last);

	auto end = std::chrono::steady_clock::now();

	auto diff = end - start;

	return std::chrono::duration <double, std::milli> (diff).count();
}


/**
* @brief Função responsável por gerênciar a execução das analises.
* @param secundario - Um vector passado por referência, que serve de auxiliar para o vetor principal.
* @param principal - Um vector passado por referência, que contém os elementos a serem ordenados.
* @param arquivo - Um apontador para um arquivo de saída, que guardará no arquivo os resultados das analises.
* @param numero_elementos - Uma variável inteira positiva, que diz a quantidade total de elementos do vector.
* @param numero_testes - Uma variável inteira positiva, que diz a quantidade total de testes que serão realizados para medir o tempo.
* @param numero_func - Uma variável inteira positiva, que diz o número da função a ser instânciada para a ordenação do vetor.
*/
void executar_analises (u_vector &secundario , u_vector &principal, std::ofstream &arquivo, unsigned int numero_elementos, unsigned int numero_testes, unsigned int numero_func){
		
	function_type tipo_funcao[] = {
		insertion_sort,		//0 - preenchimento necessário para que as funções fiquem dos indices de 1 a 7
		insertion_sort,		//1
		selection_sort,		//2
		bubble_sort,		//3
		merge_sort,			//4
		quick_sort,			//5
		shell_sort,			//6
		radix_sort			//7
	};

	double media_progressiva = 0;

	//	Laço que roda as analises a quantidade de vezes passadas pelo usuário para tirar a média do tempo, para cada algoritmo passado pelo usuário.
	for (unsigned int j = 1; j <= numero_testes; ++j){
		media_progressiva = media_progressiva + ((medicao_tempo(secundario.begin(), secundario.begin() + numero_elementos, (tipo_funcao[numero_func])) - media_progressiva) / j);
		secundario = principal;

	}

	arquivo << "," << std::fixed << std::setprecision(9) << media_progressiva;
}