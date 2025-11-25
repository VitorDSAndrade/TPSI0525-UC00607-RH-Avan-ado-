#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <string>
#include "colaborador.h"

bool guardar(const std::string &ficheiro, const std::vector<Colaborador> &lista);
bool carregar(const std::string &ficheiro, std::vector<Colaborador> &lista);

int procurarColaborador(const std::vector<Colaborador> &lista, const std::string &nome);
int procurarColaboradorPorId(const std::vector<Colaborador> &lista, int id);
int proximoId(const std::vector<Colaborador> &lista);

#endif
