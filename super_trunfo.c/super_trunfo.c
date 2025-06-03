#include <stdio.h> // Biblioteca para entrada e saída de dados (printf, scanf)
#include <string.h> // Biblioteca para manipulação de strings (strncpy)

// Definição da estrutura para uma carta de Super Trunfo
// Isso cria um "molde" para as informações de cada carta
typedef struct {
    char estado;              // Uma letra de 'A' a 'H'
    char codigo_carta[5];     // Ex: A01, B03 (precisa de 4 caracteres + 1 para o nulo '\0')
    char nome_cidade[50];     // O nome da cidade (coloquei um tamanho generoso)
    int populacao;            // Número de habitantes
    float area_km2;           // Área em km²
    float pib;                // Produto Interno Bruto
    int num_pontos_turisticos; // Quantidade de pontos turísticos
} CartaSuperTrunfo; // O nome do nosso novo tipo de dado

int main() {
    // Declaração de duas variáveis do tipo CartaSuperTrunfo
    CartaSuperTrunfo carta1, carta2;

    // --- CADASTRO DA CARTA 1 ---
    printf("--- Cadastro da Carta 1 ---\n");

    printf("Estado (A-H): ");
    scanf(" %c", &carta1.estado); // O espaço antes de %c é importante para consumir o '\n' do enter anterior

    printf("Codigo da Carta (ex: A01): ");
    scanf("%s", carta1.codigo_carta); // %s lê uma string até encontrar um espaço ou quebra de linha

    printf("Nome da Cidade: ");
    // Limpa o buffer de entrada antes de ler a string com espaços
    // Fgets é mais seguro para ler strings com espaços do que scanf("%s")
    getchar(); // Consome o '\n' que sobrou do scanf anterior
    fgets(carta1.nome_cidade, sizeof(carta1.nome_cidade), stdin);
    // Remove o '\n' que o fgets adiciona no final da string, se houver
    carta1.nome_cidade[strcspn(carta1.nome_cidade, "\n")] = 0;


    printf("Populacao: ");
    scanf("%d", &carta1.populacao);

    printf("Area (em km^2): ");
    scanf("%f", &carta1.area_km2);

    printf("PIB (em bilhoes de reais): ");
    scanf("%f", &carta1.pib);

    printf("Numero de Pontos Turisticos: ");
    scanf("%d", &carta1.num_pontos_turisticos);

    printf("\n"); // Adiciona uma linha em branco para melhor visualização

    // --- CADASTRO DA CARTA 2 ---
    printf("--- Cadastro da Carta 2 ---\n");

    printf("Estado (A-H): ");
    scanf(" %c", &carta2.estado);

    printf("Codigo da Carta (ex: A01): ");
    scanf("%s", carta2.codigo_carta);

    printf("Nome da Cidade: ");
    getchar(); // Consome o '\n'
    fgets(carta2.nome_cidade, sizeof(carta2.nome_cidade), stdin);
    carta2.nome_cidade[strcspn(carta2.nome_cidade, "\n")] = 0;

    printf("Populacao: ");
    scanf("%d", &carta2.populacao);

    printf("Area (em km^2): ");
    scanf("%f", &carta2.area_km2);

    printf("PIB (em bilhoes de reais): ");
    scanf("%f", &carta2.pib);

    printf("Numero de Pontos Turisticos: ");
    scanf("%d", &carta2.num_pontos_turisticos);

    printf("\n");

    // --- EXIBIÇÃO DAS CARTAS ---
    printf("--- Cartas Cadastradas ---\n");

    // Exibição da Carta 1
    printf("Carta 1:\n");
    printf("Estado: %c\n", carta1.estado);
    printf("Codigo: %s\n", carta1.codigo_carta);
    printf("Nome da Cidade: %s\n", carta1.nome_cidade);
    printf("Populacao: %d\n", carta1.populacao);
    printf("Area: %.2f km^2\n", carta1.area_km2); // %.2f formata para 2 casas decimais
    printf("PIB: %.2f bilhoes de reais\n", carta1.pib);
    printf("Numero de Pontos Turisticos: %d\n", carta1.num_pontos_turisticos);

    printf("\n");

    // Exibição da Carta 2
    printf("Carta 2:\n");
    printf("Estado: %c\n", carta2.estado);
    printf("Codigo: %s\n", carta2.codigo_carta);
    printf("Nome da Cidade: %s\n", carta2.nome_cidade);
    printf("Populacao: %d\n", carta2.populacao);
    printf("Area: %.2f km^2\n", carta2.area_km2);
    printf("PIB: %.2f bilhoes de reais\n", carta2.pib);
    printf("Numero de Pontos Turisticos: %d\n", carta2.num_pontos_turisticos);

    return 0; // Indica que o programa terminou com sucesso
}