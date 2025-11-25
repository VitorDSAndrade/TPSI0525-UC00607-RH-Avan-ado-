#include "storage.h"
#include "utils.h"
#include <fstream>
#include <sstream>

using namespace std;

int procurarColaborador(const vector<Colaborador> &lista, const string &nome) {
    string n = minusculas(nome);
    for (size_t i = 0; i < lista.size(); i++)
        if (minusculas(lista[i].nome) == n) return (int)i;
    return -1;
}

int procurarColaboradorPorId(const vector<Colaborador> &lista, int id) {
    for (size_t i=0;i<lista.size();++i) if (lista[i].id == id) return (int)i;
    return -1;
}

int proximoId(const vector<Colaborador> &lista) {
    int m = 0;
    for (const auto& c : lista) if (c.id > m) m = c.id;
    return m + 1;
}

static bool parseDate(const std::string &s, int &y,int &m,int &d){
    if (s.size()!=10 || s[4]!='-' || s[7]!='-') return false;
    y = stoi(s.substr(0,4));
    m = stoi(s.substr(5,2));
    d = stoi(s.substr(8,2));
    return true;
}

bool guardar(const string &ficheiro, const vector<Colaborador> &lista) {
    ofstream f(ficheiro, ios::binary);
    if (!f.is_open()) return false;

    f << "H;V2\n";
    for (const auto &c : lista) {
        f << "C;" << c.id << ";" << cifraXOR(c.nome) << ";" << cifraXOR(c.departamento) << "\n";
    }
    for (const auto &c : lista) {
        for (const auto &m : c.lista) {
            f << "M;" << c.id << ";";
            f << m.ano << "-" << (m.mes<10?"0":"") << m.mes << "-" << (m.dia<10?"0":"") << m.dia;
            f << ";" << m.tipo << "\n";
        }
        for (const auto &fo : c.formacoes) {
            f << "F;" << c.id << ";" << cifraXOR(fo.nome_curso) << ";" << fo.data_conclusao << "\n";
        }
        for (const auto &nt : c.notas) {
            f << "N;" << c.id << ";" << nt.data << ";" << cifraXOR(nt.texto) << "\n";
        }
    }
    return true;
}

bool carregar(const string &ficheiro, vector<Colaborador> &lista) {
    ifstream f(ficheiro, ios::binary);
    if (!f.is_open()) return false;

    lista.clear();
    string line;
    bool v2 = false;

    // Leitura completa para suportar V1 e V2
    vector<string> lines;
    while (getline(f, line)) lines.push_back(line);

    if (!lines.empty() && lines[0] == "H;V2") v2 = true;

    if (v2) {
        // V2
        for (auto &ln : lines) {
            if (ln.rfind("C;",0)==0) {
                // C;id;nome;departamento
                string tag, sid, nomeEnc, depEnc;
                stringstream ss(ln);
                getline(ss, tag, ';');
                getline(ss, sid, ';');
                getline(ss, nomeEnc, ';');
                getline(ss, depEnc, ';');
                Colaborador c;
                c.id = stoi(sid);
                c.nome = cifraXOR(nomeEnc);
                c.departamento = cifraXOR(depEnc);
                lista.push_back(c);
            }
        }
        for (auto &ln : lines) {
            if (ln.rfind("M;",0)==0) {
                string tag, sid, data, tipoStr;
                stringstream ss(ln);
                getline(ss, tag, ';');
                getline(ss, sid, ';');
                getline(ss, data, ';');
                getline(ss, tipoStr, ';');
                int idx = procurarColaboradorPorId(lista, stoi(sid));
                if (idx<0) continue;
                int y,m,d; if(!parseDate(data,y,m,d)) continue;
                char t = tipoStr.empty()?' ':tipoStr[0];
                lista[idx].lista.push_back({y,m,d,t});
            } else if (ln.rfind("F;",0)==0) {
                string tag, sid, cursoEnc, data;
                stringstream ss(ln);
                getline(ss, tag, ';');
                getline(ss, sid, ';');
                getline(ss, cursoEnc, ';');
                getline(ss, data, ';');
                int idx = procurarColaboradorPorId(lista, stoi(sid));
                if (idx<0) continue;
                lista[idx].formacoes.push_back({cifraXOR(cursoEnc), data});
            } else if (ln.rfind("N;",0)==0) {
                string tag, sid, data, textoEnc;
                stringstream ss(ln);
                getline(ss, tag, ';');
                getline(ss, sid, ';');
                getline(ss, data, ';');
                getline(ss, textoEnc, ';');
                int idx = procurarColaboradorPorId(lista, stoi(sid));
                if (idx<0) continue;
                lista[idx].notas.push_back({cifraXOR(textoEnc), data});
            }
        }
    } else {
        // V1 (compat)
        vector<string> nomes;
        vector<string> eventos;
        for (auto &ln : lines) {
            if (ln.rfind("C;",0)==0) nomes.push_back(cifraXOR(ln.substr(2)));
            else if (ln.rfind("M;",0)==0) eventos.push_back(ln);
        }
        // cria colaboradores com id sequencial
        int id = 1;
        for (auto &n : nomes) {
            Colaborador c;
            c.id = id++;
            c.nome = n;
            c.departamento = "";
            lista.push_back(c);
        }
        // eventos
        for (auto &ln : eventos) {
            // M;<nome_enc>;<yyyy-mm-dd>;<tipo>
            string tag, nomeEnc, data, tipoStr;
            stringstream ss(ln);
            getline(ss, tag, ';');
            getline(ss, nomeEnc, ';');
            getline(ss, data, ';');
            getline(ss, tipoStr, ';');
            string nome = cifraXOR(nomeEnc);
            int idx = procurarColaborador(lista, nome);
            if (idx<0) continue;
            int y,m,d; if(!parseDate(data,y,m,d)) continue;
            char t = tipoStr.empty()?' ':tipoStr[0];
            lista[idx].lista.push_back({y,m,d,t});
        }
    }

    return true;
}
