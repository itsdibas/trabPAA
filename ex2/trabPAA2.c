#include <stdio.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

int main() {
    int N;
    scanf("%d", &N);

    int labirinto[N][N];

    // Ler o labirinto
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%d", &labirinto[i][j]);
        }
    }

    // Calcular a potência máxima em cada posição
    for (int i = N - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            labirinto[i][j] += max(labirinto[i + 1][j], labirinto[i + 1][j + 1]);
        }
    }

    // Encontrar a maior potência final
    int max_potencia = labirinto[0][0];
    printf("%d\n", max_potencia);

    return 0;
}
