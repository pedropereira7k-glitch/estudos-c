#include <stdio.h>
#include <string.h>

#define TAM 100
#define DESC_MAX 50

struct Aluno {
  int matricula;
  char nome[DESC_MAX];
  float nota1, nota2;
};

int buscaPormatricula(struct Aluno v[], int qtd, int x) {
  int inicio = 0;
  int fim = qtd - 1;
  int meio;

  while (inicio <= fim) {
    meio = (inicio + fim) / 2;

    if (v[meio].matricula == x) {
      return meio;
    }
    if (v[meio].matricula < x) {
      inicio = meio + 1;
    }
    if (v[meio].matricula > x) {
      fim = meio - 1;
    }
  }
  return -1;
}

float calcularMedia(float nota1, float nota2) { return (nota1 + nota2) / 2; }

void cadastrarAlunos(struct Aluno v[], int* qtd) {
  int matricula;
  printf("Matrícula: ");
  scanf("%d", &matricula);
  getchar();

  int pos = buscaPormatricula(v, *qtd, matricula);
  if (pos != -1) {
    printf("Matrícula já cadastrada!\n");
    return;
  }
  v[*qtd].matricula = matricula;
  printf("Nome: ");
  fgets(v[*qtd].nome, DESC_MAX, stdin);
  v[*qtd].nome[strcspn(v[*qtd].nome, "\n")] = '\0';

  printf("Nota 1: ");
  scanf("%f", &v[*qtd].nota1);
  getchar();

  printf("Nota 2: ");
  scanf("%f", &v[*qtd].nota2);
  getchar();

  (*qtd)++;
}
void imprimirBuscaPorMatricula(struct Aluno v[], int qtd) {
  int matricula;

  printf("Digite a matrícula: ");
  scanf("%d", &matricula);
  getchar();

  int pos = buscaPormatricula(v, qtd, matricula);
  if (pos != -1) {
    printf("Nome: %s\n", v[pos].nome);
    printf("Nota 1: %.2f\n", v[pos].nota1);
    printf("Nota 2: %.2f\n", v[pos].nota2);
    printf("Média: %.2f\n", calcularMedia(v[pos].nota1, v[pos].nota2));
  } else {
    printf("Aluno não encontrado!\n");
  }
}

void imprimirAlunos(struct Aluno v[], int qtd) {
  printf("\n===== ALUNOS =====\n");

  for (int i = 0; i < qtd; i++) {
    float media = calcularMedia(v[i].nota1, v[i].nota2);
    printf("\nNOME: %s\n", v[i].nome);
    printf("MATRÍCULA: %d\n", v[i].matricula);
    printf("NOTA 1: %.2f\n", v[i].nota1);
    printf("NOTA 2: %.2f\n", v[i].nota2);
    printf("Média: %.2f\n", media);
    if (media >= 7) {
      printf("Aluno aprovado por média!\n");
    } else {
      printf("Aluno reprovado por média!\n");
    }
  }
}

void aprovadoReprovado(struct Aluno v[], int qtd) {
  printf("\n===== APROVADOS =====\n");
  for (int i = 0; i < qtd; i++) {
    float media = calcularMedia(v[i].nota1, v[i].nota2);
    if (media >= 7) {
      printf("\n%s - %.2f\n", v[i].nome, media);
    }
  }
  printf("\n===== REPROVADOS =====\n");
  for (int i = 0; i < qtd; i++) {
    float media = calcularMedia(v[i].nota1, v[i].nota2);
    if (media < 7) {
      printf("\n%s - %.2f\n", v[i].nome, media);
    }
  }
}

void ordenarPorNome(struct Aluno v[], int qtd) {
  int menor = 0;

  for (int i = 0; i < qtd - 1; i++) {
    menor = i;
    for (int j = i + 1; j < qtd; j++) {
      if (strcmp(v[j].nome, v[menor].nome) < 0) {
        menor = j;
      }
    }
    if (menor != i) {
      struct Aluno aux;
      aux = v[i];
      v[i] = v[menor];
      v[menor] = aux;
    }
  }
}
int main() {
  struct Aluno alunos[TAM];

  int opcao;
  int qtd = 0;

  do {
    printf("\n===== MENU =====\n");
    printf("1 - Cadastrar aluno\n");
    printf("2 - Listar alunos\n");
    printf("3 - Buscar por matrícula\n");
    printf("4 - Aprovados e Reprovados\n");
    printf("5 - Ordenar por nome\n");
    printf("0 - Sair\n");

    printf("Opção: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
      case 1:
        cadastrarAlunos(alunos, &qtd);
        break;

      case 2:
        imprimirAlunos(alunos, qtd);
        break;

      case 3:
        imprimirBuscaPorMatricula(alunos, qtd);
        break;

      case 4:
        aprovadoReprovado(alunos, qtd);
        break;
      case 5:
        ordenarPorNome(alunos, qtd);
        imprimirAlunos(alunos, qtd);
        break;

      case 0:
        printf("Programa encerrado!\n");
        break;

      default:
        printf("Opção inválida\n");
    }
  } while (opcao != 0);
}