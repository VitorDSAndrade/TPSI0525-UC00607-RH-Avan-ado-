#include "exporter.h"
#include "calendar.h"
#include <fstream>
#include <iomanip>

using namespace std;

// -----------------------------------------------------------
// EXPORTAR CALENDÁRIO INDIVIDUAL (TXT)
// -----------------------------------------------------------
bool exportCalendarioTXT(const Colaborador& c, int ano, int mes, const string& path) {
    ofstream f(path);
    if (!f.is_open()) return false;

    f << "=========================================\n";
    f << "     CALENDARIO DE " << c.nome << "\n";
    f << "     Departamento: " << c.departamento << "\n";
    f << "     Mes: " << mes << " / " << ano << "\n";
    f << "=========================================\n\n";

    static const char* headers[7] = {"Seg","Ter","Qua","Qui","Sex","Sab","Dom"};

    for (int i=0; i<7; i++)
        f << setw(4) << headers[i];
    f << "\n";

    int dim = diasNoMes(ano, mes);
    int start = diaSemana(ano, mes, 1); // 0 = Seg
    int col = 0;

    for (int j=0; j<start; j++) {
        f << setw(4) << "";
        col++;
    }

    for (int d=1; d <= dim; d++) {
        char tipo=' ';
        bool existe = existeMarcacao(c, ano, mes, d, &tipo);

        if (tipo == 'F')      f << setw(4) << "F";
        else if (tipo == 'X') f << setw(4) << "X";
        else                  f << setw(4) << d;

        col++;
        if (col == 7) {
            f << "\n";
            col = 0;
        }
    }

    f << "\n\nLegenda:\n";
    f << "F = Férias\nX = Falta\n\n";

    return true;
}


// -----------------------------------------------------------
// EXPORTAR RELATÓRIO MENSAL (TXT) — TODOS OS COLABORADORES
// -----------------------------------------------------------
bool exportRelatorioTXT(const vector<Colaborador>& lista, int ano, int mes, const string& path) {
    ofstream f(path);
    if (!f.is_open()) return false;

    f << "=========================================\n";
    f << "       RELATORIO MENSAL - " << mes << "/" << ano << "\n";
    f << "=========================================\n\n";

    for (const auto& c : lista) {
        int totalF = 0;
        int totalX = 0;

        // Contar marcações dentro do mês
        for (const auto& m : c.lista) {   
            if (m.ano == ano && m.mes == mes) {
                if (m.tipo == 'F') totalF++;
                if (m.tipo == 'X') totalX++;
            }
        }

        f << "ID: " << c.id << "\n";
        f << "Nome: " << c.nome << "\n";
        f << "Departamento: " << c.departamento << "\n";
        f << "Férias: " << totalF << "\n";
        f << "Faltas: " << totalX << "\n";
        f << "-----------------------------------------\n";
    }

    return true;
}
