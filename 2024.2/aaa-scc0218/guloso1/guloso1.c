#include <stdbool.h>
#include <stdio.h>

void trocas(int v[], int n) {
    int rounds = 0;
    bool found[n + 1];

    // Initialize the boolean array
    for (int i = 0; i <= n; i++) {
        found[i] = false;
    }

    int count = 0;

    while (count < n) {
        rounds++;
        for (int i = 0; i < n; i++) {
            if (!found[v[i]] && v[i] == count + 1) {
                found[v[i]] = true;
                count++;
            }
        }
    }

    printf("%d\n", rounds);
}

int main() {
    int n;
    scanf("%d", &n);

    int vetor[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }

    trocas(vetor, n);

    return 0;
}
