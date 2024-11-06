#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>

int main() {
  int N, S, num_threads;
  int sum = 0;

  // Solicita o número de elementos (N) e a seed (S)
  scanf("%d", &N);
  scanf("%d", &S);

  // Define a seed para geração de números aleatórios
  srand(S);

  // Gera um número de threads aleatório entre 5 e 10
  num_threads = 5;

  // Define o número de threads

  omp_set_num_threads(num_threads);

  // Aloca memória para o vetor
  int *vetor = (int *)malloc(N * sizeof(int));

  // Gera os valores aleatórios no intervalo [0, 9] para o vetor
  for (int i = 0; i < N; i++) {
    vetor[i] = rand() % 10;
  }

// Calcula a soma dos elementos do vetor em paralelo
#pragma omp parallel for reduction(+ : sum)
  for (int i = 0; i < N; i++) {
    sum += vetor[i];
  }

  // Exibe o resultado
  printf("%d", sum);

  // Libera a memória alocada
  free(vetor);

  return 0;
}
