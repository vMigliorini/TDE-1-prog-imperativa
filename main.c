#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DESCRICAO 65
#define TAMANHO_LISTA 100
#define MAX_ALIMENTOS_POR_LISTA 12

struct alimento{
    int numero_alimento;
    char descricao[MAX_DESCRICAO];
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

int input_padrao_categoria(const char* nomes_categoria[]) {
    int categoria_escolha = 0;

    printf("\n\tESCOLHA A CATEGORIA:");
    for (int i = 0; i < 10; i++) {
        printf("\n\t[%d]- %s",i + 1,nomes_categoria[i]);
    }

    printf("\n\tinput: ");
    scanf("%d", &categoria_escolha);
    return categoria_escolha;
}

int input_padrao_quantidade_alimentos() {
    int qtd_alimentos_pedidos = 0;

    printf("Insira quantos alimentos você quer vizualizar: ");
    scanf("%d", &qtd_alimentos_pedidos);
    return qtd_alimentos_pedidos;
}

void print_categorias(const char* nomes_categoria[]) {
    printf("\ncategorias:\n");
    for (int i = 0; i < 10; i++) {
        printf("- %s\n ", nomes_categoria[i]);
    }
}

void imprimir_alimento_energia(struct alimento alim) {
    printf("\t%-70s %.2f kcal\n", alim.descricao, alim.energia);
}

void imprimir_alimento_proteina(struct alimento alim) {
    printf("\t%-70s %.2f g\n", alim.descricao, alim.proteina);
}

void imprimir_alimento_umidade(struct alimento alim) {
    printf("\t%-70s %.2f %\n", alim.descricao, alim.umidade);
}

void imprimir_alimento_carboidrato(struct alimento alim) {
    printf("\t%-70s %.2f g\n", alim.descricao, alim.carboidrato);
}

void imprimir_alimento_relacao_energia_proteina(struct alimento alim) {
    if (alim.proteina == 0) {
        printf("\t%-70s %.2f \n", alim.descricao, alim.energia);
    }else {
        printf("\t%-70s %.2f \n", alim.descricao, alim.energia / alim.proteina);
    }
}

void imprimir_alimento_relacao_energia_carboidrato(struct alimento alim) {
    if (alim.carboidrato == 0) {
        printf("\t%-70s %.2f \n", alim.descricao, alim.energia);
    }else {
        printf("\t%-70s %.2f \n", alim.descricao, alim.energia / alim.carboidrato);
    }
}

int comparar_por_capacidade_energetica_decrescente(struct alimento a, struct alimento b) {
    if (a.energia < b.energia) {
        return 1;
    }else if (a.energia > b.energia) {
        return -1;
    }
    return 0;
}

int comparar_por_quantidade_de_proteina_decrescente(struct alimento a, struct alimento b) {
    if (a.proteina < b.proteina) {
        return 1;
    }else if (a.proteina > b.proteina) {
        return -1;
    }
    return 0;
}

int comparar_por_percentual_de_umidade_decrescente(struct alimento a, struct alimento b) {
    if (a.umidade < b.umidade) {
        return 1;
    }else if (a.umidade > b.umidade) {
        return -1;
    }
    return 0;
}

int comparar_por_quantidade_de_carboidrato_decrescente(struct alimento a, struct alimento b) {
    if (a.carboidrato < b.carboidrato) {
        return 1;
    }else if (a.carboidrato > b.carboidrato) {
        return -1;
    }
    return 0;
}

int comparar_por_relacao_energia_e_proteina_decrescente(struct alimento a, struct alimento b) {
    if (a.proteina == 0) return -1;
    if (b.proteina == 0) return 1;
    if (a.energia / a.proteina < b.energia / b.proteina) {
        return 1;
    }else if (a.energia / a.proteina > b.energia / b.proteina) {
        return -1;
    }
    return 0;
}

int comparar_por_relacao_energia_e_carboidrato_decrescente(struct alimento a, struct alimento b) {
    if (a.carboidrato == 0) return -1;
    if (b.carboidrato == 0) return 1;
    if (a.energia / a.carboidrato < b.energia / b.carboidrato) {
        return 1;
    }else if (a.energia / a.carboidrato > b.energia / b.carboidrato) {
        return -1;
    }
    return 0;
}

void bubble_sort_descricao(int total_alimentos, struct alimento* lista_alimentos, int categoria_escolha) {
    int contador_local = 0;
    char lista_sort[TAMANHO_LISTA][MAX_DESCRICAO];
    char vetor_swap[MAX_DESCRICAO];

    for (int j = 0; j < total_alimentos; j++) {
        if ((lista_alimentos[j].categoria) == categoria_escolha - 1) {
            strcpy(lista_sort[contador_local], lista_alimentos[j].descricao);
            contador_local += 1;
        }
    }

    for (int i = 0; i < contador_local - 1; i++) {
        for (int j = 0; j < contador_local - 1 - i; j++){
            if (strcmp(lista_sort[j], lista_sort[j + 1]) > 0) {
                strcpy(vetor_swap, lista_sort[j]);
                strcpy(lista_sort[j], lista_sort[j + 1]);
                strcpy(lista_sort[j + 1], vetor_swap);
            }
        }
    }

    for (int i = 0; i < contador_local; i++) {
        printf("\t- %s\n", lista_sort[i]);
    }
}

void bubble_sort_float(int total_alimentos, struct alimento* lista_alimentos, int categoria_escolha, int (*funcao_comparacao)(struct alimento, struct alimento), void (*funcao_impressao)(struct alimento), int qtd_alimentos_pedidos) {
    int contador_local = 0;

    struct alimento alimentos_categoria[TAMANHO_LISTA];

    for (int j = 0; j < total_alimentos; j++) {
        if ((lista_alimentos[j].categoria) == categoria_escolha - 1) {
            alimentos_categoria[contador_local] = lista_alimentos[j];
            contador_local += 1;
        }
    }

    for (int i = 0; i < contador_local - 1; i++) {
        for (int j = 0; j < contador_local - 1 - i; j++){
            if (funcao_comparacao(alimentos_categoria[j], alimentos_categoria[j + 1]) > 0) {
                struct alimento temp = alimentos_categoria[j];
                alimentos_categoria[j] = alimentos_categoria[j + 1];
                alimentos_categoria[j + 1] = temp;
            }
        }
    }
    if (qtd_alimentos_pedidos == 0 || qtd_alimentos_pedidos > contador_local) {
        for (int i = 0; i < contador_local; i++) {
            funcao_impressao(alimentos_categoria[i]);
        }
    }else {
        for (int i = 0; i < qtd_alimentos_pedidos; i++) {
            funcao_impressao(alimentos_categoria[i]);
        }
    }

}

void todos_alimentos_categoria_x_ordem_alfabetica(const char* nomes_categoria[], struct alimento* lista_alimentos, int total_alimentos) {
    int categoria_escolha = 0;

    printf("\n\tESCOLHA A CATEGORIA:");
    for (int i = 0; i < 10; i++) {
        printf("\n\t[%d]- %s",i + 1,nomes_categoria[i]);
    }
    printf("\n\tinput: ");
    scanf("%d", &categoria_escolha);
    printf("\n\tAlimentos da categoria: %s\n", nomes_categoria[categoria_escolha - 1]);

    bubble_sort_descricao(total_alimentos, lista_alimentos, categoria_escolha);
}

void alimentos_ordem_decrescente_capacidade_energetica(const char* nomes_categoria[], struct alimento* lista_alimentos, int total_alimentos, int limite) {
    int categoria_escolha = input_padrao_categoria(nomes_categoria);
    int qtd_alimentos_pedidos = 0;

    if (limite == 1) {
        int qtd_alimentos_pedidos = input_padrao_quantidade_alimentos();
        bubble_sort_float(total_alimentos, lista_alimentos, categoria_escolha, &comparar_por_capacidade_energetica_decrescente, &imprimir_alimento_energia, qtd_alimentos_pedidos);
    }else {
        printf("\n\t alimentos em ordem decrescente de capacidade energetica\n");
        bubble_sort_float(total_alimentos, lista_alimentos, categoria_escolha, &comparar_por_capacidade_energetica_decrescente, &imprimir_alimento_energia, qtd_alimentos_pedidos);
    }
}

void alimentos_ordem_decrescente_quantidade_proteina(const char* nomes_categoria[], struct alimento* lista_alimentos, int total_alimentos) {
    int categoria_escolha = input_padrao_categoria(nomes_categoria);
    int qtd_alimentos_pedidos = input_padrao_quantidade_alimentos();

    printf("\n\t alimentos em ordem decrescente de quantidade de proteina\n");
    bubble_sort_float(total_alimentos, lista_alimentos, categoria_escolha, &comparar_por_quantidade_de_proteina_decrescente, &imprimir_alimento_proteina, qtd_alimentos_pedidos);
}

void alimentos_percentual_de_umidade_decrescente(const char* nomes_categoria[], struct alimento* lista_alimentos, int total_alimentos) {
    int categoria_escolha = input_padrao_categoria(nomes_categoria);
    int qtd_alimentos_pedidos = input_padrao_quantidade_alimentos();

    printf("\n\t alimentos em ordem decrescente de pecentual de umidade\n");
    bubble_sort_float(total_alimentos, lista_alimentos, categoria_escolha, &comparar_por_percentual_de_umidade_decrescente, &imprimir_alimento_umidade, qtd_alimentos_pedidos);
}

void alimentos_quantidade_de_carboidrato_decrescente(const char* nomes_categoria[], struct alimento* lista_alimentos, int total_alimentos) {
    int categoria_escolha = input_padrao_categoria(nomes_categoria);
    int qtd_alimentos_pedidos = input_padrao_quantidade_alimentos();

    printf("\n\t alimentos em ordem decrescente de quantidade de carboidrato\n");
    bubble_sort_float(total_alimentos, lista_alimentos, categoria_escolha, &comparar_por_quantidade_de_carboidrato_decrescente, &imprimir_alimento_carboidrato, qtd_alimentos_pedidos);
}

void alimentos_relacao_entre_energia_e_proteina_decrescente(const char* nomes_categoria[], struct alimento* lista_alimentos, int total_alimentos) {
    int categoria_escolha = input_padrao_categoria(nomes_categoria);
    int qtd_alimentos_pedidos = input_padrao_quantidade_alimentos();

    printf("\n\t alimentos em ordem decrescente de maior relacao entre energia e proteina\n");
    bubble_sort_float(total_alimentos, lista_alimentos, categoria_escolha, &comparar_por_relacao_energia_e_proteina_decrescente, &imprimir_alimento_relacao_energia_proteina, qtd_alimentos_pedidos);

}

void alimentos_relacao_entre_energia_e_carboidrato_decrescente(const char* nomes_categoria[], struct alimento* lista_alimentos, int total_alimentos) {
    int categoria_escolha = input_padrao_categoria(nomes_categoria);
    int qtd_alimentos_pedidos = input_padrao_quantidade_alimentos();

    bubble_sort_float(total_alimentos, lista_alimentos, categoria_escolha, &comparar_por_relacao_energia_e_carboidrato_decrescente, &imprimir_alimento_relacao_energia_carboidrato, qtd_alimentos_pedidos);
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
               "[3] para ver todos alimentos dentro de X categoria em ordem decrescente de capacidade energetica\n[4] para ver os N alimentos de X categoria com maior percentual de umidade em ordem decrescente\n"
               "[5] para ver N alimentos  de X categoria em ordem decrescente de capacidade energetica\n[6] para ver os N alimentos de X categoria em ordem decrescente em maior quantidade de proteina\n"
               "[7] para ver os N alimentos de X categoria em ordem decrescente em maior quantidade de carboidrato\n"
               "[8] para ver os N alimentos de X categoria que contem a relacao mais alta entre energia e proteina em ordem decrescente\n"
               "[9] para ver os N alimentos de X categoria que contem a relacao mais alta entre energia e carboidrato em ordem decrescente\n[10] para encerrar o programa\ninput: ");
        scanf("%d", &escolha);
        if (escolha == 1) {
            print_categorias(nomes_categoria);
        }else if (escolha == 2) {
            todos_alimentos_categoria_x_ordem_alfabetica(nomes_categoria, lista_alimentos, indice);
        }else if (escolha == 3) {
            alimentos_ordem_decrescente_capacidade_energetica(nomes_categoria, lista_alimentos, indice, 0);
        }else if (escolha == 4) {
            alimentos_percentual_de_umidade_decrescente(nomes_categoria, lista_alimentos, indice);
        }else if (escolha == 5) {
            alimentos_ordem_decrescente_capacidade_energetica(nomes_categoria, lista_alimentos, indice, 1);
        }else if (escolha == 6) {
            alimentos_ordem_decrescente_quantidade_proteina(nomes_categoria, lista_alimentos, indice);
        }else if (escolha == 7) {
            alimentos_quantidade_de_carboidrato_decrescente(nomes_categoria, lista_alimentos, indice);
        }else if (escolha == 8) {
            alimentos_relacao_entre_energia_e_proteina_decrescente(nomes_categoria, lista_alimentos, indice);
        }else if (escolha == 9) {
            alimentos_relacao_entre_energia_e_carboidrato_decrescente(nomes_categoria, lista_alimentos, indice);
        }
    }

    return 0;
}