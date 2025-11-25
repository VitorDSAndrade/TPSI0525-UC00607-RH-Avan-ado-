#include <iostream>
#include <vector>
#include <limits>
#include <ctime>

#include "colaborador.h"
#include "calendar.h"
#include "storage.h"
#include "reports.h"
#include "exporter.h"

using namespace std;

string CAMINHO = "../data/dados_rh.csv";

// ------------------------------------------------
// FUNÇÕES AUXILIARES
// ------------------------------------------------

void pausa() {
    cout << "\nPressione ENTER...";
    // Se ainda houver um '\n' pendurado no buffer, limpa-o
    if (cin.peek() == '\n')
        cin.ignore();
    // Agora espera mesmo pelo ENTER do utilizador
    cin.get();
}

int lerInt(const string &msg, int min, int max) {
    int v;
    while (true) {
        cout << msg;
        if (cin >> v && v >= min && v <= max) return v;

        cout << "Valor invalido.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string lerLinha(const string &msg) {
    cout << msg;

    // Se o próximo char for '\n', significa que ficou lixo do cin >> anterior
    if (cin.peek() == '\n')
        cin.ignore();

    string s;
    getline(cin, s);
    return s;
}

int escolherColab(const vector<Colaborador> &lista) {
    if (lista.empty()) {
        cout << "\nNao ha colaboradores.\n";
        return -1;
    }

    cout << "\n--- COLABORADORES ---\n";
    for (size_t i = 0; i < lista.size(); i++) {
        cout << (i+1) << ") [" << lista[i].id << "] "
             << lista[i].nome << " (" << lista[i].departamento << ")\n";
    }

    int esc = lerInt("Escolha (0 cancelar): ", 0, (int)lista.size());
    return (esc == 0) ? -1 : (esc - 1);
}

bool fimDeSemana(int ano, int mes, int dia) {
    return diaSemana(ano, mes, dia) >= 5;
}

int anoAtual() {
    time_t t = time(nullptr);
    tm* a = localtime(&t);
    return a->tm_year + 1900;
}

int mesAtual() {
    time_t t = time(nullptr);
    tm* a = localtime(&t);
    return a->tm_mon + 1;
}

// ------------------------------------------------
// SUBMENUS
// ------------------------------------------------

void menuFormacoes(Colaborador &c) {
    while (true) {
        cout << "\n--- FORMACOES DE " << c.nome << " ---\n"
             << "1) Listar\n"
             << "2) Adicionar\n"
             << "3) Editar\n"
             << "4) Remover\n"
             << "0) Voltar\n"
             << "Opcao: ";

        int op;
        if (!(cin >> op)) return;

        if (op == 0) break;

        if (op == 1) {
            if (c.formacoes.empty()) cout << "(nenhuma)\n";
            for (size_t i=0; i < c.formacoes.size(); i++) {
                cout << (i+1) << ") " << c.formacoes[i].nome_curso
                     << " (" << c.formacoes[i].data_conclusao << ")\n";
            }
        }

        else if (op == 2) {
            string nome = lerLinha("Nome curso: ");
            string data = lerLinha("Data conclusao (yyyy-mm-dd): ");
            c.formacoes.push_back({nome, data});
            cout << "Adicionado.\n";
        }

        else if (op == 3) {
            if (c.formacoes.empty()) {
                cout << "Sem formacoes.\n";
                continue;
            }
            int idx = lerInt("Qual numero? ", 1, (int)c.formacoes.size()) - 1;
            string nome = lerLinha("Novo nome: ");
            string data = lerLinha("Nova data: ");
            c.formacoes[idx] = {nome, data};
            cout << "Atualizado.\n";
        }

        else if (op == 4) {
            if (c.formacoes.empty()) {
                cout << "Sem formacoes.\n";
                continue;
            }
            int idx = lerInt("Qual numero? ", 1, (int)c.formacoes.size()) - 1;
            c.formacoes.erase(c.formacoes.begin() + idx);
            cout << "Removido.\n";
        }
    }
}

void menuNotas(Colaborador &c) {
    while (true) {
        cout << "\n--- NOTAS DE " << c.nome << " ---\n"
             << "1) Listar\n"
             << "2) Adicionar\n"
             << "3) Editar\n"
             << "4) Remover\n"
             << "0) Voltar\n"
             << "Opcao: ";

        int op;
        if (!(cin >> op)) return;

        if (op == 0) break;

        if (op == 1) {
            if (c.notas.empty()) cout << "(nenhuma)\n";
            for (size_t i=0; i < c.notas.size(); i++) {
                cout << (i+1) << ") [" << c.notas[i].data << "] "
                     << c.notas[i].texto << "\n";
            }
        }

        else if (op == 2) {
            string texto = lerLinha("Texto: ");
            string data  = lerLinha("Data (yyyy-mm-dd): ");
            c.notas.push_back({texto, data});
            cout << "Adicionada.\n";
        }

        else if (op == 3) {
            if (c.notas.empty()) {
                cout << "Sem notas.\n";
                continue;
            }
            int idx = lerInt("Qual numero? ", 1, (int)c.notas.size()) - 1;
            string texto = lerLinha("Novo texto: ");
            string data  = lerLinha("Nova data: ");
            c.notas[idx] = {texto, data};
            cout << "Atualizada.\n";
        }

        else if (op == 4) {
            if (c.notas.empty()) {
                cout << "Sem notas.\n";
                continue;
            }
            int idx = lerInt("Qual numero? ", 1, (int)c.notas.size()) - 1;
            c.notas.erase(c.notas.begin() + idx);
            cout << "Removida.\n";
        }
    }
}

// ------------------------------------------------
// REMOVER COLABORADOR (OPÇÃO 2)
// ------------------------------------------------

void removerColaborador(vector<Colaborador> &lista) {
    if (lista.empty()) {
        cout << "\nNao ha colaboradores para remover.\n";
        pausa();
        return;
    }

    int i = escolherColab(lista);
    if (i < 0) return;

    cout << "\nTem a certeza que deseja remover "
         << lista[i].nome << " (" << lista[i].departamento << ")? (s/N): ";

    char r;
    cin >> r;

    if (r != 's' && r != 'S') {
        cout << "Operacao cancelada.\n";
        pausa();
        return;
    }

    lista.erase(lista.begin() + i);
    cout << "Colaborador removido.\n";
    pausa();
}

// ------------------------------------------------
// MAIN
// ------------------------------------------------

int main() {
    vector<Colaborador> lista;

    if (carregar(CAMINHO, lista))
        cout << "Dados carregados.\n";
    else
        cout << "Sem ficheiro, a iniciar vazio.\n";

    while (true) {
        cout << "\n=============================\n"
             << "        RH AVANCADO\n"
             << "=============================\n"
             << "1) Listar colaboradores\n"
             << "2) Remover colaborador\n"
             << "3) Adicionar colaborador\n"
             << "4) Marcar ferias/falta\n"
             << "5) Desmarcar ferias/falta\n"
             << "6) Ver calendario mensal\n"
             << "7) Buscar colaborador (ID/nome)\n"
             << "8) Gerir formacoes\n"
             << "9) Gerir notas\n"
             << "10) Relatorio mensal (todos)\n"
             << "11) Estatisticas por departamento\n"
             << "12) Dashboard\n"
             << "13) Exportar TXT\n"
             << "0) Sair\n";

        int op = lerInt("Opcao: ", 0, 13);

        // 0 - SAIR
        if (op == 0) {
            guardar(CAMINHO, lista);
            cout << "Dados guardados.\n";
            break;
        }

        // 1 - LISTAR
        else if (op == 1) {
            cout << "\n--- COLABORADORES ---\n";
            for (auto &c : lista)
                cout << "ID " << c.id << " | "
                     << c.nome << " | " << c.departamento << "\n";
            pausa();
        }

        // 2 - REMOVER
        else if (op == 2) {
            removerColaborador(lista);
        }

        // 3 - ADICIONAR
        else if (op == 3) {
            string nome = lerLinha("Nome: ");
            string dept = lerLinha("Departamento: ");

            Colaborador c;
            c.id = proximoId(lista);
            c.nome = nome;
            c.departamento = dept;

            lista.push_back(c);
            cout << "Adicionado com ID " << c.id << "\n";
            pausa();
        }

        // 4 - MARCAR
        else if (op == 4) {
            int i = escolherColab(lista);
            if (i < 0) continue;

            int ano = lerInt("Ano: ", 1900, 2100);
            int mes = lerInt("Mes: ", 1, 12);
            int dia = lerInt("Dia: ", 1, diasNoMes(ano, mes));

            if (fimDeSemana(ano, mes, dia)) {
                cout << "Nao pode marcar fim-de-semana.\n";
                pausa();
                continue;
            }

            cout << "Tipo (F ferias / X falta): ";
            char t; cin >> t;

            t = (t=='f'||t=='F') ? 'F' : 'X';

            if (t == 'F') {
                if (haConflitoFeriasMesmoDepto(lista, ano, mes, dia, lista[i].departamento, lista[i].id)) {
                    cout << "Aviso: ja ha ferias nesse dia no departamento!\n"
                         << "Continuar? (s/N): ";
                    char r; cin >> r;
                    if (r!='s' && r!='S') {
                        pausa();
                        continue;
                    }
                }
            }

            if (adicionarMarcacao(lista[i], ano, mes, dia, t))
                cout << "Marcado.\n";
            else
                cout << "Ja existe marcacao.\n";

            pausa();
        }

        // 5 - DESMARCAR
        else if (op == 5) {
            int i = escolherColab(lista);
            if (i < 0) continue;

            int ano = lerInt("Ano: ", 1900, 2100);
            int mes = lerInt("Mes: ", 1, 12);
            int dia = lerInt("Dia: ", 1, diasNoMes(ano, mes));

            if (removerMarcacao(lista[i], ano, mes, dia))
                cout << "Desmarcado.\n";
            else
                cout << "Nao existia marcacao.\n";

            pausa();
        }

        // 6 - CALENDARIO
        else if (op == 6) {
            int i = escolherColab(lista);
            if (i < 0) continue;

            int ano = lerInt("Ano: ", 1900, 2100);
            int mes = lerInt("Mes: ", 1, 12);

            mostrarCalendario(lista[i], ano, mes);
            pausa();
        }

        // 7 - BUSCA
        else if (op == 7) {
            cout << "1) Procurar ID\n2) Procurar nome\n";
            int b; cin >> b;
            int idx = -1;

            if (b == 1) {
                int id = lerInt("ID: ", 1, 999999);
                idx = procurarColaboradorPorId(lista, id);
            } else {
                string nome = lerLinha("Nome: ");
                idx = procurarColaborador(lista, nome);
            }

            if (idx < 0) {
                cout << "Nao encontrado.\n";
                pausa();
                continue;
            }

            cout << "Encontrado: " << lista[idx].nome << " | "
                 << lista[idx].departamento << "\n";

            mostrarCalendario(lista[idx], anoAtual(), mesAtual());
            pausa();
        }

        // 8 - FORMAÇÕES
        else if (op == 8) {
            int i = escolherColab(lista);
            if (i >= 0) menuFormacoes(lista[i]);
            pausa();
        }

        // 9 - NOTAS
        else if (op == 9) {
            int i = escolherColab(lista);
            if (i >= 0) menuNotas(lista[i]);
            pausa();
        }

        // 10 - RELATÓRIO MENSAL
        else if (op == 10) {
            int ano = lerInt("Ano: ", 1900, 2100);
            int mes = lerInt("Mes: ", 1, 12);
            relatorioMensalTodos(lista, ano, mes);
            pausa();
        }

        // 11 - ESTATÍSTICAS POR DEPARTAMENTO
        else if (op == 11) {
            int ano = lerInt("Ano: ", 1900, 2100);
            int mes = lerInt("Mes: ", 1, 12);
            estatisticasDepartamento(lista, ano, mes);
            pausa();
        }

        // 12 - DASHBOARD
        else if (op == 12) {
            int ano = lerInt("Ano: ", 1900, 2100);
            int mes = lerInt("Mes: ", 1, 12);
            dashboard(lista, ano, mes, 22);
            pausa();
        }

        // 13 - EXPORTAÇÃO 
        else if (op == 13) {
            cout << "1) Exportar calendario TXT (1 colaborador)\n"
                 << "2) Exportar relatorio TXT (todos)\nOpcao: ";
            int ex; cin >> ex;

            if (ex == 1) {
                int i = escolherColab(lista);
                if (i < 0) continue;

                int ano = lerInt("Ano: ", 1900, 2100);
                int mes = lerInt("Mes: ", 1, 12);

                string path = lerLinha("Caminho TXT: ");
                if (exportCalendarioTXT(lista[i], ano, mes, path))
                    cout << "Exportado.\n";
                else
                    cout << "Erro.\n";
            } else {
                int ano = lerInt("Ano: ", 1900, 2100);
                int mes = lerInt("Mes: ", 1, 12);

                string path = lerLinha("Caminho TXT: ");
                if (exportRelatorioTXT(lista, ano, mes, path))
                    cout << "Exportado.\n";
                else
                    cout << "Erro.\n";
            }

            pausa();
        }
    }

    return 0;
}
