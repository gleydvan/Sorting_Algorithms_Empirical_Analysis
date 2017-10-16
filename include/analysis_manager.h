#ifndef ANALYSIS_MANAGER_H
#define ANALYSIS_MANAGER_H

#include <vector>
#include <iterator>

//	Definindo um tipo para o vector
typedef std::vector<unsigned int> u_vector;

//	Definindo um tipo para o iterator
typedef std::vector<unsigned int>::iterator u_iterator;

//	Definição dos ponteiros para funções e atribuição de nomes para os mesmo
using function_type = void ( * ) (u_iterator, u_iterator);
using analysis_type = void ( * ) (u_vector &, u_vector &, std::ofstream &, unsigned int, unsigned int, unsigned int);


void analise_emp_nao_decrescente (u_vector &secundario , u_vector &principal, unsigned int quantidade_elementos, unsigned int quantidade_testes,
									analysis_type analise, std::ofstream &arquivo, u_vector &funcoes_escolhidas);

void analise_emp_nao_crescente (u_vector &secundario , u_vector &principal, unsigned int quantidade_elementos, unsigned int quantidade_testes,
									analysis_type analise, std::ofstream &arquivo, u_vector &funcoes_escolhidas);

void analise_emp_aleatoria (u_vector &secundario , u_vector &principal,	unsigned int quantidade_elementos, unsigned int quantidade_testes, analysis_type analise, 
							std::ofstream &arquivo, u_vector &funcoes_escolhidas);

double medicao_tempo (u_iterator first_, u_iterator last_, function_type nome_funcao_ord);

void executar_analises (u_vector &secundario , u_vector &principal, std::ofstream &arquivo, unsigned int numero_elementos, unsigned int numero_testes, unsigned int numero_func);

#endif
