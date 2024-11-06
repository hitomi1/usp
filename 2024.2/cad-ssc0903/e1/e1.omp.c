#include <omp.h>
#include <stdio.h>

int main() {
  int N;

  // Solicita ao usuário o número de threads
  scanf("%d", &N);

  // Define o número de threads
  omp_set_num_threads(N);

// Seção paralela com OpenMP
#pragma omp parallel

  printf("Hello, World!\n");

  return 0;
}
