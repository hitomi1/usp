#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int is_perfect(int num) {
  int sum = 1; // 1 é um divisor de todos os números

  // Encontrar os divisores próprios de num
  for (int i = 2; i * i <= num; i++) {
    if (num % i == 0) {
      sum += i;

      if (i != num / i) {
        sum += num / i;
      }
    }
  }

  return (sum == num && num != 1);
}

int main() {
  int N, num_threads;
  int total_sum = 0;

  // Solicita o limite superior N
  scanf("%d", &N);

  // Define um número de threads aleatório entre 5 e 10
  num_threads = (rand() % 6) + 5; // (10 - 5 + 1) + 5 = [5, 10]

  // Define o número de threads

  omp_set_num_threads(num_threads);

// Calcula a soma dos números perfeitos em paralelo
#pragma omp parallel reduction(+ : total_sum)
  {
#pragma omp for
    for (int i = 2; i <= N; i++) {
      if (is_perfect(i)) {
        total_sum += i;
      }
    }
  }

  // Exibe o resultado
  printf("%d", total_sum);

  return 0;
}
