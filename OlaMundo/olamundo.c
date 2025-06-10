#include <stdio.h> // É importante incluir stdio.h para usar scanf e printf

int main() {
    int num, ind, soma = 0;
    for (ind = 1; ind <= 5; ind++) {
        scanf("%d", &num);
        if (num % 2 == 0)
            soma = soma + num;
    }
    printf("%d", soma);
    return 0; // Boa prática para indicar que o programa terminou com sucesso
}