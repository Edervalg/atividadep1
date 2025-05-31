#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NOME 50
#define MAX_DESCRICAO 100
#define ARQ_PECAS "pecas.bin"
#define ARQ_TEMP "temp.bin"

typedef struct {
    int codigo;
    char nome[MAX_NOME];
    char descricao[MAX_DESCRICAO];
    char setor[30];
    int quantidade;
    float peso; // em kg
    char data_fabricacao[11]; // DD/MM/AAAA
} Peca;

void cadastrar_peca();
void listar_pecas();
void buscar_peca();
void atualizar_peca();
void remover_peca();
void relatorio_setor();
int proximo_codigo();
void salvar_peca(Peca p);
void limpar_buffer();

int main() {
    int opcao;
    
    do {
        system("cls || clear");
        printf("\n=== SISTEMA DE CONTROLE DE PECAS ===\n");
        printf("1. Cadastrar peca\n");
        printf("2. Listar todas as pecas\n");
        printf("3. Buscar peca por codigo\n");
        printf("4. Atualizar peca\n");
        printf("5. Remover peca\n");
        printf("6. Relatorio por setor\n");
        printf("0. Sair\n");
        printf("\nOpcao: ");
        scanf("%d", &opcao);
        limpar_buffer();
        
        switch(opcao) {
            case 1: cadastrar_peca(); break;
            case 2: listar_pecas(); break;
            case 3: buscar_peca(); break;
            case 4: atualizar_peca(); break;
            case 5: remover_peca(); break;
            case 6: relatorio_setor(); break;
            case 0: printf("Saindo do sistema...\n"); break;
            default: printf("Opcao invalida!\n");
        }
        
        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            limpar_buffer();
        }
    } while (opcao != 0);
    
    return 0;
}

void cadastrar_peca() {
    Peca p;
    p.codigo = proximo_codigo();
    
    printf("\n=== CADASTRAR PECA ===\n");
    printf("Codigo: %d\n", p.codigo);
    
    printf("Nome: ");
    fgets(p.nome, MAX_NOME, stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';
    
    printf("Descricao: ");
    fgets(p.descricao, MAX_DESCRICAO, stdin);
    p.descricao[strcspn(p.descricao, "\n")] = '\0';
    
    printf("Setor (Montagem/Usinagem/Acabamento/Embalagem): ");
    fgets(p.setor, 30, stdin);
    p.setor[strcspn(p.setor, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &p.quantidade);
    
    printf("Peso (kg): ");
    scanf("%f", &p.peso);
    limpar_buffer();
    
    printf("Data de fabricacao (DD/MM/AAAA): ");
    fgets(p.data_fabricacao, 11, stdin);
    limpar_buffer();
    
    salvar_peca(p);
    printf("\nPeca cadastrada com sucesso!\n");
}

void listar_pecas() {
    FILE *arquivo = fopen(ARQ_PECAS, "rb");
    if (arquivo == NULL) {
        printf("Nenhuma peca cadastrada!\n");
        return;
    }
    
    printf("\n=== LISTA DE PECAS ===\n");
    printf("COD | NOME               | SETOR        | QTD | PESO  | FABRICACAO\n");
    printf("----|--------------------|--------------|-----|-------|-----------\n");
    
    Peca p;
    while(fread(&p, sizeof(Peca), 1, arquivo)) {
        printf("%-3d | %-18s | %-12s | %3d | %5.2f | %s\n", 
               p.codigo, p.nome, p.setor, p.quantidade, p.peso, p.data_fabricacao);
    }
    
    fclose(arquivo);
}

void buscar_peca() {
    int codigo;
    printf("\nDigite o codigo da peca: ");
    scanf("%d", &codigo);
    limpar_buffer();
    
    FILE *arquivo = fopen(ARQ_PECAS, "rb");
    if (arquivo == NULL) {
        printf("Nenhuma peca cadastrada!\n");
        return;
    }
    
    Peca p;
    bool encontrada = false;
    
    while(fread(&p, sizeof(Peca), 1, arquivo)) {
        if (p.codigo == codigo) {
            encontrada = true;
            printf("\n=== DADOS DA PECA ===\n");
            printf("Codigo: %d\n", p.codigo);
            printf("Nome: %s\n", p.nome);
            printf("Descricao: %s\n", p.descricao);
            printf("Setor: %s\n", p.setor);
            printf("Quantidade: %d\n", p.quantidade);
            printf("Peso: %.2f kg\n", p.peso);
            printf("Data fabricacao: %s\n", p.data_fabricacao);
            break;
        }
    }
    
    if (!encontrada) {
        printf("Peca nao encontrada!\n");
    }
    
    fclose(arquivo);
}

void atualizar_peca() {
    int codigo;
    printf("\nDigite o codigo da peca a atualizar: ");
    scanf("%d", &codigo);
    limpar_buffer();
    
    FILE *arquivo = fopen(ARQ_PECAS, "r+b");
    if (arquivo == NULL) {
        printf("Nenhuma peca cadastrada!\n");
        return;
    }
    
    Peca p;
    bool encontrada = false;
    long posicao = 0;
    
    while(fread(&p, sizeof(Peca), 1, arquivo)) {
        if (p.codigo == codigo) {
            encontrada = true;
            posicao = ftell(arquivo) - sizeof(Peca);
            
            printf("\n=== DADOS ATUAIS ===\n");
            printf("Nome: %s\n", p.nome);
            printf("Descricao: %s\n", p.descricao);
            printf("Setor: %s\n", p.setor);
            printf("Quantidade: %d\n", p.quantidade);
            printf("Peso: %.2f kg\n", p.peso);
            printf("Data fabricacao: %s\n", p.data_fabricacao);
            
            printf("\n=== NOVOS DADOS ===\n");
            printf("Novo nome (atual: %s): ", p.nome);
            fgets(p.nome, MAX_NOME, stdin);
            p.nome[strcspn(p.nome, "\n")] = '\0';
            
            printf("Nova descricao (atual: %s): ", p.descricao);
            fgets(p.descricao, MAX_DESCRICAO, stdin);
            p.descricao[strcspn(p.descricao, "\n")] = '\0';
            
            printf("Novo setor (atual: %s): ", p.setor);
            fgets(p.setor, 30, stdin);
            p.setor[strcspn(p.setor, "\n")] = '\0';
            
            printf("Nova quantidade (atual: %d): ", p.quantidade);
            scanf("%d", &p.quantidade);
            
            printf("Novo peso (atual: %.2f): ", p.peso);
            scanf("%f", &p.peso);
            limpar_buffer();
            
            printf("Nova data fabricacao (atual: %s): ", p.data_fabricacao);
            fgets(p.data_fabricacao, 11, stdin);
            limpar_buffer();
            
            fseek(arquivo, posicao, SEEK_SET);
            fwrite(&p, sizeof(Peca), 1, arquivo);
            printf("\nPeca atualizada com sucesso!\n");
            break;
        }
    }
    
    if (!encontrada) {
        printf("Peca nao encontrada!\n");
    }
    
    fclose(arquivo);
}

void remover_peca() {
    int codigo;
    printf("\nDigite o codigo da peca a remover: ");
    scanf("%d", &codigo);
    limpar_buffer();
    
    FILE *arquivo_original = fopen(ARQ_PECAS, "rb");
    if (arquivo_original == NULL) {
        printf("Nenhuma peca cadastrada!\n");
        return;
    }
    
    FILE *arquivo_temp = fopen(ARQ_TEMP, "wb");
    if (arquivo_temp == NULL) {
        printf("Erro ao criar arquivo temporario!\n");
        fclose(arquivo_original);
        return;
    }
    
    Peca p;
    bool encontrada = false;
    
    while(fread(&p, sizeof(Peca), 1, arquivo_original)) {
        if (p.codigo != codigo) {
            fwrite(&p, sizeof(Peca), 1, arquivo_temp);
        } else {
            encontrada = true;
        }
    }
    
    fclose(arquivo_original);
    fclose(arquivo_temp);
    
    if (encontrada) {
        remove(ARQ_PECAS);
        rename(ARQ_TEMP, ARQ_PECAS);
        printf("Peca removida com sucesso!\n");
    } else {
        remove(ARQ_TEMP);
        printf("Peca nao encontrada!\n");
    }
}

void relatorio_setor() {
    char setor[30];
    printf("\nDigite o setor para o relatorio: ");
    fgets(setor, 30, stdin);
    setor[strcspn(setor, "\n")] = '\0';
    
    FILE *arquivo = fopen(ARQ_PECAS, "rb");
    if (arquivo == NULL) {
        printf("Nenhuma peca cadastrada!\n");
        return;
    }
    
    printf("\n=== RELATORIO DO SETOR %s ===\n", setor);
    printf("COD | NOME               | QTD | PESO  | FABRICACAO\n");
    printf("----|--------------------|-----|-------|-----------\n");
    
    Peca p;
    int total_pecas = 0;
    float peso_total = 0;
    
    while(fread(&p, sizeof(Peca), 1, arquivo)) {
        if (strcmp(p.setor, setor) == 0) {
            printf("%-3d | %-18s | %3d | %5.2f | %s\n", 
                   p.codigo, p.nome, p.quantidade, p.peso, p.data_fabricacao);
            total_pecas += p.quantidade;
            peso_total += p.peso * p.quantidade;
        }
    }
    
    printf("\nTotal de pecas: %d\n", total_pecas);
    printf("Peso total: %.2f kg\n", peso_total);
    
    fclose(arquivo);
}

int proximo_codigo() {
    FILE *arquivo = fopen(ARQ_PECAS, "rb");
    if (arquivo == NULL) return 1;
    
    fseek(arquivo, 0, SEEK_END);
    if (ftell(arquivo) == 0) {
        fclose(arquivo);
        return 1;
    }
    
    fseek(arquivo, -sizeof(Peca), SEEK_END);
    Peca ultima;
    fread(&ultima, sizeof(Peca), 1, arquivo);
    fclose(arquivo);
    
    return ultima.codigo + 1;
}

void salvar_peca(Peca p) {
    FILE *arquivo = fopen(ARQ_PECAS, "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de pecas!\n");
        return;
    }
    
    fwrite(&p, sizeof(Peca), 1, arquivo);
    fclose(arquivo);
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}