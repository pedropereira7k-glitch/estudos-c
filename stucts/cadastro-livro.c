#include <stdio.h>
#include <string.h>

#define TAM 100
#define DESC_MAX 50

struct Livro {
  int codigo;
  char titulo[DESC_MAX];
  char autor[DESC_MAX];
  float preco;
  int qtdEstoque;
};
// função de busca por título
int buscaSequencialPorTitulo(struct Livro v[], int qtd, char x[]) {
  for (int i = 0; i < qtd; i++) {
    if (strcmp(v[i].titulo, x) == 0) {
      return i;
    }
  }
  return -1;
}
// função de busca por código
int buscaBinariaPorCodigo(struct Livro v[], int qtd, int x) {
  int inicio = 0;
  int fim = qtd - 1;
  int meio;

  while (inicio <= fim) {
    meio = (inicio + fim) / 2;

    if (v[meio].codigo == x) {
      return meio;
    }

    if (v[meio].codigo < x) {
      inicio = meio + 1;
    }

    if (v[meio].codigo > x) {
      fim = meio - 1;
    }
  }
  return -1;
}
void cadastrarLivro(struct Livro v[], int* qtd) {
  int codigo;

  printf("Código: ");
  scanf("%d", &codigo);
  getchar();

  int pos = buscaBinariaPorCodigo(v, *qtd, codigo);
  if (pos != -1) {
    printf("O livro já possui cadastro!\n");
    return;
  }

  v[*qtd].codigo = codigo;

  printf("Título: ");
  fgets(v[*qtd].titulo, DESC_MAX, stdin);
  v[*qtd].titulo[strcspn(v[*qtd].titulo, "\n")] = '\0';

  printf("Autor: ");
  fgets(v[*qtd].autor, DESC_MAX, stdin);
  v[*qtd].autor[strcspn(v[*qtd].autor, "\n")] = '\0';

  printf("Preço: ");
  scanf("%f", &v[*qtd].preco);
  getchar();

  printf("Quantos no estoque: ");
  scanf("%d", &v[*qtd].qtdEstoque);
  getchar();

  (*qtd)++;

  printf("Foram cadastrados %d livro(s)!\n", *qtd);
}
void imprimirBuscaPorTitulo(struct Livro v[], int qtd) {
  char titulo[DESC_MAX];

  printf("Digite o título do livro que deseja encontrar: ");
  fgets(titulo, DESC_MAX, stdin);
  titulo[strcspn(titulo, "\n")] = '\0';

  int pos = buscaSequencialPorTitulo(v, qtd, titulo);

  if (pos != -1) {
    printf("\nCÓDIGO: %d\n", v[pos].codigo);
    printf("TÍTULO: %s\n", v[pos].titulo);
    printf("AUTOR: %s\n", v[pos].autor);
    printf("PREÇO: %.2f\n", v[pos].preco);
    printf("QUANTIDADE NO ESTOQUE: %d\n", v[pos].qtdEstoque);
  } else {
    printf("Livro não encontrado!\n");
  }
}
void imprimirBuscaPorCodigo(struct Livro v[], int qtd) {
  int codigo;

  printf("Digite o código do livro que deseja encontrar: ");
  scanf("%d", &codigo);
  getchar();

  int pos2 = buscaBinariaPorCodigo(v, qtd, codigo);

  if (pos2 != -1) {
    printf("CÓDIGO: %d\n", v[pos2].codigo);
    printf("\nTÍTULO: %s\n", v[pos2].titulo);
    printf("AUTOR: %s\n", v[pos2].autor);
    printf("PREÇO: %.2f\n", v[pos2].preco);
    printf("QUANTIDADE NO ESTOQUE: %d\n", v[pos2].qtdEstoque);
  } else {
    printf("Livro não encontrado!\n");
  }
}
void imprimirLivros(struct Livro v[], int qtd) {
  printf("\n===== LIVROS =====\n");

  for (int i = 0; i < qtd; i++) {
    printf("\nCÓDIGO: %d\n", v[i].codigo);
    printf("TÍTULO: %s\n", v[i].titulo);
    printf("AUTOR: %s\n", v[i].autor);
    printf("PREÇO: %.2f\n", v[i].preco);
    printf("QUANTIDADE NO ESTOQUE: %d\n", v[i].qtdEstoque);
  }
}
void livrosEmFalta(struct Livro v[], int qtd) {
  printf("\n===== LIVROS EM FALTA =====\n");

  for (int i = 0; i < qtd; i++) {
    if (v[i].qtdEstoque == 0) {
      printf("\nCÓDIGO: %d\n", v[i].codigo);
      printf("TÍTULO: %s\n", v[i].titulo);
      printf("AUTOR: %s\n", v[i].autor);
      printf("PREÇO: %.2f\n", v[i].preco);
      printf("QUANTIDADE NO ESTOQUE: %d\n", v[i].qtdEstoque);
    }
  }
}
void ordenarPorPreco(struct Livro v[], int qtd) {
  int menor;

  for (int i = 0; i < qtd - 1; i++) {
    menor = i;
    for (int j = i + 1; j < qtd; j++) {
      if (v[j].preco < v[menor].preco) {
        menor = j;
      }
    }
    if (menor != i) {
      struct Livro aux = v[i];

      v[i] = v[menor];
      v[menor] = aux;
    }
  }
}
int main() {
  struct Livro livros[TAM];

  int qtd = 0;
  int opcao;

  do {
    printf("\n===== MENU =====\n");
    printf("1 - Cadastrar livro\n");
    printf("2 - Listar livro\n");
    printf("3 - Buscar por título\n");
    printf("4 - Buscar por código\n");
    printf("5 - Mostrar livro(s) em falta\n");
    printf("6 - Ordenar por preço\n");
    printf("0 - Sair\n");

    printf("Opção: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
      case 1:
        cadastrarLivro(livros, &qtd);
        break;

      case 2:
        imprimirLivros(livros, qtd);
        break;

      case 3:
        imprimirBuscaPorTitulo(livros, qtd);
        break;

      case 4:
        imprimirBuscaPorCodigo(livros, qtd);
        break;

      case 5:
        livrosEmFalta(livros, qtd);
        break;

      case 6:
        ordenarPorPreco(livros, qtd);
        imprimirLivros(livros, qtd);
        break;

      case 0:
        printf("Programa encerrado!\n");
        break;

      default:
        printf("Opção inválida!\n");
    }
  } while (opcao != 0);
}