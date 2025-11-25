#ifndef REPORTS_H
#define REPORTS_H

#include <vector>
#include <string>
#include "colaborador.h"

struct TotaisMes {
    int ferias{0};
    int faltas{0};
};

TotaisMes totaisDoMes(const Colaborador& c, int ano, int mes);
void relatorioMensalTodos(const std::vector<Colaborador>& lista, int ano, int mes);
void dashboard(const std::vector<Colaborador>& lista, int ano, int mes, int totalFeriasAno=22);
void estatisticasDepartamento(const std::vector<Colaborador>& lista, int ano, int mes);

bool haConflitoFeriasMesmoDepto(const std::vector<Colaborador>& lista, int ano, int mes, int dia, const std::string& departamento, int ignorarId);

#endif
