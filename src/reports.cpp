#include "reports.h"
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

TotaisMes totaisDoMes(const Colaborador& c, int ano, int mes) {
    TotaisMes t;
    for (const auto& m : c.lista) {
        if (m.ano==ano && m.mes==mes) {
            if (m.tipo=='F') t.ferias++;
            else if (m.tipo=='X') t.faltas++;
        }
    }
    return t;
}

void relatorioMensalTodos(const vector<Colaborador>& lista, int ano, int mes) {
    cout << "\n--- Relatorio Mensal (" << mes << "/" << ano << ") ---\n";
    cout << left << setw(4) << "ID" << setw(20) << "Nome" << setw(15) << "Departamento"
         << right << setw(8) << "Ferias" << setw(8) << "Faltas" << "\n";
    for (const auto& c : lista) {
        TotaisMes t = totaisDoMes(c, ano, mes);
        cout << left << setw(4) << c.id
             << setw(20) << c.nome.substr(0,19)
             << setw(15) << c.departamento.substr(0,14)
             << right << setw(8) << t.ferias
             << setw(8) << t.faltas << "\n";
    }
    cout << "\n";
}

void dashboard(const vector<Colaborador>& lista, int ano, int mes, int totalFeriasAno) {
    cout << "\n--- Dashboard (" << mes << "/" << ano << ") ---\n";
    cout << left << setw(20) << "Nome" << right << setw(8) << "Ferias"
         << setw(8) << "Faltas" << setw(16) << "Dias rest. F" << "\n";
    for (const auto& c : lista) {
        TotaisMes tm = totaisDoMes(c, ano, mes);
        int usadasAno = contarNoAno(c, ano, 'F');
        int restantes = totalFeriasAno - usadasAno;
        if (restantes < 0) restantes = 0;
        cout << left << setw(20) << c.nome.substr(0,19)
             << right << setw(8) << tm.ferias
             << setw(8) << tm.faltas
             << setw(16) << restantes << "\n";
    }
    cout << "\n";
}

void estatisticasDepartamento(const vector<Colaborador>& lista, int ano, int mes) {
    map<string, pair<int,int>> mapa; // depto -> (F, X)
    for (const auto& c : lista) {
        TotaisMes t = totaisDoMes(c, ano, mes);
        auto &ref = mapa[c.departamento];
        ref.first  += t.ferias;
        ref.second += t.faltas;
    }
    cout << "\n--- Estatisticas por Departamento ("<< mes << "/" << ano <<") ---\n";
    cout << left << setw(15) << "Departamento" << right << setw(8) << "Ferias" << setw(8) << "Faltas" << "\n";
    string piorDepto; int piorAbs = -1;
    for (auto &kv : mapa) {
        cout << left << setw(15) << (kv.first.empty()?"(Sem)":kv.first)
             << right << setw(8) << kv.second.first
             << setw(8) << kv.second.second << "\n";
        int abs = kv.second.first + kv.second.second;
        if (abs > piorAbs) { piorAbs = abs; piorDepto = kv.first; }
    }
    if (!mapa.empty())
        cout << "Departamento com mais ausencias: " << (piorDepto.empty()?"(Sem)":piorDepto) << " ("<< piorAbs <<")\n\n";
}

bool haConflitoFeriasMesmoDepto(const vector<Colaborador>& lista, int ano, int mes, int dia, const string& departamento, int ignorarId) {
    if (departamento.empty()) return false;
    for (const auto& c : lista) {
        if (c.id == ignorarId) continue;
        if (c.departamento != departamento) continue;
        for (const auto& m : c.lista) {
            if (m.ano==ano && m.mes==mes && m.dia==dia && m.tipo=='F') return true;
        }
    }
    return false;
}
