#include <stdio.h>   // Biblioteca para entrada e saída de dados (printf, scanf)
#include <string.h>  // Biblioteca para manipulação de strings (strncpy, strcspn, strcmp)
#include <limits.h>  // Incluído para compatibilidade

// Função auxiliar para limpar o buffer de entrada
void limpar_buffer_entrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Definição da estrutura para uma carta de Super Trunfo
typedef struct {
    char estado;                 // Uma letra de 'A' a 'H'
    char codigo_carta[5];        // Ex: A01, B03
    char nome_cidade[50];        // O nome da cidade
    unsigned long int populacao; // População (usando unsigned long int para maior alcance)
    float area_km2;              // Área em km²
    float pib;                   // Produto Interno Bruto (em bilhões de reais)
    int num_pontos_turisticos;   // Quantidade de pontos turísticos
    
    // Atributos calculados
    float densidade_populacional; // População / Área
    float pib_per_capita;         // PIB / População (após ajuste de escala)
} CartaSuperTrunfo;

// Função auxiliar para obter o valor "pontuável" de um atributo para a soma
// Para densidade demográfica, um valor menor deve significar uma pontuação maior.
// Usamos um valor máximo de referência para inverter a pontuação da densidade.
float obter_valor_pontuavel(const CartaSuperTrunfo *carta, int atributo_id) {
    switch (atributo_id) {
        case 1: return (float)carta->populacao;
        case 2: return carta->area_km2;
        case 3: return carta->pib;
        case 4: return (float)carta->num_pontos_turisticos;
        case 5: // Densidade Demográfica: menor valor é melhor, então inverter a pontuação
            // Assumimos um valor máximo razoável para a densidade para inversão.
            // Para cidades muito densas, esse valor pode precisar ser ajustado.
            // Se densidade for 0, o inverso é infinito. Lidamos com isso na origem.
            if (carta->densidade_populacional > 0) {
                 // Uma abordagem simples: 1 / densidade. Valores menores de densidade resultam em 1/densidade maiores.
                 return 100000.0 / carta->densidade_populacional; // Multiplicado para ter um valor mais significativo na soma
            } else {
                 return 1000000.0; // Se densidade é zero, considera um valor muito alto (bom)
            }
        case 6: return carta->pib_per_capita;
        default: return 0.0; // Atributo inválido
    }
}

// Função auxiliar para obter o nome de um atributo dado seu ID
const char* obter_nome_atributo(int atributo_id) {
    switch (atributo_id) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Número de Pontos Turísticos";
        case 5: return "Densidade Demográfica";
        case 6: return "PIB per Capita";
        default: return "Atributo Desconhecido";
    }
}

// Função auxiliar para exibir o menu de atributos dinamicamente
void exibir_menu_atributos(int atributo_ja_escolhido) {
    printf("\n--- Escolha um Atributo para Comparacao ---\n");
    if (atributo_ja_escolhido != 1) printf("1. Populacao\n");
    if (atributo_ja_escolhido != 2) printf("2. Area\n");
    if (atributo_ja_escolhido != 3) printf("3. PIB\n");
    if (atributo_ja_escolhido != 4) printf("4. Numero de Pontos Turisticos\n");
    if (atributo_ja_escolhido != 5) printf("5. Densidade Demografica\n");
    if (atributo_ja_escolhido != 6) printf("6. PIB per Capita\n");
    printf("Digite o numero do atributo: ");
}

int main() {
    CartaSuperTrunfo carta1, carta2;
    int escolha_atributo1, escolha_atributo2;
    int escolha_valida; // Para controlar a validação das escolhas

    // --- CADASTRO DA CARTA 1 ---
    printf("--- Cadastro da Carta 1 ---\n");
    printf("Estado (A-H): ");
    scanf(" %c", &carta1.estado);
    printf("Codigo da Carta (ex: A01): ");
    scanf("%s", carta1.codigo_carta);
    limpar_buffer_entrada(); 
    printf("Nome da Cidade: ");
    fgets(carta1.nome_cidade, sizeof(carta1.nome_cidade), stdin);
    carta1.nome_cidade[strcspn(carta1.nome_cidade, "\n")] = 0; 
    printf("Populacao: ");
    scanf("%lu", &carta1.populacao); 
    printf("Area (em km^2): ");
    scanf("%f", &carta1.area_km2);
    printf("PIB (em bilhoes de reais): ");
    scanf("%f", &carta1.pib); 
    printf("Numero de Pontos Turisticos: ");
    scanf("%d", &carta1.num_pontos_turisticos);

    // --- CÁLCULOS PARA A CARTA 1 ---
    carta1.densidade_populacional = (carta1.area_km2 > 0) ? (float)carta1.populacao / carta1.area_km2 : 0.0;
    carta1.pib_per_capita = (carta1.populacao > 0) ? (float)((double)carta1.pib * 1000000000.0 / (double)carta1.populacao) : 0.0;

    printf("\n"); 

    // --- CADASTRO DA CARTA 2 ---
    printf("--- Cadastro da Carta 2 ---\n");
    printf("Estado (A-H): ");
    scanf(" %c", &carta2.estado);
    printf("Codigo da Carta (ex: A01): ");
    scanf("%s", carta2.codigo_carta);
    limpar_buffer_entrada(); 
    printf("Nome da Cidade: ");
    fgets(carta2.nome_cidade, sizeof(carta2.nome_cidade), stdin);
    carta2.nome_cidade[strcspn(carta2.nome_cidade, "\n")] = 0;
    printf("Populacao: ");
    scanf("%lu", &carta2.populacao); 
    printf("Area (em km^2): ");
    scanf("%f", &carta2.area_km2);
    printf("PIB (em bilhoes de reais): ");
    scanf("%f", &carta2.pib); 
    printf("Numero de Pontos Turisticos: ");
    scanf("%d", &carta2.num_pontos_turisticos);

    // --- CÁLCULOS PARA A CARTA 2 ---
    carta2.densidade_populacional = (carta2.area_km2 > 0) ? (float)carta2.populacao / carta2.area_km2 : 0.0;
    carta2.pib_per_capita = (carta2.populacao > 0) ? (float)((double)carta2.pib * 1000000000.0 / (double)carta2.populacao) : 0.0;

    printf("\n");

    // --- ESCOLHA DO PRIMEIRO ATRIBUTO ---
    do {
        exibir_menu_atributos(0); // 0 indica que nenhum atributo foi escolhido ainda
        scanf("%d", &escolha_atributo1);
        limpar_buffer_entrada();

        escolha_valida = (escolha_atributo1 >= 1 && escolha_atributo1 <= 6);
        if (!escolha_valida) {
            printf("Opcao invalida para o primeiro atributo. Tente novamente.\n");
        }
    } while (!escolha_valida);

    // --- ESCOLHA DO SEGUNDO ATRIBUTO (Dinâmico) ---
    do {
        printf("\n--- Escolha o Segundo Atributo para Comparacao ---\n");
        printf("Atributo ja escolhido: %s\n", obter_nome_atributo(escolha_atributo1));
        exibir_menu_atributos(escolha_atributo1); // Passa o atributo já escolhido para excluí-lo do menu
        scanf("%d", &escolha_atributo2);
        limpar_buffer_entrada();

        escolha_valida = (escolha_atributo2 >= 1 && escolha_atributo2 <= 6 && escolha_atributo2 != escolha_atributo1);
        if (!escolha_valida) {
            printf("Opcao invalida ou atributo ja escolhido. Tente novamente.\n");
        }
    } while (!escolha_valida);

    printf("\n--- Resultado da Rodada Super Trunfo (Nível Mestre) ---\n");
    printf("Atributos escolhidos: %s e %s\n\n", 
           obter_nome_atributo(escolha_atributo1), obter_nome_atributo(escolha_atributo2));

    // --- CALCULAR SOMA DOS ATRIBUTOS PARA CADA CARTA ---
    float soma_carta1 = obter_valor_pontuavel(&carta1, escolha_atributo1) + 
                        obter_valor_pontuavel(&carta1, escolha_atributo2);
    
    float soma_carta2 = obter_valor_pontuavel(&carta2, escolha_atributo1) + 
                        obter_valor_pontuavel(&carta2, escolha_atributo2);

    // --- EXIBIÇÃO DETALHADA ---
    printf("Carta 1 (%s):\n", carta1.nome_cidade);
    printf("  %s: ", obter_nome_atributo(escolha_atributo1));
    switch (escolha_atributo1) {
        case 1: printf("%lu\n", carta1.populacao); break;
        case 2: printf("%.2f km^2\n", carta1.area_km2); break;
        case 3: printf("%.2f bilhoes de reais\n", carta1.pib); break;
        case 4: printf("%d pontos\n", carta1.num_pontos_turisticos); break;
        case 5: printf("%.2f hab/km^2\n", carta1.densidade_populacional); break;
        case 6: printf("%.2f reais\n", carta1.pib_per_capita); break;
    }
    printf("  %s: ", obter_nome_atributo(escolha_atributo2));
    switch (escolha_atributo2) {
        case 1: printf("%lu\n", carta1.populacao); break;
        case 2: printf("%.2f km^2\n", carta1.area_km2); break;
        case 3: printf("%.2f bilhoes de reais\n", carta1.pib); break;
        case 4: printf("%d pontos\n", carta1.num_pontos_turisticos); break;
        case 5: printf("%.2f hab/km^2\n", carta1.densidade_populacional); break;
        case 6: printf("%.2f reais\n", carta1.pib_per_capita); break;
    }
    printf("  Soma Total Pontuavel: %.2f\n\n", soma_carta1);

    printf("Carta 2 (%s):\n", carta2.nome_cidade);
    printf("  %s: ", obter_nome_atributo(escolha_atributo1));
    switch (escolha_atributo1) {
        case 1: printf("%lu\n", carta2.populacao); break;
        case 2: printf("%.2f km^2\n", carta2.area_km2); break;
        case 3: printf("%.2f bilhoes de reais\n", carta2.pib); break;
        case 4: printf("%d pontos\n", carta2.num_pontos_turisticos); break;
        case 5: printf("%.2f hab/km^2\n", carta2.densidade_populacional); break;
        case 6: printf("%.2f reais\n", carta2.pib_per_capita); break;
    }
    printf("  %s: ", obter_nome_atributo(escolha_atributo2));
    switch (escolha_atributo2) {
        case 1: printf("%lu\n", carta2.populacao); break;
        case 2: printf("%.2f km^2\n", carta2.area_km2); break;
        case 3: printf("%.2f bilhoes de reais\n", carta2.pib); break;
        case 4: printf("%d pontos\n", carta2.num_pontos_turisticos); break;
        case 5: printf("%.2f hab/km^2\n", carta2.densidade_populacional); break;
        case 6: printf("%.2f reais\n", carta2.pib_per_capita); break;
    }
    printf("  Soma Total Pontuavel: %.2f\n\n", soma_carta2);

    // --- DETERMINAR O VENCEDOR OU EMPATE USANDO OPERADOR TERNÁRIO ---
    const char *resultado = (soma_carta1 > soma_carta2) ? "Carta 1" : 
                            (soma_carta2 > soma_carta1) ? "Carta 2" : "Empate";

    if (strcmp(resultado, "Empate") == 0) {
        printf("Resultado Final: Empate!\n");
    } else {
        printf("Resultado Final: %s (%s) venceu a rodada!\n", 
               resultado, (strcmp(resultado, "Carta 1") == 0 ? carta1.nome_cidade : carta2.nome_cidade));
    }
    
    return 0;
}