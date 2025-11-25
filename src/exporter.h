#ifndef EXPORTER_H
#define EXPORTER_H

#include <vector>
#include <string>
#include "colaborador.h"

bool exportCalendarioTXT(const Colaborador& c, int ano, int mes, const std::string& path);
bool exportRelatorioTXT(const std::vector<Colaborador>& lista, int ano, int mes, const std::string& path);

#endif
