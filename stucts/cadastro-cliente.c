#include <stdio.h>
#include <string.h>

#define TAM 100
#define DESC_MAX 50

struct Cliente {
  int codigo;
  char nome[DESC_MAX];
  char cidade[50];
  float renda;
};
void cadastrarClientes(struct Cliente v[], int* qtd) {
  printf("CÓDIGO: ");
  scanf("%d", &v[*qtd].codigo);
  getchar();

  printf("NOME: ");
  fgets(v[*qtd].nome, DESC_MAX, stdin);
  v[*qtd].nome[strcspn(v[*qtd].nome, "\n")] = '\0';

  printf("CIDADE: ");
  fgets(v[*qtd].cidade, DESC_MAX, stdin);
  v[*qtd].cidade[strcspn(v[*qtd].codigo, "\n")] = '\0';

  printf("RENDA: ");
  scanf("%f", &v[*qtd].renda);
  getchar();

  (*qtd)++;
  printf("Foram cadastrados %d clientes!", *qtd);
}
void impimirClientes(struct Cliente v[], int qtd) {
  printf("\n===== CLIENTES CADASTRADOS =====\n");

  for (int i = 0; i < qtd; i++) {
    printf("\nCÓDIGO: %d\n", v[i].codigo);
    printf("NOME %s\n", v[i].nome);
    printf("CIDADE: %s\n", v[i].cidade);
    printf("RENDA: %.2f\n", v[i].renda);
  }
}
int buscaSequencilPorNome(struct Cliente v[], int qtd, char x[]) {
  for (int i = 0; i < qtd; i++) {
    if (strcmp(v[i].nome, x) == 0) {  // comparação de string retorna 0 quando é
                                      // sucesso e -1 quando não encontra
      return i;
    }
  }
  return -1;
}
void imprimirbuscaSequencilPorNome(struct Cliente v[], int qtd) {
  char nome[DESC_MAX];

  printf("Digite o nome do cliente que deseja encontrar: ");
  fgets(nome, DESC_MAX, stdin);
  nome[strcspn(nome, "\n")] = '\0';

  int pos = buscaSequencilPorNome(v, qtd, nome);
  if (pos != -1) {
    printf("\nCÓDIGO: %d\n", v[pos].codigo);
    printf("NOME %s\n", v[pos].nome);
    printf("CIDADE: %s\n", v[pos].cidade);
    printf("RENDA: %.2f\n", v[pos].renda);
  } else {
    printf("Cliente não encontrado!\n");
  }
}
int buscaPorCodigo(struct Cliente v[], int qtd, int codigo) {
  int inicio;
  int fim = qtd - 1;
  int meio;

  while (inicio <= qtd) {
    meio = (inicio + fim) / 2;
  }
  if (v[meio].codigo == codigo) {
    return meio;
  }
  if (v[meio].codigo < codigo) {
    inicio = meio + 1;
  }
  if (v[meio].codigo > codigo) {
    fim = meio - 1;
  }
  return -1;
}
void imprimirBuscaPorCodigo(struct Cliente v[], int qtd) {
  int codigo;

  printf("Digite o código do cliente que deseja encontrar\n");
  scanf("%d", &codigo);
  getchar();

  int pos2 = buscaPorCodigo(v, qtd, codigo);
  if (pos2 != -1) {
    printf("\nCÓDIGO: %d\n", v[pos2].codigo);
    printf("NOME %s\n", v[pos2].nome);
    printf("CIDADE: %s\n", v[pos2].cidade);
    printf("RENDA: %.2f\n", v[pos2].renda);
  } else {
    printf("Cliente não encontrado!\n");
  }
}

int main() { struct Cliente clientes[TAM]; }