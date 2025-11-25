#ifndef COLABORADOR_H
#define COLABORADOR_H

#include <string>
#include <vector>

struct Marcacao {
    int ano;
    int mes;
    int dia;
    char tipo;   // 'F' férias, 'X' falta
};

struct Formacao {
    std::string nome_curso;
    std::string data_conclusao; // yyyy-mm-dd
};

struct Nota {
    std::string texto;
    std::string data; // yyyy-mm-dd
};

struct Colaborador {
    int id{0};                      // NOVO: ID interno
    std::string nome;               // Nome desencriptado
    std::string departamento;       // NOVO
    std::vector<Marcacao> lista;    // Marcações
    std::vector<Formacao> formacoes;// NOVO
    std::vector<Nota> notas;        // NOVO
};

// Marcações
bool existeMarcacao(const Colaborador &c, int ano, int mes, int dia, char *tipoEncontrado = nullptr);
bool adicionarMarcacao(Colaborador &c, int ano, int mes, int dia, char tipo);
bool removerMarcacao(Colaborador &c, int ano, int mes, int dia);

// Utilitários
int contarNoMes(const Colaborador& c, int ano, int mes, char tipo); // 'F' ou 'X'
int contarNoAno(const Colaborador& c, int ano, char tipo);

#endif
