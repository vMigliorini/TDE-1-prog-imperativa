#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct alimento{
    int numero_alimento;
    char descricao[50];
    float umidade;
    float energia;
    float proteina;
    float carboidrato;
    int categoria;
};
typedef enum {
    ALIMENTOS_PREPARADOS,
    BEBIDAS,
    CARNES_E_DERIVADOS,
    CEREAIS_E_DERIVADOS,
    GORDURAS_E_OLEOS,
    LEGUMINOSAS_E_DERIVADOS,
    LEITE_E_DERIVADOS,
    PRODUTOS_ACUCARADOS
} CategoriaAlimento;


int main(void) {
    FILE* texto_alimentos;
    texto_alimentos = fopen("alimentos.txt", "r");
    if (texto_alimentos == NULL) {
        perror("error");
    }
    struct alimento lista_alimentos[100];
    char linha[100];
    const char delimiter[] = ",";
    char *item;
    int contador_organizador = 0;
    int indice = 0;

    while (fgets(linha, 100, texto_alimentos) != NULL) {

        linha[strcspn(linha, "\r\n")] = '\0';
        item = strtok(linha, delimiter);
        contador_organizador = 0;
        while (item != NULL) {
            contador_organizador += 1;
            if (contador_organizador == 1) {
                lista_alimentos[indice].numero_alimento = atoi(item);
            }else if (contador_organizador == 2) {
                strcpy(lista_alimentos[indice].descricao, item);
            }else if (contador_organizador == 3) {
                lista_alimentos[indice].umidade = atof(item);
            }else if (contador_organizador == 4) {
                lista_alimentos[indice].energia = atof(item);
            }else if (contador_organizador == 5) {
                lista_alimentos[indice].proteina = atof(item);
            }else if (contador_organizador == 6) {
                lista_alimentos[indice].carboidrato = atof(item);
            }else if (contador_organizador == 7) {
                if (strcmp(item, "Alimentos preparados") == 0) {
                    lista_alimentos[indice].categoria = ALIMENTOS_PREPARADOS;
                }else if (strcmp(item, "Bebidas (alcoólicas e não alcoólicas)") == 0) {
                    lista_alimentos[indice].categoria = BEBIDAS;
                }else if (strcmp(item, "Carnes e derivados") == 0) {
                    lista_alimentos[indice].categoria = CARNES_E_DERIVADOS;
                }else if (strcmp(item, "Cereais e derivados") == 0) {
                    lista_alimentos[indice].categoria = CEREAIS_E_DERIVADOS;
                }else if (strcmp(item, "Gorduras e óleos") == 0) {
                    lista_alimentos[indice].categoria = GORDURAS_E_OLEOS;
                }else if (strcmp(item, "Leguminosas e derivados") == 0) {
                    lista_alimentos[indice].categoria = LEGUMINOSAS_E_DERIVADOS;
                }else if (strcmp(item, "Leite e derivados") == 0) {
                    lista_alimentos[indice].categoria = LEITE_E_DERIVADOS;
                }else if (strcmp(item, "Produtos açucarados") == 0) {
                    lista_alimentos[indice].categoria = PRODUTOS_ACUCARADOS;
                }
            }

            item = strtok(NULL, delimiter);
        }
        indice += 1;
    }
    //printf de teste
    printf("alimento %d\ndescricao: %s\numidade: %f\nenergia: %f\nproteina: %f\ncarboidrato: %f\ncategoria: %d ", lista_alimentos[20].numero_alimento, lista_alimentos[20].descricao, lista_alimentos[20].umidade, lista_alimentos[20].energia, lista_alimentos[20].proteina, lista_alimentos[20].carboidrato, lista_alimentos[20].categoria);


    return 0;
}