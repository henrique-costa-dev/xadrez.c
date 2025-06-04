#include <stdio.h>   
#include <string.h>  
#include <limits.h>  

void limpar_buffer_entrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

typedef struct {
    char estado;                 // Uma letra de 'A' a 'H'
    char codigo_carta[5];        // Ex: A01, B03
    char nome_cidade[50];        // O nome da cidade
    unsigned long int populacao; // CUIDADO: unsigned long int para números maiores
    float area_km2;              // Área em km²
    float pib;                   // Produto Interno Bruto (em bilhões de reais)
    int num_pontos_turisticos;   // Quantidade de pontos turísticos
    
    float densidade_populacional; // População / Área
    float pib_per_capita;         // PIB / População (após ajuste de escala)
    float super_poder;            // Soma de atributos com lógica de inverso para densidade
} CartaSuperTrunfo;

int main() {
    CartaSuperTrunfo carta1, carta2;

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

    // --- CÁLCULOS PARA A CARTA 1 (Densidade Populacional e PIB per Capita) ---
    if (carta1.area_km2 > 0) {
        carta1.densidade_populacional = (float)carta1.populacao / carta1.area_km2;
    } else {
        carta1.densidade_populacional = 0.0; 
    }
    
    if (carta1.populacao > 0) {
        
        carta1.pib_per_capita = (float)((double)carta1.pib * 1000000000.0 / (double)carta1.populacao);
    } else {
        carta1.pib_per_capita = 0.0; 
    }

    // --- CÁLCULO DO SUPER PODER PARA A CARTA 1 ---
    float inverso_densidade_carta1 = 0.0;
    if (carta1.densidade_populacional > 0) {
        inverso_densidade_carta1 = 1.0 / carta1.densidade_populacional;
    }
    carta1.super_poder = (float)carta1.populacao + carta1.area_km2 + carta1.pib + 
                          (float)carta1.num_pontos_turisticos + carta1.pib_per_capita + 
                          inverso_densidade_carta1;


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

    // --- CÁLCULOS PARA A CARTA 2 (Densidade Populacional e PIB per Capita) 
    if (carta2.area_km2 > 0) {
        carta2.densidade_populacional = (float)carta2.populacao / carta2.area_km2;
    } else {
        carta2.densidade_populacional = 0.0;
    }
    
    if (carta2.populacao > 0) {
      
        carta2.pib_per_capita = (float)((double)carta2.pib * 1000000000.0 / (double)carta2.populacao);
    } else {
        carta2.pib_per_capita = 0.0;
    }

    // --- CÁLCULO DO SUPER PODER PARA A CARTA 2 ---
    float inverso_densidade_carta2 = 0.0;
    if (carta2.densidade_populacional > 0) {
        inverso_densidade_carta2 = 1.0 / carta2.densidade_populacional;
    }
    carta2.super_poder = (float)carta2.populacao + carta2.area_km2 + carta2.pib + 
                          (float)carta2.num_pontos_turisticos + carta2.pib_per_capita + 
                          inverso_densidade_carta2;


    printf("\n");

    // --- EXIBIÇÃO DAS CARTAS ---
    printf("--- Cartas Cadastradas ---\n");

    // Exibição da Carta 1
    printf("Carta 1:\n");
    printf("Estado: %c\n", carta1.estado);
    printf("Codigo: %s\n", carta1.codigo_carta);
    printf("Nome da Cidade: %s\n", carta1.nome_cidade);
    printf("Populacao: %lu\n", carta1.populacao); 
    printf("Area: %.2f km^2\n", carta1.area_km2); 
    printf("PIB: %.2f bilhoes de reais\n", carta1.pib);
    printf("Numero de Pontos Turisticos: %d\n", carta1.num_pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km^2\n", carta1.densidade_populacional); 
    printf("PIB per Capita: %.2f reais\n", carta1.pib_per_capita);                 
    printf("Super Poder: %.2f\n", carta1.super_poder); 

    printf("\n");

    // Exibição da Carta 2
    printf("Carta 2:\n");
    printf("Estado: %c\n", carta2.estado);
    printf("Codigo: %s\n", carta2.codigo_carta);
    printf("Nome da Cidade: %s\n", carta2.nome_cidade);
    printf("Populacao: %lu\n", carta2.populacao); 
    printf("Area: %.2f km^2\n", carta2.area_km2);
    printf("PIB: %.2f bilhoes de reais\n", carta2.pib);
    printf("Numero de Pontos Turisticos: %d\n", carta2.num_pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km^2\n", carta2.densidade_populacional); 
    printf("PIB per Capita: %.2f reais\n", carta2.pib_per_capita);                 
    printf("Super Poder: %.2f\n", carta2.super_poder); 

    printf("\n--- Resultados das Comparacoes ---\n");

    // --- COMPARAÇÕES ---
    // População (maior vence)
    int populacao_vencedora = (carta1.populacao > carta2.populacao) ? 1 : 0;
    printf("Populacao: Carta %d venceu! (%d)\n", populacao_vencedora == 1 ? 1 : 2, populacao_vencedora);

    // Área (maior vence)
    int area_vencedora = (carta1.area_km2 > carta2.area_km2) ? 1 : 0;
    printf("Area: Carta %d venceu! (%d)\n", area_vencedora == 1 ? 1 : 2, area_vencedora);

    // PIB (maior vence)
    int pib_vencedor = (carta1.pib > carta2.pib) ? 1 : 0;
    printf("PIB: Carta %d venceu! (%d)\n", pib_vencedor == 1 ? 1 : 2, pib_vencedor);

    // Numero de Pontos Turisticos (maior vence)
    int pontos_turisticos_vencedor = (carta1.num_pontos_turisticos > carta2.num_pontos_turisticos) ? 1 : 0;
    printf("Pontos Turisticos: Carta %d venceu! (%d)\n", pontos_turisticos_vencedor == 1 ? 1 : 2, pontos_turisticos_vencedor);

    // Densidade Populacional (MENOR vence)
    int densidade_vencedora = (carta1.densidade_populacional < carta2.densidade_populacional) ? 1 : 0; 
    printf("Densidade Populacional: Carta %d venceu! (%d)\n", densidade_vencedora == 1 ? 1 : 2, densidade_vencedora);

    // PIB per Capita (maior vence)
    int pib_per_capita_vencedor = (carta1.pib_per_capita > carta2.pib_per_capita) ? 1 : 0;
    printf("PIB per Capita: Carta %d venceu! (%d)\n", pib_per_capita_vencedor == 1 ? 1 : 2, pib_per_capita_vencedor);

    // Super Poder (maior vence)
    int super_poder_vencedor = (carta1.super_poder > carta2.super_poder) ? 1 : 0;
    printf("Super Poder: Carta %d venceu! (%d)\n", super_poder_vencedor == 1 ? 1 : 2, super_poder_vencedor);


    return 0;
}