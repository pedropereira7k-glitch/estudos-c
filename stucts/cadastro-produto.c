#include <stdio.h>
#include <string.h>

#define TAM 100
#define QTD 5
#define DESC_MAX 50

struct Produto {
  int id;
  float preco;
  char descricao[DESC_MAX];
};

void cadastrarProduto(struct Produto v[], int* qtd) {
  printf("\nDigite o ID: ");
  scanf("%d", &v[*qtd].id);
  getchar();

  printf("Digite a descrição: ");
  fgets(v[*qtd].descricao, DESC_MAX, stdin);
  v[*qtd].descricao[strcspn(v[*qtd].descricao, "\n")] = '\0';

  printf("Digite o preço: ");
  scanf("%f", &v[*qtd].preco);
  getchar();
  (*qtd)++;
  printf("Foram preenchidas %d fichas\n", *qtd);
}

void imprimirProdutos(struct Produto v[], int qtd) {
  printf("===== PRODUTOS =====");

  for (int i = 0; i < qtd; i++) {
    printf("\nID: %d\n", v[i].id);
    printf("DESCRIÇÃO: %s\n", v[i].descricao);
    printf("PREÇO: %.2f\n", v[i].preco);
  }
}

int buscaSequencialPorDescricao(struct Produto v[], int qtd, char x[]) {
  for (int i = 0; i < qtd; i++) {
    if (strcmp(v[i].descricao, x) == 0) {
      return i;
    }
  }
  return -1;
}

void imprimirBuscaPorDescricao(struct Produto v[], int qtd) {
  char descricao[50];
  printf("Digite a descrição para buscar: ");
  fgets(descricao, 50, stdin);
  descricao[strcspn(descricao, "\n")] = '\0';

  int pos = buscaSequencialPorDescricao(v, qtd, descricao);
  if (pos != -1) {
    printf("Encontrado na posição %d\n", pos);
    printf("ID: %d\n", v[pos].id);
  } else {
    printf("Produto não encontrado!\n");
  }
}

int buscaPorId(struct Produto v[], int qtd, int x) {
  int inicio = 0;
  int fim = qtd - 1;
  int meio;

  while (inicio <= fim) {
    meio = (inicio + fim) / 2;

    if (v[meio].id == x) {
      return meio;
    }
    if (v[meio].id < x) {
      inicio = meio + 1;
    }
    if (v[meio].id > x) {
      fim = meio - 1;
    }
  }
  return -1;
}

void imprimirBuscaPorId(struct Produto v[], int qtd) {
  int id;

  printf("Digite o id para buscar: ");
  scanf("%d", &id);
  getchar();

  int pos2 = buscaPorId(v, qtd, id);
  if (pos2 != -1) {
    printf("Produto encontrado: %s\n", v[pos2].descricao);
  } else {
    printf("Produto não encontrado!\n");
  }
}

void ordenarPorPreco(struct Produto v[], int qtd) {
  int menor;
  for (int i = 0; i < qtd - 1; i++) {
    menor = i;
    for (int j = i + 1; j < qtd; j++) {
      if (v[j].preco < v[menor].preco) {
        menor = j;
      }
    }
    if (menor != i) {
      struct Produto aux;
      aux = v[i];
      v[i] = v[menor];
      v[menor] = aux;
    }
  }
}
void ordenarPorDescricao(struct Produto v[], int qtd) {
  int menor = 0;
  for (int i = 0; i < qtd - 1; i++) {
    menor = i;
    for (int j = i + 1; j < qtd; j++) {
      if (strcmp(v[j].descricao, v[menor].descricao) < 0) {
        menor = j;
      }
    }
    if (menor != i) {
      struct Produto aux;
      aux = v[i];
      v[i] = v[menor];
      v[menor] = aux;
    }
  }
}
void ordenarPorId(struct Produto v[], int qtd) {
  int menor;
  for (int i = 0; i < qtd - 1; i++) {
    menor = i;
    for (int j = i + 1; j < qtd; j++) {
      if (v[j].id < v[menor].id) {
        menor = j;
      }
    }
    if (menor != i) {
      struct Produto aux;
      aux = v[i];
      v[i] = v[menor];
      v[menor] = aux;
    }
  }
}

int produtoMaisCaro(struct Produto v[], int qtd) {
  int maisCaro = 0;

  for (int i = 0; i < qtd; i++) {
    if (v[i].preco > v[maisCaro].preco) {
      maisCaro = i;
    }
  }
  return maisCaro;
}

int produtoMaisBarato(struct Produto v[], int qtd) {
  int maisBarato = 0;
  for (int i = 0; i < qtd; i++) {
    if (v[i].preco < v[maisBarato].preco) {
      maisBarato = i;
    }
  }
  return maisBarato;
}

void imprimirMaisCaroMaiSBarato(struct Produto v[], int qtd) {
  int maisCaro = produtoMaisCaro(v, qtd);
  int maisBarato = produtoMaisBarato(v, qtd);

  printf("\n===== PRODUTO MAIS CARO =====\n");

  printf("ID: %d\n", v[maisCaro].id);
  printf("DESCRIÇÃO: %s\n", v[maisCaro].descricao);
  printf("Preço: %.2f", v[maisCaro].preco);

  printf("\n===== PRODUTO MAIS BARATO =====\n");

  printf("ID: %d\n", v[maisBarato].id);
  printf("DESCRIÇÃO: %s\n", v[maisBarato].descricao);
  printf("PREÇO: %.2f", v[maisBarato].preco);
}

int main() {
  struct Produto produtos[TAM];

  int opcao;
  int qtd = 0;
  do {
    printf("\n===== MENU =====\n");
    printf("1 - Cadastrar produtos\n");
    printf("2 - Imprimir produtos\n");
    printf("3 - Ordenar por preco\n");
    printf("4 - Ordenar por descricao\n");
    printf("5 - Ordenar por ID\n");
    printf("6 - Buscar por descricao\n");
    printf("7 - Buscar por ID\n");
    printf("8 - Mostrar mais caro e mais barato\n");
    printf("0 - Sair\n");

    printf("Opcao: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
      case 1:
        cadastrarProduto(produtos, &qtd);
        break;

      case 2:
        if (qtd == 0) {
          printf("Nenhum produto cadatrado!\n");
        }
        imprimirProdutos(produtos, qtd);
        break;

      case 3:
        if (qtd == 0) {
          printf("Nenhum produto encontrado!\n");
        }
        ordenarPorPreco(produtos, qtd);
        imprimirProdutos(produtos, qtd);
        break;

      case 4:
        if (qtd == 0) {
          printf("Nenhum produto cadastrado!\n");
        }
        ordenarPorDescricao(produtos, qtd);
        imprimirProdutos(produtos, qtd);
        break;

      case 5:
        if (qtd == 0) {
          printf("Nenhum produto cadastrado!\n");
        }
        ordenarPorId(produtos, qtd);
        imprimirProdutos(produtos, qtd);
        break;

      case 6:
        if (qtd == 0) {
          printf("Nenhum produto cadastrado!\n");
        }
        imprimirBuscaPorDescricao(produtos, qtd);
        break;

      case 7:
        if (qtd == 0) {
          printf("Nenhum produto cadastrado!\n");
        }
        ordenarPorId(produtos, qtd);
        imprimirBuscaPorId(produtos, qtd);
        break;

      case 8:
        if (qtd == 0) {
          printf("Nenhum produto cadastrado!\n");
        }
        imprimirMaisCaroMaiSBarato(produtos, qtd);
        break;

      case 0:
        printf("Programa encerrado!\n");
        break;

      default:
        printf("Opção inválida!\n");
        break;
    }

  } while (opcao != 0);
}