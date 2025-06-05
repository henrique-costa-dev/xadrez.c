#include <stdio.h>

// Função recursiva para movimento da Torre (direita)
void moverTorre(int casas) {
    if (casas <= 0) return; // Caso base
    printf("Direita\n");
    moverTorre(casas - 1); // Chamada recursiva
}

// Função recursiva para movimento do Bispo (diagonal superior direita)
void moverBispo(int casas) {
    if (casas <= 0) return; // Caso base
    printf("Cima, Direita\n");
    moverBispo(casas - 1); // Chamada recursiva
}

// Função recursiva para movimento da Rainha (esquerda)
void moverRainha(int casas) {
    if (casas <= 0) return; // Caso base
    printf("Esquerda\n");
    moverRainha(casas - 1); // Chamada recursiva
}

// Função para movimento do Cavalo com loops complexos (2 cima, 1 direita)
void moverCavalo() {
    int vertical = 2; // Casas para cima
    int horizontal = 1; // Casa para direita
    
    // Loop complexo com múltiplas variáveis
    for (int i = 1, j = 1; i <= vertical || j <= horizontal; ) {
        if (i <= vertical) {
            printf("Cima\n");
            i++;
            continue; // Continua priorizando o movimento vertical
        }
        
        if (j <= horizontal) {
            printf("Direita\n");
            j++;
            break; // Após completar o horizontal, sai do loop
        }
    }
}

// Função para movimento do Bispo com loops aninhados
void moverBispoAninhado(int casas) {
    // Loop externo para controle geral
    for (int i = 0; i < casas; i++) {
        // Loop interno para simular a diagonal
        for (int j = 0; j < 1; j++) { // Executa apenas uma vez por iteração externa
            printf("Cima, Direita\n");
        }
    }
}

int main() {
    // Constantes para número de movimentos
    const int TORRE_CASAS = 5;
    const int BISPO_CASAS = 5;
    const int RAINHA_CASAS = 8;
    
    printf("Movimento da Torre (recursivo):\n");
    moverTorre(TORRE_CASAS);
    
    printf("\nMovimento do Bispo (recursivo):\n");
    moverBispo(BISPO_CASAS);
    
    printf("\nMovimento da Rainha (recursivo):\n");
    moverRainha(RAINHA_CASAS);
    
    printf("\nMovimento do Cavalo (loops complexos):\n");
    moverCavalo();
    
    printf("\nMovimento do Bispo (loops aninhados):\n");
    moverBispoAninhado(BISPO_CASAS);
    
    return 0;
}