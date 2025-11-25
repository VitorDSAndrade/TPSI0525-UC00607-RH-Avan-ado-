#ifndef CALENDAR_H
#define CALENDAR_H

#include "colaborador.h"

bool anoBissexto(int ano);
int diasNoMes(int ano, int mes);
int diaSemana(int ano, int mes, int dia);   // 0 = Segunda ... 6 = Domingo

void mostrarCalendario(const Colaborador &c, int ano, int mes);

#endif
