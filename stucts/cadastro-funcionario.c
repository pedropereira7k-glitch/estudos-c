#include <stdio.h>
#include <string.h>

#define TAM 100
#define DESC_MAX 50

struct Funcionario {
  int matricula;
  char nome[DESC_MAX];
  char cargo[DESC_MAX];
  float salario;
};
// função que busca nome
int buscaSequencialPorNome(struct Funcionario v[], int qtd, char x[]) {
  for (int i = 0; i < qtd; i++) {
    if (strcmp(v[i].nome, x) == 0) {
      return i;
    }
  }
  return -1;
}
// fução que matricula
int buscaBinariaPorMatricula(struct Funcionario v[], int qtd, int x) {
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
// função para cadastrar funcionários
void cadastrarFuncionario(struct Funcionario v[], int* qtd) {
  int matricula;

  printf("Digite a matrícula: ");
  scanf("%d", &matricula);
  getchar();

  int pos = buscaBinariaPorMatricula(v, *qtd, matricula);
  if (pos != -1) {
    printf("O funcionário já está cadastrado!\n");
    return;
  }
  v[*qtd].matricula = matricula;

  printf("NOME: ");
  fgets(v[*qtd].nome, DESC_MAX, stdin);
  v[*qtd].nome[strcspn(v[*qtd].nome, "\n")] = '\0';

  printf("CARGO: ");
  fgets(v[*qtd].cargo, DESC_MAX, stdin);
  v[*qtd].cargo[strcspn(v[*qtd].cargo, "\n")] = '\0';

  printf("SALÁRIO: ");
  scanf("%f", &v[*qtd].salario);
  getchar();

  (*qtd)++;
  printf("Foram cadastrados %d funcionários(s)!", *qtd);
}
// função para imprimir funcinários
void imprimirFuncionarios(struct Funcionario v[], int qtd) {
  printf("\n===== INFORMAÇÕES DOS FUNCIONÁRIOS =====\n");

  for (int i = 0; i < qtd; i++) {
    printf("\nMATRÍCULA: %d\n", v[i].matricula);
    printf("NOME: %s\n", v[i].nome);
    printf("CARGO: %s\n", v[i].cargo);
    printf("SALÁRIO: %.2f\n", v[i].salario);
  }
}
// função imprimir busca por nome
void imprimirBuscaPorNome(struct Funcionario v[], int qtd) {
  char nome[DESC_MAX];

  printf("Digite o nome do funcionário que deseja encontrar: ");
  fgets(nome, DESC_MAX, stdin);
  nome[strcspn(nome, "\n")] = '\0';

  int pos = buscaSequencialPorNome(v, qtd, nome);

  if (pos != -1) {
    printf("\nMATRÍCULA: %d\n", v[pos].matricula);
    printf("NOME: %s\n", v[pos].nome);
    printf("CARGO: %s\n", v[pos].cargo);
    printf("SALÁRIO: %.2f\n", v[pos].salario);
  } else {
    printf("Funcinário não encontrado!\n");
  }
}
// função que imprime busca por matrícula
void imprimirBuscaPorMatricula(struct Funcionario v[], int qtd) {
  int matricula;

  printf("Digite a matrícula do funcionário que deseja encontrar: ");
  scanf("%d", &matricula);

  int pos2 = buscaBinariaPorMatricula(v, qtd, matricula);

  if (pos2 != -1) {
    printf("\nMATRÍCULA: %d\n", v[pos2].matricula);
    printf("NOME: %s\n", v[pos2].nome);
    printf("CARGO: %s\n", v[pos2].cargo);
    printf("SALÁRIO: %.2f\n", v[pos2].salario);
  } else {
    printf("Funcionário não encontrado!\n");
  }
}
// função que mostra funcionário com salários acima do valor
void funcionariosComSalariosAcima(struct Funcionario v[], int qtd,
                                  float valor) {
  printf("\n===== FUNCINÁRIOS QUE RECEBEM ACIMA DO VALOR MÍNIMO =====\n");

  for (int i = 0; i < qtd; i++) {
    if (v[i].salario > valor) {
      printf("\nMATRÍCULA: %d\n", v[i].matricula);
      printf("NOME: %s\n", v[i].nome);
      printf("CARGO: %s\n", v[i].cargo);
      printf("SALÁRIO: %.2f\n", v[i].salario);
    }
  }
}

// função que calcula média salarial
float calcularMediaSalarial(struct Funcionario v[], int qtd) {
  float soma = 0;

  for (int i = 0; i < qtd; i++) {
    soma += v[i].salario;
  }
  if (qtd == 0) {
    return 0;
  } else {
    return soma / qtd;
  }
}
void imprimirMedia(struct Funcionario v[], int qtd) {
  printf("Média salarial: %.2f\n", calcularMediaSalarial(v, qtd));
}
// imprimir acima da média
void acimaDaMediaSalarial(struct Funcionario v[], int qtd) {
  float media = calcularMediaSalarial(v, qtd);

  printf("\n===== FUNCIONÁRIOS QUE GANHAM ACIMA DA MÉDIA =====\n");

  for (int i = 0; i < qtd; i++) {
    if (v[i].salario > media) {
      printf("\nMATRÍCULA: %d\n", v[i].matricula);
      printf("NOME: %s\n", v[i].nome);
      printf("CARGO: %s\n", v[i].cargo);
      printf("SALÁRIO: %.2f\n", v[i].salario);
    }
  }
}
// função que ordena salário
void ordnarPorSalario(struct Funcionario v[], int qtd) {
  int menor;

  for (int i = 0; i < qtd - 1; i++) {
    menor = i;
    for (int j = i + 1; j < qtd; j++) {
      if (v[j].salario < v[menor].salario) {
        menor = j;
      }
    }
    if (menor != i) {
      struct Funcionario aux = v[i];
      v[i] = v[menor];
      v[menor] = aux;
    }
  }
}
// função ordenar por nome
void ordenarPorNome(struct Funcionario v[], int qtd) {
  int menor = 0;

  for (int i = 0; i < qtd - 1; i++) {
    menor = i;
    for (int j = i + 1; j < qtd; j++) {
      if (strcmp(v[j].nome, v[menor].nome) < 0) {
        menor = j;
      }
    }
    if (menor != i) {
      struct Funcionario aux = v[i];
      v[i] = v[menor];
      v[menor] = aux;
    }
  }
}
// função para aumento de salário
void aumentarSalario(struct Funcionario v[], int qtd, float percentual) {
  for (int i = 0; i < qtd; i++) {
    float salarioAntigo = v[i].salario;
    float aumento = salarioAntigo * percentual / 100;

    printf("\nFuncionário: %s\n", v[i].nome);
    printf("Salário antigo: %.2f\n", salarioAntigo);
    printf("Aumento: %.2f\n", aumento);

    v[i].salario = salarioAntigo + aumento;

    printf("Novo salário: %.2f\n", v[i].salario);
  }
}
int main() {
  struct Funcionario funcionarios[TAM];

  int qtd = 0;
  int opcao;
  float valor;
  float percentual;

  do {
    printf("\n===== MENU =====\n");
    printf("1 - Cadastrar funcionários\n");
    printf("2 - Listar todos\n");
    printf("3 - Buscar por nome\n");
    printf("4 - Buscar por matrícula\n");
    printf("5 - Funcionários acima de um salário\n");
    printf("6 - Média salarial)\n");
    printf("7 - Funcinários acima da média\n");
    printf("8 - Ordenar por salário\n");
    printf("9 - Ordenar por nome\n");
    printf("10 - Dar aumento para todos\n");
    printf("0 - Encerrar o programa\n");

    printf("Opção: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
      case 1:
        cadastrarFuncionario(funcionarios, &qtd);
        break;

      case 2:
        imprimirFuncionarios(funcionarios, qtd);
        break;

      case 3:
        imprimirBuscaPorNome(funcionarios, qtd);
        break;

      case 4:
        imprimirBuscaPorMatricula(funcionarios, qtd);
        break;

      case 5:
        printf("Digite o valor mínimo: ");
        scanf("%f", &valor);
        getchar();
        funcionariosComSalariosAcima(funcionarios, qtd, valor);
        break;

      case 6:
        imprimirMediaSalarial(funcionarios, qtd);
        break;

      case 7:
        acimaDaMediaSalarial(funcionarios, qtd);
        break;

      case 8:
        ordnarPorSalario(funcionarios, qtd);
        imprimirFuncionarios(funcionarios, qtd);
        break;

      case 9:
        ordenarPorNome(funcionarios, qtd);
        imprimirFuncionarios(funcionarios, qtd);
        break;

      case 10:
        printf("Digite o percentual de aumento: ");
        scanf("%f", &percentual);
        getchar();
        aumentarSalario(funcionarios, qtd, percentual);
        break;

      case 0:
        printf("FIM DO PROGRAMA!\n");
        break;

      default:
        printf("OPÇÃO INVÁLIDA!\n");
    }
  } while (opcao != 0);
}