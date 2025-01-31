# Gerenciador Financeiro em C

Um aplicativo simples em C para gerenciar suas finanças pessoais, registrar transações e acompanhar gastos com cartão de crédito.

---

## Funcionalidades

- **Adicionar Transação**: Registre suas transações com descrição, valor, categoria e tipo (crédito ou débito).
- **Listar Transações**: Visualize todas as transações cadastradas.
- **Calcular Saldo**: Veja o saldo atual com base nas transações registradas.
- **Persistência de Dados**: As transações são salvas em um arquivo binário para que não se percam ao fechar o programa.

---

## Como Usar

### Pré-requisitos

- Compilador C (ex.: GCC).
- Terminal ou ambiente de execução configurado para UTF-8 (para suportar caracteres especiais do português).

### Compilação

1. Clone o repositório ou baixe o arquivo `moo.c`.
2. Compile o programa usando o GCC:
   ```bash
   gcc moo.c -o moo