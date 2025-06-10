#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída
#include <math.h>  // Necessário para a função abs() para o octaedro

// Definições de constantes para facilitar a manutenção do código
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5 // Novo valor para representar a área de efeito da habilidade

// Tamanho das matrizes de habilidade (ex: 5x5)
#define TAMANHO_HABILIDADE_MATRIZ 5 // Deve ser um número ímpar para ter um centro claro

// --- Funções Auxiliares (do nível aventureiro, ligeiramente modificadas/mantidas) ---

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para exibir o tabuleiro (modificada para incluir HABILIDADE)
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n--- Tabuleiro do Batalha Naval ---\n");
    printf("0 = Agua\n");
    printf("3 = Navio\n");
    printf("5 = Habilidade\n\n");

    // Imprime os índices das colunas para facilitar a visualização
    printf("   "); // Espaço para alinhar com os índices das linhas
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j); // Imprime o índice da coluna
    }
    printf("\n");

    // Imprime a linha separadora
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("---");
    }
    printf("-\n");


    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d |", i); // Imprime o índice da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]); // Imprime o valor da célula
        }
        printf("\n");
    }
    printf("\n");
}

// Função para posicionar um navio e validar. Retorna 1 se houve erro, 0 se sucesso.
// tipo_navio: 0 = horizontal, 1 = vertical, 2 = diagonal_principal (linha e coluna aumentam), 3 = diagonal_secundaria (linha aumenta, coluna diminui)
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicio, int coluna_inicio, int tipo_navio) {
    // Verifica os limites do tabuleiro e sobreposição
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        int linha_atual, coluna_atual;

        if (tipo_navio == 0) { // Horizontal
            linha_atual = linha_inicio;
            coluna_atual = coluna_inicio + k;
        } else if (tipo_navio == 1) { // Vertical
            linha_atual = linha_inicio + k;
            coluna_atual = coluna_inicio;
        } else if (tipo_navio == 2) { // Diagonal Principal (crescente)
            linha_atual = linha_inicio + k;
            coluna_atual = coluna_inicio + k;
        } else if (tipo_navio == 3) { // Diagonal Secundária (linha crescente, coluna decrescente)
            linha_atual = linha_inicio + k;
            coluna_atual = coluna_inicio - k; // Coluna diminui
        } else {
            printf("Erro interno: Tipo de navio invalido.\n");
            return 1; // Erro interno
        }

        // Valida se a posição atual está dentro dos limites do tabuleiro
        if (linha_atual < 0 || linha_atual >= TAMANHO_TABULEIRO ||
            coluna_atual < 0 || coluna_atual >= TAMANHO_TABULEIRO) {
            printf("Erro: Navio fora dos limites do tabuleiro. (Tipo: %d, Inicio: %d,%d)\n", tipo_navio, linha_inicio, coluna_inicio);
            return 1; // Erro: fora dos limites
        }

        // Valida sobreposição com outro navio
        if (tabuleiro[linha_atual][coluna_atual] == NAVIO) {
            printf("Erro: Sobreposicao detectada para o navio. (Tipo: %d, Inicio: %d,%d)\n", tipo_navio, linha_inicio, coluna_inicio);
            return 1; // Erro: sobreposição
        }
    }

    // Se passou por todas as validações, posiciona o navio
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        int linha_atual, coluna_atual;

        if (tipo_navio == 0) { // Horizontal
            linha_atual = linha_inicio;
            coluna_atual = coluna_inicio + k;
        } else if (tipo_navio == 1) { // Vertical
            linha_atual = linha_inicio + k;
            coluna_atual = coluna_inicio;
        } else if (tipo_navio == 2) { // Diagonal Principal (crescente)
            linha_atual = linha_inicio + k;
            coluna_atual = coluna_inicio + k;
        } else if (tipo_navio == 3) { // Diagonal Secundária (linha crescente, coluna decrescente)
            linha_atual = linha_inicio + k;
            coluna_atual = coluna_inicio - k;
        }

        tabuleiro[linha_atual][coluna_atual] = NAVIO;
    }
    return 0; // Sucesso
}

// --- Funções para Habilidades Especiais ---

// Função para criar a matriz da habilidade Cone
// O cone aponta para baixo, com o vértice no topo central
void criarHabilidadeCone(int habilidade_matriz[TAMANHO_HABILIDADE_MATRIZ][TAMANHO_HABILIDADE_MATRIZ]) {
    int centro = TAMANHO_HABILIDADE_MATRIZ / 2; // Centro da matriz da habilidade

    for (int i = 0; i < TAMANHO_HABILIDADE_MATRIZ; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_MATRIZ; j++) {
            habilidade_matriz[i][j] = AGUA; // Inicializa com 0 (não afetado)
        }
    }

    // Lógica para o cone (apontando para baixo)
    for (int i = 0; i < TAMANHO_HABILIDADE_MATRIZ; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_MATRIZ; j++) {
            // Distância da coluna ao centro na linha atual
            int dist_coluna_centro = abs(j - centro);
            // Largura do cone na linha 'i'. Diminui conforme 'i' sobe.
            // Ex: Na linha 0, largura 1. Na linha 1, largura 3. Na linha 2, largura 5.
            if (dist_coluna_centro <= i) {
                habilidade_matriz[i][j] = 1;
            }
        }
    }
    // Para um cone apontando para baixo, podemos querer que a largura aumente.
    // Exemplo:
    // i=0:   0 0 1 0 0  (centro)
    // i=1:   0 1 1 1 0  (centro +/- 1)
    // i=2:   1 1 1 1 1  (centro +/- 2)

    // Reajustando a lógica para que o cone comece estreito no topo e expanda
    for (int i = 0; i < TAMANHO_HABILIDADE_MATRIZ; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_MATRIZ; j++) {
            habilidade_matriz[i][j] = AGUA; // Reset
            // A largura do cone aumenta com a linha (i)
            // Na linha 0, apenas o centro. Na linha 1, centro e adjacentes, etc.
            int largura_na_linha = i; // controla o "raio"
            if (j >= centro - largura_na_linha && j <= centro + largura_na_linha) {
                habilidade_matriz[i][j] = 1;
            }
        }
    }
}


// Função para criar a matriz da habilidade Cruz
// O centro da cruz é o centro da matriz
void criarHabilidadeCruz(int habilidade_matriz[TAMANHO_HABILIDADE_MATRIZ][TAMANHO_HABILIDADE_MATRIZ]) {
    int centro = TAMANHO_HABILIDADE_MATRIZ / 2; // Centro da matriz da habilidade

    for (int i = 0; i < TAMANHO_HABILIDADE_MATRIZ; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_MATRIZ; j++) {
            habilidade_matriz[i][j] = AGUA; // Inicializa com 0 (não afetado)
        }
    }

    // Linha do meio
    for (int j = 0; j < TAMANHO_HABILIDADE_MATRIZ; j++) {
        habilidade_matriz[centro][j] = 1;
    }
    // Coluna do meio
    for (int i = 0; i < TAMANHO_HABILIDADE_MATRIZ; i++) {
        habilidade_matriz[i][centro] = 1;
    }
}

// Função para criar a matriz da habilidade Octaedro (Losango)
// O centro do losango é o centro da matriz
void criarHabilidadeOctaedro(int habilidade_matriz[TAMANHO_HABILIDADE_MATRIZ][TAMANHO_HABILIDADE_MATRIZ]) {
    int centro = TAMANHO_HABILIDADE_MATRIZ / 2; // Centro da matriz da habilidade

    for (int i = 0; i < TAMANHO_HABILIDADE_MATRIZ; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_MATRIZ; j++) {
            habilidade_matriz[i][j] = AGUA; // Inicializa com 0 (não afetado)
        }
    }

    // Lógica para o losango (octaedro)
    // A soma das distâncias absolutas ao centro (manhattan distance) deve ser <= ao raio
    // Para um tamanho 5x5, o raio máximo do losango é 2 (centro 2,2)
    // |i - centro| + |j - centro| <= centro
    for (int i = 0; i < TAMANHO_HABILIDADE_MATRIZ; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_MATRIZ; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro) {
                habilidade_matriz[i][j] = 1;
            }
        }
    }
}

// Função para sobrepor uma habilidade no tabuleiro
// habilidade_matriz: a matriz da habilidade (cone, cruz, octaedro)
// centro_tabuleiro_linha, centro_tabuleiro_coluna: ponto de origem da habilidade no tabuleiro
void sobreporHabilidadeNoTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                                   int habilidade_matriz[TAMANHO_HABILIDADE_MATRIZ][TAMANHO_HABILIDADE_MATRIZ],
                                   int centro_tabuleiro_linha, int centro_tabuleiro_coluna) {

    int offset = TAMANHO_HABILIDADE_MATRIZ / 2; // Distância do centro à borda da matriz de habilidade

    // Itera sobre a matriz da habilidade
    for (int i = 0; i < TAMANHO_HABILIDADE_MATRIZ; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_MATRIZ; j++) {
            // Calcula a posição correspondente no tabuleiro
            int tabuleiro_linha = centro_tabuleiro_linha - offset + i;
            int tabuleiro_coluna = centro_tabuleiro_coluna - offset + j;

            // Verifica se a posição está dentro dos limites do tabuleiro
            if (tabuleiro_linha >= 0 && tabuleiro_linha < TAMANHO_TABULEIRO &&
                tabuleiro_coluna >= 0 && tabuleiro_coluna < TAMANHO_TABULEIRO) {
                
                // Se a posição na matriz de habilidade é '1' (afetada)
                if (habilidade_matriz[i][j] == 1) {
                    // Marca a posição no tabuleiro com o valor de HABILIDADE,
                    // mas sem sobrescrever navios (opcional, dependendo da regra do jogo)
                    // Por simplicidade, vamos sobrescrever para visualizar a área de efeito.
                    // Se quisermos que o navio continue visível, poderíamos usar um valor diferente
                    // ou uma lógica mais complexa.
                    tabuleiro[tabuleiro_linha][tabuleiro_coluna] = HABILIDADE;
                }
            }
        }
    }
}


int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // --- Posicionamento dos Quatro Navios (do nível aventureiro) ---

    // Navio 1: Horizontal
    if (posicionarNavio(tabuleiro, 2, 1, 0) != 0) {
        printf("Nao foi possivel posicionar o Navio 1 (Horizontal).\n");
    }

    // Navio 2: Vertical
    if (posicionarNavio(tabuleiro, 5, 7, 1) != 0) {
        printf("Nao foi possivel posicionar o Navio 2 (Vertical).\n");
    }

    // Navio 3: Diagonal Principal (linha e coluna aumentam)
    if (posicionarNavio(tabuleiro, 1, 1, 2) != 0) { // Cuidado com sobreposições aqui!
        printf("Nao foi possivel posicionar o Navio 3 (Diagonal Principal).\n");
    }

    // Navio 4: Diagonal Secundária (linha aumenta, coluna diminui)
    if (posicionarNavio(tabuleiro, 0, 9, 3) != 0) {
        printf("Nao foi possivel posicionar o Navio 4 (Diagonal Secundaria).\n");
    }

    // --- Criação e Sobreposição das Habilidades ---

    int habilidade_cone[TAMANHO_HABILIDADE_MATRIZ][TAMANHO_HABILIDADE_MATRIZ];
    int habilidade_cruz[TAMANHO_HABILIDADE_MATRIZ][TAMANHO_HABILIDADE_MATRIZ];
    int habilidade_octaedro[TAMANHO_HABILIDADE_MATRIZ][TAMANHO_HABILIDADE_MATRIZ];

    // Cria as matrizes de habilidade
    criarHabilidadeCone(habilidade_cone);
    criarHabilidadeCruz(habilidade_cruz);
    criarHabilidadeOctaedro(habilidade_octaedro);

    // Exibe as matrizes de habilidade para debug (opcional)
    /*
    printf("\n--- Matriz Habilidade Cone ---\n");
    for(int i=0; i<TAMANHO_HABILIDADE_MATRIZ; i++) {
        for(int j=0; j<TAMANHO_HABILIDADE_MATRIZ; j++) {
            printf("%d ", habilidade_cone[i][j]);
        }
        printf("\n");
    }
    printf("\n--- Matriz Habilidade Cruz ---\n");
    for(int i=0; i<TAMANHO_HABILIDADE_MATRIZ; i++) {
        for(int j=0; j<TAMANHO_HABILIDADE_MATRIZ; j++) {
            printf("%d ", habilidade_cruz[i][j]);
        }
        printf("\n");
    }
    printf("\n--- Matriz Habilidade Octaedro ---\n");
    for(int i=0; i<TAMANHO_HABILIDADE_MATRIZ; i++) {
        for(int j=0; j<TAMANHO_HABILIDADE_MATRIZ; j++) {
            printf("%d ", habilidade_octaedro[i][j]);
        }
        printf("\n");
    }
    */


    // Sobrepõe as habilidades no tabuleiro em pontos específicos
    // (linha_centro_habilidade, coluna_centro_habilidade)
    // O ponto de origem da habilidade é o centro da matriz da habilidade.
    // Ex: uma matriz 5x5 tem o centro em [2][2]
    sobreporHabilidadeNoTabuleiro(tabuleiro, habilidade_cone, 3, 5); // Cone centrado em (3,5)
    sobreporHabilidadeNoTabuleiro(tabuleiro, habilidade_cruz, 7, 2); // Cruz centrado em (7,2)
    sobreporHabilidadeNoTabuleiro(tabuleiro, habilidade_octaedro, 6, 6); // Octaedro centrado em (6,6)


    // Exibir o tabuleiro final com navios e habilidades
    exibirTabuleiro(tabuleiro);

    return 0; // Indica que o programa foi executado com sucesso
}