# RH Avançado – Sistema de Gestão de Recursos Humanos em C++

Projeto de consola desenvolvido em C++ para gestão de Recursos Humanos, com foco em organização modular, persistência de dados em ficheiros, validação de datas e geração de relatórios.

Este projeto foi desenvolvido com o objetivo de consolidar conceitos de:
- Programação Modular em C++
- Manipulação de ficheiros (CSV e TXT)
- Estruturas de dados
- Validação de entradas
- Geração de relatórios e exportação

---

## 📁 Estrutura do Projeto
```
EXCPPRH/
├── data/
│   ├── dados_rh.csv          # Base de dados principal dos colaboradores
│   └── relatorio.txt          # Ficheiros de exportação de relatórios
│
├── src/
│   ├── main.cpp               # Menu principal e controlo da aplicação
│   ├── colaborador.h/.cpp     # Estrutura do colaborador e lógica associada
│   ├── calendar.h/.cpp        # Cálculo de datas e geração do calendário
│   ├── storage.h/.cpp         # Leitura e escrita de ficheiros CSV
│   ├── reports.h/.cpp         # Relatórios e estatísticas
│   ├── exporter.h/.cpp        # Exportação de ficheiros TXT
│   └── utils.h/.cpp           # Funções auxiliares (validações, apoio)
│
├── README.md                  # Documentação do projeto
└── rh_app.exe                 # Executável da aplicação
```



---

## ⚙️ Funcionalidades do Sistema

### 👥 Gestão de Colaboradores
- Listar colaboradores existentes
- Adicionar novos colaboradores
- Remover colaboradores existentes
- Pesquisa por ID ou nome

Cada colaborador possui:
- ID único
- Nome
- Departamento
- Registos de férias e faltas
- Formações
- Notas internas

---

### 📅 Gestão de Férias e Faltas

É possível:
- Marcar férias (`F`)
- Marcar faltas (`X`)
- Desmarcar eventos já registados

O sistema inclui:
✅ Validação de datas  
✅ Bloqueio de fins-de-semana  
✅ Deteção de conflitos dentro do mesmo departamento  

---

### 🗓️ Calendário Mensal

O sistema gera automaticamente um calendário mensal em modo de texto:

- Dias normais → vazios
- `F` → férias
- `X` → faltas
- `*` → fins-de-semana

---

### 📝 Formações

Cada colaborador pode ter:
- Lista de formações
- Data de conclusão de cada formação
- Possibilidade de adicionar / editar / remover formações

---

### 🗒️ Notas Internas

Permite manter notas por colaborador com:
- Texto da nota
- Data registada

---

## 📊 Relatórios

Através do módulo `reports.cpp`, o sistema permite:

- Relatório mensal geral
- Estatísticas por departamento
- Dashboard resumo mensal

---

## 📤 Exportação

Módulo `exporter.cpp` permite:

- Exportar o calendário de um colaborador para `.txt`
- Exportar o relatório geral para `.txt`

Os ficheiros são guardados automaticamente na pasta:

/data/

---

## 💾 Persistência de Dados

Toda a informação é guardada em:
data/dados_rh.csv


O módulo `storage.cpp` é responsável por:
- Ler os dados ao iniciar o programa
- Gravar automaticamente ao sair

---

## 🧠 Arquitetura do Código

O projeto foi construído de forma **modular**, separando responsabilidades:

| Ficheiro         | Função principal |
|------------------|-----------------|
| `main.cpp`       | Menus e fluxo do programa |
| `colaborador.cpp`| Lógica do modelo de colaborador |
| `calendar.cpp`   | Gestão de datas e calendários |
| `storage.cpp`    | Leitura/Escrita CSV |
| `reports.cpp`    | Estatísticas e relatórios |
| `exporter.cpp`   | Exportação TXT |
| `utils.cpp`      | Funções de apoio |

---

## 🛠️ Compilação

Dentro da pasta `src`:

```bash
g++ -std=c++17 -Wall -Wextra -o ../rh_app \
main.cpp colaborador.cpp calendar.cpp storage.cpp reports.cpp exporter.cpp utils.cpp


▶️ Execução

No Windows: rh_app.exe


🐞 Problemas Comuns  (A principio nao deve acontecer mas se por acaso...)

Não guarda o CSV?
→ Verificar se a pasta /data existe.

Caracteres estranhos no terminal?
→ No Windows executar: chcp 65001
