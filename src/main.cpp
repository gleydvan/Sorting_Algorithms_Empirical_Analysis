/**
* @file 	main.cpp
* @brief 	Programa principal para realização de analises empirica de algoritmos de ordenação.
* @author	Gleydvan Macedo
* @since 	01/10/2017
* @date		16/10/2017
* @sa	http://www.google.com/
* @sa	http://www.cplusplus.com/
* @sa	http://www.cplusplus.com/reference/random/
* @sa 	http://www.cplusplus.com/reference/algorithm/generate/?kw=generate
* @sa	https://cadernogeek.wordpress.com/tag/shell-sort/
* @sa	https://en.wikipedia.org/wiki/Sorting_algorithm#Distribution_sort
* @sa	http://www.geeksforgeeks.org/sorting-algorithms/
* @sa 	https://www.gnu.org/software/libc/manual/html_node/Getopt.html#Getopt
*/

#include <ctype.h> 		// isprint
#include <unistd.h> 	
#include <iostream>		
#include <vector>		
#include <stdlib.h>		// strtol
#include <getopt.h>		// getopt
#include <fstream>
#include "analysis_manager.h"
#include "fill_manager.h"
#include "bubble_sort_variants.h"
#include "simple_sorts.h"
#include "efficient_sorts.h"
#include "distribution_sort.h"

//	Macros utilizadas no programa principal
#define MIN_ELEMENTS 26
#define ERRO_ARQUIVO "O arquivo nao pode ser aberto!"

//	Definindo um um tipo para o vector
typedef std::vector<unsigned int> u_vector;

//	Definindo um tipo para o iterator
typedef std::vector<unsigned int>::iterator u_iterator;

//	Definindo ponteiro para funções
using function_type = void ( * ) (u_iterator, u_iterator);


/**
* @brief Função para testar a alocação do vector
* @param tamanho - Uma variável do tipo inteiro positivo, que corresponde ao tamanho da alocação pretendida
* @return Retorna um inteiro positivo, ou 0.
*/
unsigned int teste_alocacao(unsigned int tamanho){
	unsigned int *vetor;
	try{

		vetor = new unsigned int[tamanho];

	}

	catch(std::bad_alloc& ba){

		
		return tamanho;

	}

	delete[] vetor;

	return 0;
	
}

/**
* @brief Função principal.
* @details 	Recebe do usuário, por meio de linha de comando, um inteiro positivo correspondente
*			aos típos de algoritmos de ordenação que serão analisados, um inteiro positivo maior que 26
*			correspondente a quantidade de elementos a serem ordenados e um inteiro positivo correspondente
*			a quantidade de testes que usuário quer que o programa faça para calcular a média do tempo gasto
*			nas analises empirica.
*/
int main(int argc, char *argv[]){
	
	int funcao;
	int aux_funcao = 0;
	u_vector funcoes_escolhidas;
	unsigned int range, quantidade_testes;
	int c;
	char *aux;
	opterr = 0;

	//	Laço que pega a entrada da linha de comando e manipula a mesma
	while((c = getopt (argc, argv, "cf:q:r:")) != -1){

		switch(c){

			//	Caso para a escolha das funções de ordenação a serem analisadas
			case 'f':

				//	Pega a entrada após o -f e guarda numa variavel
				funcao = strtol(optarg,&aux,10);

				//	Laço para manipular as escolhas do usuário
				while (funcao != 0 and funcao != -1){

					//	Condições para separar as escolhas dos alg de ordenação e armazena-las em um vetor
					if(funcao%10 == 8){

						funcoes_escolhidas.erase(funcoes_escolhidas.begin(), funcoes_escolhidas.end());
						aux_funcao = 1;

						for(int temp = 0; temp < 7; ++temp)
							funcoes_escolhidas.push_back(temp+1);

						funcao = -1;

					} else if (funcao%10 < 1 or funcao%10 > 8){

						std::cerr << "Erro: Número de função inválido, por favor indique um número de 1 a 8\n";
						return 1;

					} else {

						funcoes_escolhidas.push_back(funcao%10);
						funcao = funcao/10;

						if(funcao == 0)
							funcao = -1;
					}

				}


			break;

			//	Caso para saber qual a quantidade de testes que o usuário deseja fazer para cada amostra das analises,
			//	para o calculo do tempo medio de cada algoritmo de ordenação.
			case 'q':

				quantidade_testes = strtol(optarg,&aux,10);

				if(quantidade_testes <= 0 or quantidade_testes >= 1073741824){
					std::cerr << "Erro: Entrada invalida, por favor escolha um numero maior que 0 como argumento do -q" << std::endl;
					return 1;
				}

			break;

			//	Caso para saber qual o número máximo de elementos que o usuário quer utilizar nas analises
			case 'r':

				range = strtoul(optarg,&aux,10);

				if ((range < MIN_ELEMENTS and range != 1) or range >= 1073741824){

					std::cerr << "Erro: Entrada invalida, por favor escolha um numero maior que 26 como argumento para o -r "
								<< std::endl << std::endl
								<< "Caso deseje alocar a capacidade maxima de elementos pra seu computador digite 1 como argumento de -r "
								<< std::endl;
					return 1;

				}


			break;

			//	Caso para tratar entradas sem argumentos
			case '?':
				if (optopt == 'f' or optopt == 'r' or optopt == 'q'){

					std::cerr << "Erro: '-" << char(optopt) << "' necessita de um argumento.\n";

					return 1;
				} else if (isprint(optopt)){

					std::cerr << "Erro: '-" << char(optopt) << "' invalido.\n";

					return 1;
				} else {

					std::cerr << "Erro: '\\x" << optopt << "' caractere invalido\n" ;

					return 1;
				}

			default:
				abort();

		}

	}

	//	Se não for digitado nenhuma opção de função então o Modo de usar irá aparecer na tela
	if (funcao == 0){
		std::cout << "\t>>	Modo de usar	<<" << std::endl
				  << "'-f (numero da funcao)' - Indica quais tipos de funcoes de ordenacao deseja utilizar na analise" << std::endl
				  << "'-q (quantidade)' - indica a quantidade de testes realizados para cada amostra em cada Analise Empirica" << std::endl
				  << "'-r (quantidade)' - indica o tamanho do range a ser utilizado (ou seja, a quantidade de elementos)" << std::endl
				  << std::endl
				  << ">>	Números de cada Função 	<<" << std::endl
				  << "1 - Insertion sort" << std::endl
				  << "2 - Selection sort" << std::endl
				  << "3 - Bubble sort" << std::endl
				  << "4 - Merge sort" << std::endl
				  << "5 - Quick sort" << std::endl
				  << "6 - Shell sort" << std::endl
				  << "7 - Radix sort" << std::endl
				  << "8 - All algorithms" << std::endl;

		return 1;
	}

	/*	Caso o usuário não escolha a quantidade de elementos a ser alocada o programa alocará o máximo	*/
	if (range == 1){
		std::cout << "O programa alocara o maximo de elementos possiveis.\n" << std::endl;
		std::cout << "Descobrindo qual a quantidade maxima de elementos que serao alocados. "
					<< "Isso levara algum tempo, por favor espere" << std::endl;
		auto qtd_elemntos = 32768u;	//	2^15

		while(teste_alocacao(qtd_elemntos) == 0){

		qtd_elemntos *= 2;

		}

		range = (qtd_elemntos/4);
		
	}

	std::cout << "Quantidade de elementos que serao alocados no vector:  " << range << std::endl;
	std::cout << "Iniciando alocacao do vetor!" << std::endl;

	//	Aloca na memória o espaço da quantidade de elementos passada pelo usúario ou o máximo de elementos que a memória suportar.
	u_vector v_principal(range);

	//	Cria um vector secundario e aloca na memória o mesmo espaço do vector principal.
	u_vector v_secundario(v_principal);

	//	Variáveis que guardam as configurações das colunas para o csv
	std::string colunas = "tamanho_vetor,Insertion,Selection,Bubble,Merge,Quick,Shell,Radix";
	std::string colunas_vetor[] = {"tamanho_vetor", "Insertion", "Selection", "Bubble", "Merge", "Quick", "Shell", "Radix"};
	std::string virgula = ",";

	std::cout << "Utilizando a seguinte quantidade de testes por função: "
			  <<  quantidade_testes << std::endl;


	/*		Vector organizado com elementos em ordem não decrescente		*/

	//	Criando um arquivo para armazenar as saídas da analise com elementos não decrescentes.
	std::ofstream tempos_vector_nao_decrescentes;
	tempos_vector_nao_decrescentes.open ("tempos/tempos_vector_nao_decrescentes.csv");
	if(tempos_vector_nao_decrescentes.bad()){

		std::cerr << ERRO_ARQUIVO << std::endl;

		std::exit(1);
	}

	/*		Condições para imprimir no arquivo de saída os nomes das colunas com base nos algoritmos escolhidos pelo usuário.		*/
	if(aux_funcao == 1){

		tempos_vector_nao_decrescentes << colunas << std::endl;

	} else {

		colunas = "tamanho_vetor";
		u_iterator it_escolhidas = funcoes_escolhidas.begin();

		while (it_escolhidas != funcoes_escolhidas.end()){

			colunas = colunas + virgula + colunas_vetor[(*it_escolhidas)];
			++it_escolhidas;

		}

		tempos_vector_nao_decrescentes << colunas << std::endl;
	}


	analise_emp_nao_decrescente (v_secundario, v_principal, range, quantidade_testes, executar_analises, tempos_vector_nao_decrescentes, funcoes_escolhidas);


	/*		Vector organizado com elementos em ordem não crescente		*/

	//	Criando um arquivo para armazenar as saídas da analise com elementos não crescentes.
	std::ofstream tempos_vector_nao_crescentes;
	tempos_vector_nao_crescentes.open ("tempos/tempos_vector_nao_crescentes.csv");

	if(tempos_vector_nao_crescentes.bad()){

		std::cerr << ERRO_ARQUIVO << std::endl;

		std::exit(1);
	}

	/*		Condições para imprimir no arquivo de saída os nomes das colunas com base nos algoritmos escolhidos pelo usuário.		*/
	if(aux_funcao == 1){

		tempos_vector_nao_crescentes << colunas << std::endl;

	} else {

		colunas = "tamanho_vetor";
		u_iterator it_escolhidas = funcoes_escolhidas.begin();

		while (it_escolhidas != funcoes_escolhidas.end()){

			colunas = colunas + virgula + colunas_vetor[(*it_escolhidas)];
			++it_escolhidas;

		}

		tempos_vector_nao_crescentes << colunas << std::endl;
	}

	analise_emp_nao_crescente (v_secundario, v_principal, range, quantidade_testes, executar_analises, tempos_vector_nao_crescentes, funcoes_escolhidas);

	/*		Vector organizado com elementos em ordem aleatória 		*/

	//	Criando um arquivo para armazenar as saídas da analise com elementos aleatórios.
	std::ofstream tempos_vector_aleatorio;
	tempos_vector_aleatorio.open ("tempos/tempos_vector_aleatorio.csv");
	if(tempos_vector_aleatorio.bad()){

		std::cerr << ERRO_ARQUIVO << std::endl;

		std::exit(1);
	}

	/*		Condições para imprimir no arquivo de saída os nomes das colunas com base nos algoritmos escolhidos pelo usuário.		*/
	if(aux_funcao == 1){

		tempos_vector_aleatorio << colunas << std::endl;

	} else {

		colunas = "tamanho_vetor";
		u_iterator it_escolhidas = funcoes_escolhidas.begin();

		while (it_escolhidas != funcoes_escolhidas.end()){

			colunas = colunas + virgula + colunas_vetor[(*it_escolhidas)];
			++it_escolhidas;

		}

		tempos_vector_aleatorio << colunas << std::endl;
	}

	analise_emp_aleatoria (v_secundario, v_principal, range, quantidade_testes, executar_analises, tempos_vector_aleatorio, funcoes_escolhidas);


	return 0;
}

	