#include "colaborador.h"

bool existeMarcacao(const Colaborador &c, int ano, int mes, int dia, char *tipoEncontrado) {
    for (const auto &m : c.lista) {
        if (m.ano == ano && m.mes == mes && m.dia == dia) {
            if (tipoEncontrado) *tipoEncontrado = m.tipo;
            return true;
        }
    }
    return false;
}

bool adicionarMarcacao(Colaborador &c, int ano, int mes, int dia, char tipo) {
    char t;
    if (existeMarcacao(c, ano, mes, dia, &t)) return false;
    c.lista.push_back({ano, mes, dia, tipo});
    return true;
}

bool removerMarcacao(Colaborador &c, int ano, int mes, int dia) {
    for (size_t i = 0; i < c.lista.size(); ++i) {
        if (c.lista[i].ano == ano && c.lista[i].mes == mes && c.lista[i].dia == dia) {
            c.lista.erase(c.lista.begin() + i);
            return true;
        }
    }
    return false;
}

int contarNoMes(const Colaborador& c, int ano, int mes, char tipo) {
    int tot = 0;
    for (const auto& m : c.lista)
        if (m.ano == ano && m.mes == mes && m.tipo == tipo) tot++;
    return tot;
}

int contarNoAno(const Colaborador& c, int ano, char tipo) {
    int tot = 0;
    for (const auto& m : c.lista)
        if (m.ano == ano && m.tipo == tipo) tot++;
    return tot;
}
