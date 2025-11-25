#include "calendar.h"
#include <iostream>
#include <iomanip>

using namespace std;

bool anoBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int diasNoMes(int ano, int mes) {
    int tabela[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (mes == 2 && anoBissexto(ano)) return 29;
    return tabela[mes - 1];
}
// Adaptado do algoritmo de sakamoto (para calcular dias da semana)
int diaSemana(int ano, int mes, int dia) {
    static int t[] = {0,3,2,5,0,3,5,1,4,6,2,4};
    ano -= (mes < 3);
    int w = (ano + ano/4 - ano/100 + ano/400 + t[mes-1] + dia) % 7;
    if (w == 0) return 6; // domingo → 6
    return w - 1;         // ajusta Segunda=0
}

void mostrarCalendario(const Colaborador &c, int ano, int mes) {
    cout << "\n----- " << mes << "/" << ano << " -----\n";
    cout << "Legenda: F = Férias | X = Falta | * = Fim-de-semana\n\n";

    cout << setw(4) << "Seg" << setw(4) << "Ter" << setw(4) << "Qua"
         << setw(4) << "Qui" << setw(4) << "Sex" << setw(4) << "Sab"
         << setw(4) << "Dom" << "\n";

    int primeiro = diaSemana(ano, mes, 1); // 0=Seg...6=Dom
    int total = diasNoMes(ano, mes);

    int col = 0;

    for (int i = 0; i < primeiro; i++) {
        cout << setw(4) << "";
        col++;
    }

    for (int d = 1; d <= total; d++) {
        char tipo = ' ';
        bool temMarcacao = existeMarcacao(c, ano, mes, d, &tipo);
        bool fimSemana = (diaSemana(ano, mes, d) >= 5);

        // Construir célula de 4 caracteres para a tabela nao ficar nojentamente desalinhada
        char cell[5];

        // Caso com marcação (F ou X)
        if (temMarcacao) {
            snprintf(cell, sizeof(cell), "%2d%c ", d, tipo);   
        }
        // Caso fim de semana
        else if (fimSemana) {
            snprintf(cell, sizeof(cell), "%2d* ", d); 
        }
        // Caso dia normal
        else {
            snprintf(cell, sizeof(cell), "%2d  ", d); 
        }

        cout << cell;


        col++;
        if (col == 7) {
            cout << "\n";
            col = 0;
        }
    }

    if (col != 0) cout << "\n";
    cout << "\n";
}
