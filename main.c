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
    PRODUTOS_ACUCARADOS,
    VERDURAS_HORTALICAS_E_DERIVADOS,
    FRUTAS_E_DERIVADOS
} categoria_alimento;

void insere_alimentos_lista(char* linha,int indice ,struct alimento* lista_alimentos){
    const char delimiter[] = ",";
    char *item;
    int contador_organizador = 0;

    linha[strcspn(linha, "\r\n")] = '\0';
    item = strtok(linha, delimiter);

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
                }else if (strcmp(item, "Verduras hortaliças e derivados") == 0) {
                    lista_alimentos[indice].categoria = VERDURAS_HORTALICAS_E_DERIVADOS;
                }else if (strcmp(item, "Frutas e derivados") == 0) {
                    lista_alimentos[indice].categoria = FRUTAS_E_DERIVADOS;
                }
            }

            item = strtok(NULL, delimiter);
        }

}

void print_categorias(const char* nomes_categoria[]) {
    printf("\ncategorias:\n");
    for (int i = 0; i < 10; i++) {
        printf("- %s\n ", nomes_categoria[i]);
    }
}

void todos_alimentos_categoria_x_ordem_alfabetica(const char* nomes_categoria[], struct alimento* lista_alimentos) {
    int categoria_escolha = 0;
    printf("\n\tESCOLHA A CATEGORIA:");
    for (int i = 0; i < 10; i++) {
        printf("\n\t[%d]- %s",i + 1,nomes_categoria[i]);
    }
    printf("\n\tinput: ");
    scanf("%d", &categoria_escolha);
    printf("\n\tAlimentos da categoria %s\n", nomes_categoria[categoria_escolha - 1]);
    for (int j = 0; j < 100; j++) {
        if ((lista_alimentos[j].categoria) == categoria_escolha - 1) {
            printf("\t- %s\n", lista_alimentos[j].descricao);
        }
    }
}
int main(void) {
    FILE* texto_alimentos;
    texto_alimentos = fopen("alimentos.txt", "r");
    if (texto_alimentos == NULL) {
        perror("error");
    }
    struct alimento lista_alimentos[100];
    char linha[100];
    int indice = 0;
    const char* nomes_categoria[] = {"alimentos preparados", "bebidas", "carnes e derivados", "cereais e derivados", "gorduras e oleos", "leguminosas e derivados",
        "leite e derivados", "produtos acucarados", "verduras hortalicas e derivados", "frutas e derivados"};

    while (fgets(linha, 100, texto_alimentos) != NULL) {
        insere_alimentos_lista (linha, indice, lista_alimentos);
        indice += 1;
    }


    int escolha = 0;
    while (escolha != 10) {
        printf("\nDigite:\n[1] para ver todas as categorias de alimentos\n[2] para ver todos alimentos dentro de X categoria em ordem alfabética de acordo com a descricao do alimento\n"
               "[3] para ver todos alimentos dentro de X categoria em ordem decrescente de capacidade energetica\n[4] para ver os N alimentos com maior percentual de umidade em ordem decrescente de X categoria\n"
               "[5] para ver N alimentos em ordem decrescente de capacidade energetica de X categoria\n[6] para ver os N alimentos de X categoria em ordem decrescente em maior quantidade de proteina\n"
               "[7] para ver os N alimentos de X categoria em ordem decrescente em maior quantidade de carboidrato\n"
               "[8] para ver os N alimentos de X categoria que contem a relacao mais alta entre energia e proteina em ordem decrescente\n"
               "[9] para ver os N alimentos de X categoria que contem a relacao mais alta entre energia e carboidrato em ordem decrescente\n[10] para encerrar o programa\ninput: ");
        scanf("%d", &escolha);
        if (escolha == 1) {
            print_categorias(nomes_categoria);
        }else if (escolha == 2) {
            todos_alimentos_categoria_x_ordem_alfabetica(nomes_categoria, lista_alimentos);
        }
    }

    return 0;
}