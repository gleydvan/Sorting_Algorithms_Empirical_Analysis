#ifndef FILL_MANAGER_H
#define FILL_MANAGER_H

#include <vector>
#include <iterator>

//	Definindo um um tipo para o vector
typedef std::vector<unsigned int> u_vector;

//	Definindo um tipo para o iterator
typedef std::vector<unsigned int>::iterator u_iterator;

void preencher_nao_decrescente (u_vector &secundario);

void preencher_nao_crescente (u_vector &secundario, unsigned int quantidade_elementos);

void preencher_aleatorio (u_vector &secundario, unsigned int quantidade_elementos);

#endif