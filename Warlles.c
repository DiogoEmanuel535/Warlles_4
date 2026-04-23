#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *arquivo;
    int opcao;

    arquivo = fopen("alunos.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return 1;
    }

    fprintf(arquivo, "1;Ana Silva;2023001;Matematica\n");
    fprintf(arquivo, "2;Bruno Costa;2023002;Fisica\n");
    fprintf(arquivo, "3;Carlos Souza;2023003;Quimica\n");
    fprintf(arquivo, "4;Daniela Lima;2023004;Biologia\n");
    fprintf(arquivo, "5;Eduardo Alves;2023005;Historia\n");
    fprintf(arquivo, "6;Fernanda Rocha;2023006;Geografia\n");
    fprintf(arquivo, "7;Gabriel Martins;2023007;Portugues\n");
    fprintf(arquivo, "8;Helena Barros;2023008;Ingles\n");
    fprintf(arquivo, "9;Igor Nunes;2023009;Artes\n");
    fprintf(arquivo, "10;Juliana Melo;2023010;Educacao Fisica\n");

    fclose(arquivo);

    // Menu
    printf("\n=== MENU ===\n");
    printf("1 - Listar todos os alunos\n");
    printf("2 - Buscar aluno por ID\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    arquivo = fopen("alunos.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    if (opcao == 1) {
        int id;
        char nome[50];
        char matricula[20];
        char disciplina[50];

        printf("\nLista de alunos:\n");

        while (fscanf(arquivo, "%d;%49[^;];%19[^;];%49[^\n]\n",
                      &id, nome, matricula, disciplina) != EOF) {

            printf("\nID: %d\n", id);
            printf("Nome: %s\n", nome);
            printf("Matricula: %s\n", matricula);
            printf("Disciplina: %s\n", disciplina);
        }

    } else if (opcao == 2) {
        int idBusca;
        int id;
        char nome[50];
        char matricula[20];
        char disciplina[50];
        int encontrado = 0;

        printf("\nDigite o ID: ");
        scanf("%d", &idBusca);

        while (fscanf(arquivo, "%d;%49[^;];%19[^;];%49[^\n]\n",
                      &id, nome, matricula, disciplina) != EOF) {

            if (id == idBusca) {
                printf("\nAluno encontrado:\n");
                printf("ID: %d\n", id);
                printf("Nome: %s\n", nome);
                printf("Matricula: %s\n", matricula);
                printf("Disciplina: %s\n", disciplina);
                encontrado = 1;
            }
        }

        if (encontrado == 0) {
            printf("Aluno nao encontrado.\n");
        }

    } else {
        printf("Opcao invalida.\n");
    }

    fclose(arquivo);

    return 0;
}