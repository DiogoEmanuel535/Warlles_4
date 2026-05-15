#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char bancoPrincipal[50];
char bancoDados[50];

void criarBanco();
void listarBancos();
void adicionarRegistro();
void listarRegistros();
void buscarRegistro();
void editarRegistro();
void deletarBancos(); 

int main() {

    int opcao;

    do {

        printf("\n==============================\n");
        printf("       ESCOLHA UMA OPÇÃO      ");
        printf("\n==============================\n");
        printf("1 - Criar bancos\n");
        printf("2 - Listar bancos\n");
        printf("3 - Adicionar registro\n");
        printf("4 - Listar registros\n");
        printf("5 - Buscar registro\n");
        printf("6 - Editar registro\n");
        printf("0 - Sair\n");

        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:
                criarBanco();
                break;

            case 2:
                listarBancos();
                break;

            case 3:
                adicionarRegistro();
                break;

            case 4:
                listarRegistros();
                break;

            case 5:
                buscarRegistro();
                break;

            case 6:
                editarRegistro();
                break;

            case 0:
                printf("\nEncerrando sistema...\n");
                deletarBancos(); 
                break;

            default:
                printf("\nOpcao invalida.\n");
        }

    } while(opcao != 0);

    return 0;
}

void criarBanco() {

    FILE *arquivo1;
    FILE *arquivo2;

    printf("Nome do banco principal: ");
    scanf("%49s", bancoPrincipal);

    printf("Nome do banco de dados: ");
    scanf("%49s", bancoDados);

    strcat(bancoPrincipal, ".txt");
    strcat(bancoDados, ".txt");

    arquivo1 = fopen(bancoPrincipal, "a");
    arquivo2 = fopen(bancoDados, "a");

    if(arquivo1 == NULL || arquivo2 == NULL) {
        printf("\nErro ao criar bancos.\n");
        return;
    }

    fclose(arquivo1);
    fclose(arquivo2);

    printf("\nBancos criados com sucesso.\n");
}

void listarBancos() {

    printf("\n--- Bancos Atuais ---\n");
    printf("Banco principal: %s\n", bancoPrincipal);
    printf("Banco de dados: %s\n", bancoDados);
}

void adicionarRegistro() {

    FILE *principal;
    FILE *dados;

    int id;
    char campo1[50];
    char campo2[50];
    char campo3[50];

    if(strlen(bancoPrincipal) == 0 || strlen(bancoDados) == 0) {
        printf("\nVocê precisa criar os bancos primeiro (Opção 1)!\n");
        return;
    }

    principal = fopen(bancoPrincipal, "a");
    dados = fopen(bancoDados, "a");

    if(principal == NULL || dados == NULL) {
        printf("\nErro ao abrir bancos.\n");
        return;
    }

    printf("Digite o ID: ");
    scanf("%d", &id);

    getchar(); 
    
    printf("Digite o primeiro dado: ");
    fgets(campo1, 50, stdin);
    campo1[strcspn(campo1, "\n")] = '\0'; 

    printf("Digite o segundo dado: ");
    fgets(campo2, 50, stdin);
    campo2[strcspn(campo2, "\n")] = '\0'; 

    printf("Digite o terceiro dado: ");
    fgets(campo3, 50, stdin);
    campo3[strcspn(campo3, "\n")] = '\0'; 
    
    fprintf(principal, "%d;%s;%s;%s\n", id, campo1, campo2, campo3);
    fprintf(dados, "%d;%s;%s;%s\n", id, campo1, campo2, campo3);

    fclose(principal);
    fclose(dados);

    printf("\nRegistro salvo com sucesso.\n");
}

void listarRegistros() {

    FILE *arquivo;

    int id;
    char campo1[50];
    char campo2[50];
    char campo3[50];

    arquivo = fopen(bancoDados, "r");

    if(arquivo == NULL) {
        printf("\nErro ao abrir banco ou banco inexistente.\n");
        return;
    }

    printf("\n--- Registros ---\n");
    while(fscanf(arquivo, "%d;%49[^;];%49[^;];%49[^\n]\n", &id, campo1, campo2, campo3) != EOF) {

        printf("ID: %d | Campo 1: %s | Campo 2: %s | Campo 3: %s\n", id, campo1, campo2, campo3);
    }

    fclose(arquivo);
}

void buscarRegistro() {

    FILE *arquivo;

    int idBusca;
    int id;
    int encontrado = 0;

    char campo1[50];
    char campo2[50];
    char campo3[50];

    arquivo = fopen(bancoDados, "r");

    if(arquivo == NULL) {
        printf("\nErro ao abrir banco.\n");
        return;
    }

    printf("Digite o ID para busca: ");
    scanf("%d", &idBusca);

    while(fscanf(arquivo, "%d;%49[^;];%49[^;];%49[^\n]\n", &id, campo1, campo2, campo3) != EOF) {

        if(id == idBusca) {

            printf("\n--- Registro encontrado ---\n");
            printf("ID: %d\n", id);
            printf("Campo 1: %s\n", campo1);
            printf("Campo 2: %s\n", campo2);
            printf("Campo 3: %s\n", campo3);

            encontrado = 1;
            break; 
        }
    }

    if(encontrado == 0) {
        printf("\nRegistro nao encontrado.\n");
    }

    fclose(arquivo);
}

void editarRegistro() {

    FILE *arquivo;
    FILE *temp;

    int idBusca;
    int id;
    int encontrado = 0;

    char campo1[50];
    char campo2[50];
    char campo3[50];

    char novo1[50];
    char novo2[50];
    char novo3[50];

    arquivo = fopen(bancoDados, "r");
    temp = fopen("temp.txt", "w");

    if(arquivo == NULL || temp == NULL) {
        printf("\nErro ao abrir arquivos.\n");
        return;
    }

    printf("Digite o ID para editar: ");
    scanf("%d", &idBusca);

    getchar();

    
    while(fscanf(arquivo, "%d;%49[^;];%49[^;];%49[^\n]\n", &id, campo1, campo2, campo3) != EOF) {

        if(id == idBusca) {

            encontrado = 1;

            printf("Novo campo 1: ");
            fgets(novo1, 50, stdin);
            novo1[strcspn(novo1, "\n")] = '\0';

            printf("Novo campo 2: ");
            fgets(novo2, 50, stdin);
            novo2[strcspn(novo2, "\n")] = '\0';

            printf("Novo campo 3: ");
            fgets(novo3, 50, stdin);
            novo3[strcspn(novo3, "\n")] = '\0';

     
            fprintf(temp, "%d;%s;%s;%s\n", id, novo1, novo2, novo3);

        } else {
           
            fprintf(temp, "%d;%s;%s;%s\n", id, campo1, campo2, campo3);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove(bancoDados);
    rename("temp.txt", bancoDados);

    if(encontrado == 1) {
        printf("\nRegistro editado com sucesso.\n");
    } else {
        printf("\nRegistro nao encontrado.\n");
        remove("temp.txt"); 
    }
}

void deletarBancos() {
    int removido1 = 0, removido2 = 0;

    if(strlen(bancoPrincipal) > 0) {
        removido1 = remove(bancoPrincipal);
    }
    
    if(strlen(bancoDados) > 0) {
        removido2 = remove(bancoDados);
    }

    if (removido1 == 0 || removido2 == 0) {
        printf("Arquivos de banco de dados apagados com sucesso.\n");
    }
}
 