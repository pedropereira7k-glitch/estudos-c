#include <stdio.h>
#include <string.h>

#define TAM 100
#define DESC_MAX 50

struct Veiculo {
  int placa;
  char modelo[DESC_MAX];
  char proprietario[DESC_MAX];
  int ano;
  float valor;
};
// função de busca por modelo
int buscaSequencialPorModelo(struct Veiculo v[], int qtd, char x[]) {
  for (int i = 0; i < qtd; i++) {
    if (strcmp(v[i].modelo, x) == 0) {
      return i;
    }
  }
  return -1;
}
int buscaSequencialPorPlaca(struct Veiculo v[], int qtd, int placa) {
  for (int i = 0; i < qtd; i++) {
    if (v[i].placa == placa) {
      return i;
    }
  }
  return -1;
}
// função de busca binária por placa
int buscaBinariaPorPlaca(struct Veiculo v[], int qtd, int x) {
  int inicio = 0;
  int fim = qtd - 1;
  int meio;

  while (inicio <= fim) {
    meio = (inicio + fim) / 2;
    if (v[meio].placa == x) {
      return meio;
    }
    if (v[meio].placa < x) {
      inicio = meio + 1;
    }
    if (v[meio].placa > x) {
      fim = meio - 1;
    }
  }
  return -1;
}
// função de cadastro de carros
void cadastrarCarros(struct Veiculo v[], int* qtd) {
  int placa;
  printf("Digite o a placa do carro: ");
  scanf("%d", &placa);
  getchar();

  int pos = buscaSequencialPorPlaca(v, *qtd, placa);
  if (pos != -1) {
    printf("Carro já cadastrado!\n");
    return;
  }
  v[*qtd].placa = placa;

  printf("MODELO: ");
  fgets(v[*qtd].modelo, DESC_MAX, stdin);
  v[*qtd].modelo[strcspn(v[*qtd].modelo, "\n")] = '\0';

  printf("PROPRIETÁRIO: ");
  fgets(v[*qtd].proprietario, DESC_MAX, stdin);
  v[*qtd].proprietario[strcspn(v[*qtd].proprietario, "\n")] = '\0';

  printf("ANO: ");
  scanf("%d", &v[*qtd].ano);
  getchar();

  printf("VALOR: ");
  scanf("%f", &v[*qtd].valor);
  getchar();

  (*qtd)++;
  printf("Foram cadastrados %d carros!\n", *qtd);
}
// função para imprimir veiculos
void imprimirVeiculos(struct Veiculo v[], int qtd) {
  printf("\n===== INFORMÇÕES DOS VEÍCULOS =====\n");

  for (int i = 0; i < qtd; i++) {
    printf("\nPLACA: %d\n", v[i].placa);
    printf("MODELO: %s\n", v[i].modelo);
    printf("PROPRIETÁRIO: %s\n", v[i].proprietario);
    printf("ANO: %d\n", v[i].ano);
    printf("VALOR: %.2f\n", v[i].valor);
  }
}
void imprimirbBuscaPorModelo(struct Veiculo v[], int qtd) {
  char modelo[DESC_MAX];

  printf("Digite o modelo do carro que deseja encontrar: ");
  fgets(modelo, DESC_MAX, stdin);
  modelo[strcspn(modelo, "\n")] = '\0';

  int pos = buscaSequencialPorModelo(v, qtd, modelo);
  if (pos != -1) {
    printf("\nPLACA: %d\n", v[pos].placa);
    printf("MODELO: %s\n", v[pos].modelo);
    printf("PROPRIETÁRIO: %s\n", v[pos].proprietario);
    printf("ANO: %d\n", v[pos].ano);
    printf("VALOR: %.2f\n", v[pos].valor);
  } else {
    printf("Veículo não encontrado!\n");
  }
}
void imprimirBuscaPorPlaca(struct Veiculo v[], int qtd) {
  int placa;

  printf("Digite a placa do carro que deseja encontrar: ");
  scanf("%d", &placa);
  getchar();

  int pos2 = buscaSequencialPorPlaca(v, qtd, placa);

  if (pos2 != -1) {
    printf("\nPLACA: %d\n", v[pos2].placa);
    printf("MODELO: %s\n", v[pos2].modelo);
    printf("PROPRIETÁRIO: %s\n", v[pos2].proprietario);
    printf("ANO: %d\n", v[pos2].ano);
    printf("VALOR: %.2f\n", v[pos2].valor);
  } else {
    printf("Veículo não encontrado!\n");
  }
}
// função que informa os veículos abaixo do ano minímo
void veiculosAnterioresA(struct Veiculo v[], int qtd, int ano) {
  printf("\n===== VEÍCULOS COM ANO MENOR QUE O INFORMADO =====\n");

  for (int i = 0; i < qtd; i++) {
    if (v[i].ano < ano) {
      printf("\nPLACA: %d\n", v[i].placa);
      printf("MODELO: %s\n", v[i].modelo);
      printf("PROPRIETÁRIO: %s\n", v[i].proprietario);
      printf("ANO: %d\n", v[i].ano);
      printf("VALOR: %.2f\n", v[i].valor);
    }
  }
}
// float calcular média dos valores dos carros informados
float calcularMediaValor(struct Veiculo v[], int qtd) {
  float soma = 0;

  for (int i = 0; i < qtd; i++) {
    soma += v[i].valor;
  }
  if (qtd == 0) {
    return 0;
  } else {
    return soma / qtd;
  }
}
void imprimirMedia(struct Veiculo v[], int qtd) {
  printf("Média valor: %.2f", calcularMediaValor(v, qtd));
}
void imprimirAcimaMediaValor(struct Veiculo v[], int qtd) {
  float media = calcularMediaValor(v, qtd);

  printf("\n===== VEÍCULOS QUE ESTÃO ACIMA DA MÉDIA =====\n");

  for (int i = 0; i < qtd; i++) {
    if (v[i].valor > media) {
      printf("\nPLACA: %d\n", v[i].placa);
      printf("MODELO: %s\n", v[i].modelo);
      printf("PROPRIETÁRIO: %s\n", v[i].proprietario);
      printf("ANO: %d\n", v[i].ano);
      printf("VALOR: %.2f\n", v[i].valor);
    }
  }
}
void ordenarPorAno(struct Veiculo v[], int qtd) {
  int menor;

  for (int i = 0; i < qtd - 1; i++) {
    menor = i;
    for (int j = i + 1; j < qtd; j++) {
      if (v[j].ano < v[menor].ano) {
        menor = j;
      }
    }
    if (menor != i) {
      struct Veiculo aux = v[i];
      v[i] = v[menor];
      v[menor] = aux;
    }
  }
}
void ordenarPorValor(struct Veiculo v[], int qtd) {
  int menor;

  for (int i = 0; i < qtd - 1; i++) {
    menor = i;
    for (int j = i + 1; j < qtd; j++) {
      if (v[j].valor < v[menor].valor) {
        menor = j;
      }
    }
    if (menor != i) {
      struct Veiculo aux = v[i];
      v[i] = v[menor];
      v[menor] = aux;
    }
  }
}
void aplicarDepreciacao(struct Veiculo v[], int qtd, int percentual) {
  for (int i = 0; i < qtd; i++) {
    float valorAntigo = v[i].valor;
    float depreciacao = valorAntigo * percentual / 100;

    printf("\nModelo: %s\n", v[i].modelo);
    printf("Valor antigo: %.2f\n", valorAntigo);
    printf("Deprecição: %.2f\n", depreciacao);

    v[i].valor = valorAntigo - depreciacao;

    printf("Novo valor: %.2f\n", v[i].valor);
  }
}
int main() {
  struct Veiculo veiculos[TAM];

  int qtd = 0;
  int opcao;
  float valor;
  int percentual;
  int ano;
  do {
    printf("\n===== Menu =====\n");
    printf("1 - Cadastrar veículo\n");
    printf("2 - Listar todos os veículos\n");
    printf("3 - Buscar por modelo\n");
    printf("4 - Buscar por placa\n");
    printf("5 - Veículos anteriores a um ano\n");
    printf("6 - Média de valor dos veículos\n");
    printf("7 - Veículos acima da média de valor\n");
    printf("8 - Ordenar por ano\n");
    printf("9 - Ordenar por valor\n");
    printf("10 - Aplicar depreciação\n");
    printf("0 - Sair\n");

    printf("Opção: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
      case 1:
        cadastrarCarros(veiculos, &qtd);
        break;

      case 2:
        imprimirVeiculos(veiculos, qtd);
        break;

      case 3:
        imprimirbBuscaPorModelo(veiculos, qtd);
        break;

      case 4:
        imprimirBuscaPorPlaca(veiculos, qtd);
        break;

      case 5:
        printf("Digite o ano mínimo: ");
        scanf("%d", &ano);
        getchar();
        veiculosAnterioresA(veiculos, qtd, ano);
        break;

      case 6:
        imprimirMedia(veiculos, qtd);
        break;

      case 7:
        imprimirAcimaMediaValor(veiculos, qtd);
        break;

      case 8:
        ordenarPorAno(veiculos, qtd);
        imprimirVeiculos(veiculos, qtd);
        break;

      case 9:
        ordenarPorValor(veiculos, qtd);
        imprimirVeiculos(veiculos, qtd);
        break;

      case 10:
        printf("Digite o percentual: ");
        scanf("%d", &percentual);
        getchar();
        aplicarDepreciacao(veiculos, qtd, percentual);
        break;

      case 0:
        printf("PROGRAMA ENCERRADO!\n");
        break;

      default:
        printf("OPÇÃO INVÁLIDA!\n");
    }
  } while (opcao != 0);
}