# Mini-Sistema de Gestão de RH em C++

Sistema de gestão de Recursos Humanos desenvolvido em C++ para consola, permitindo gerir colaboradores, marcar férias e faltas, e visualizar calendários mensais com todas as marcações.

---

## 🎯 Objetivos do Projeto

- **Modularização em C++** – Código organizado em módulos reutilizáveis
- **Estruturas de dados** – Utilização de `struct` e `std::vector`
- **Validação de datas** – Anos bissextos, dias válidos por mês, fins-de-semana
- **Persistência de dados** – Armazenamento em ficheiro CSV
- **Segurança básica** – Cifra XOR para ofuscar nomes de colaboradores
- **Interface textual** – Calendário mensal formatado em consola

---

## 📁 Estrutura do Projeto

```
projeto/
├── src/
│   ├── main.cpp              # Menu principal e lógica de navegação
│   ├── colaborador.h/.cpp    # Estruturas e funções de marcações
│   ├── calendar.h/.cpp       # Geração do calendário mensal
│   ├── storage.h/.cpp        # Persistência em CSV com cifra
│   └── utils.h               # Cifra XOR e funções auxiliares
└── data/
    └── dados_rh.csv          # Ficheiro gerado automaticamente
```

---

## ⚙️ Funcionalidades

### 👤 Gestão de Colaboradores
- Adicionar novos colaboradores à lista
- Validação de duplicados com pedido de confirmação
- Nomes guardados com cifra XOR para privacidade básica

### 📅 Marcação de Férias e Faltas
Permite marcar dias com validações automáticas:

**Tipos de marcação:**
- `F` → Férias
- `X` → Falta

**Validações incluídas:**
- ✅ Verifica se o dia é válido para o mês/ano
- ✅ Considera anos bissextos
- ❌ Bloqueia marcações em fins-de-semana
- ❌ Impede marcações duplicadas no mesmo dia

### 🗓️ Visualização de Calendário
Calendário mensal em formato texto com legenda:
- Dias normais em branco
- `F` → Férias marcadas
- `X` → Faltas marcadas
- `*` → Fins-de-semana

**Exemplo:**
```
Seg Ter Qua Qui Sex Sab Dom
  1   2   3   4   5   6*  7*
  8   9  F   11  12  13* 14*
 15  X   17  18  19  20* 21*
```

### 🗑️ Desmarcação
Remove marcações existentes de forma simples e intuitiva.

### 💾 Persistência Automática
Todos os dados são guardados automaticamente ao sair em `data/dados_rh.csv`.

---

## 🔐 Segurança

**Cifra XOR:** Os nomes dos colaboradores são ofuscados usando XOR com chave `0x5A`. O mesmo processo é usado para cifrar e decifrar, garantindo privacidade básica dos dados armazenados.

---

## 🛠️ Compilação

### Pré-requisitos
- Compilador C++ com suporte a C++17 ou superior
- Sistema operativo: Windows, Linux ou macOS

### Comandos

**Dentro da pasta `/src`:**

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic \
  main.cpp colaborador.cpp calendar.cpp storage.cpp utils.cpp \
  -o ../rh_app
```

---

## ▶️ Execução

### Windows (PowerShell recomendado)

**1. Configurar codificação UTF-8 (necessário para caracteres especiais):**
```powershell
chcp 65001
```

**2. Executar o programa:**
```powershell
..\rh_app.exe
```

### Linux/macOS
```bash
../rh_app
```

> **⚠️ Nota:** Apenas testado em Windows. Em caso de problemas com caracteres especiais, executar `chcp 65001` antes de iniciar o programa.

---

## 📖 Como Usar

1. **Iniciar o programa** – O sistema carrega automaticamente os dados existentes
2. **Menu principal** – Selecionar a operação desejada:
   - ➕ Adicionar colaborador
   - 📅 Marcar férias ou falta
   - 🗑️ Desmarcar marcação
   - 🗓️ Ver calendário mensal
   - 💾 Sair (grava automaticamente)
3. **Seguir as instruções** – O programa guia através de cada operação
4. **Sair com segurança** – Todos os dados são persistidos automaticamente

---

## 📝 Notas Técnicas

- **Bibliotecas:** Apenas bibliotecas padrão do C++ (sem dependências externas)
- **Formato de dados:** CSV simples com nomes cifrados
- **Validação:** Todas as entradas são validadas antes do processamento
- **Codificação:** UTF-8 para suporte a caracteres especiais portugueses

---

## 🐛 Resolução de Problemas

**Caracteres especiais não aparecem corretamente:**
```powershell
chcp 65001
```

**Ficheiro dados_rh.csv não é criado:**
- Verificar permissões da pasta `data/`
- Criar a pasta manualmente se necessário

**Erros de compilação:**
- Confirmar versão do compilador (C++17 mínimo)
- Verificar se todos os ficheiros `.cpp` estão no comando de compilação

