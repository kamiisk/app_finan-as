#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_TRANSACTIONS 100
#define FILENAME "transactions.dat"

typedef struct {
    char description[100];
    float amount;
    char category[50];
    int is_credit; // 1 para crédito, 0 para débito
} Transaction;

void menu(Transaction transactions[], int *transaction_count);
void add_transaction(Transaction transactions[], int *transaction_count);
void list_transaction(Transaction transaction[], int transaction_count);
float balance(Transaction transactions[], int transactions_count);
void save_transactions(const char *filename, Transaction transactions[], int count);
int load_transactions(const char *filename, Transaction transactions[]);

int main() {

    setlocale(LC_ALL, "pt_BR.UTF-8");
    
    Transaction transactions[MAX_TRANSACTIONS];
    int transactions_count = load_transactions(FILENAME, transactions);
    
    menu(transactions, &transactions_count);

    return 0;
}

/* Função para adicionar nova transação */
void add_transaction(Transaction transactions[], int *transaction_count) {
    if (*transaction_count >= MAX_TRANSACTIONS) {
        printf("Limite de transacoes atingido!\n");
        return;
    }

    Transaction new_transaction;
    printf("Descricao: ");
    scanf(" %[^\n]", new_transaction.description);

    printf("Valor: ");
    scanf("%f", &new_transaction.amount);

    printf("Categoria: ");
    scanf(" %[^\n]", new_transaction.category);

    printf("É credito? (1 para sim, 0 para nao): ");
    scanf("%d", &new_transaction.is_credit);

    transactions[(*transaction_count)++] = new_transaction;
    printf("Transacao adicionada com sucesso!\n");
}

/* Função para listar transações */
void list_transactions(Transaction transactions[], int transaction_count) {
    if (transaction_count == 0) {
        printf("Nenhuma transacao cadastrada.\n");
        return;
    }

    for (int i = 0; i < transaction_count; i++) {
        printf("\nTransacao %d:\n", i + 1);
        printf("  Descricao: %s\n", transactions[i].description);
        printf("  Valor: R$ %.2f\n", transactions[i].amount);
        printf("  Categoria: %s\n", transactions[i].category);
        printf("  Tipo: %s\n", transactions[i].is_credit ? "Credito" : "Debito");
    }
}

/* Função para calcular o saldo */
float balance(Transaction transactions[], int transactions_count) {
    float saldo = 0;
    for (int i = 0; i < transactions_count; i++) {
        if (transactions[i].is_credit) {
            saldo -= transactions[i].amount;
        } else {
            saldo += transactions[i].amount;
        }
    }
    return saldo;
}

/* Salvar transações em arquivo binário */
void save_transactions(const char *filename, Transaction transactions[], int count) {
    FILE *file = fopen(FILENAME, "wb");
    if (file) {
        fwrite(transactions, sizeof(Transaction), count, file);
        fclose(file);
    } else {
        printf("Erro ao salvar transacao.\n");
    }
}

/* Carregar transações de arquivo binário */
int load_transactions(const char *filename, Transaction transactions[]) {
    FILE *file = fopen(FILENAME, "rb");
    if (file) {
        int count = fread(transactions, sizeof(Transaction), MAX_TRANSACTIONS, file);
        fclose(file);
        return count;
    } else {
        printf("Erro ao localizar arquivo. Criando novo arquivo.\n");
        return 0;
    }
}

/* Função Menu */
void menu(Transaction transactions[], int *transaction_count) {
    int choice;

    do {
        printf("\n--- Gerenciador Financeiro ---\n");
        printf("1 - Adicionar Transacao\n");
        printf("2 - Listar Transacoes\n");
        printf("3 - Calcular Saldo\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_transaction(transactions, transaction_count);
                save_transactions(FILENAME, transactions, *transaction_count);
                break;

            case 2:
                list_transactions(transactions, *transaction_count);
                break;

            case 3:
                printf("Saldo atual: R$ %.2f\n", balance(transactions, *transaction_count));
                break;

            case 0:
                save_transactions(FILENAME, transactions, *transaction_count);
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao Invalida!\n");
        }

    } while (choice != 0);
}
