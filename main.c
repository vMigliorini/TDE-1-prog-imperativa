#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_DESCRICAO 65
#define TAMANHO_LISTA 100
#define MAX_ALIMENTOS_POR_LISTA 12 


struct alimento {
    int numero_alimento;
    char descricao[MAX_DESCRICAO];
    float umidade;
    float energia;
    float proteina;
    float carboidrato;
    int categoria;
};
// guarda apenas um ponteir para o alimento original e o valor pra ordenar.
struct PonteiroAlimento {
    struct alimento* original;
    union {
        float valor_numerico;
    } chave_ordenacao;
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



void insere_alimentos_lista(char* linha, int indice, struct alimento* lista_alimentos) {
    const char delimiter[] = ",";
    char *item;
    int contador_organizador = 0;

    linha[strcspn(linha, "\r\n")] = '\0';
    item = strtok(linha, delimiter);

    while (item != NULL) {
        contador_organizador += 1;
        if (contador_organizador == 1) {
            lista_alimentos[indice].numero_alimento = atoi(item);
        } else if (contador_organizador == 2) {
            strcpy(lista_alimentos[indice].descricao, item);
        } else if (contador_organizador == 3) {
            lista_alimentos[indice].umidade = atof(item);
        } else if (contador_organizador == 4) {
            lista_alimentos[indice].energia = atof(item);
        } else if (contador_organizador == 5) {
            lista_alimentos[indice].proteina = atof(item);
        } else if (contador_organizador == 6) {
            lista_alimentos[indice].carboidrato = atof(item);
        } else if (contador_organizador == 7) {
            if (strcmp(item, "Alimentos preparados") == 0) {
                lista_alimentos[indice].categoria = ALIMENTOS_PREPARADOS;
            } else if (strcmp(item, "Bebidas (alcoólicas e não alcoólicas)") == 0) {
                lista_alimentos[indice].categoria = BEBIDAS;
            } else if (strcmp(item, "Carnes e derivados") == 0) {
                lista_alimentos[indice].categoria = CARNES_E_DERIVADOS;
            } else if (strcmp(item, "Cereais e derivados") == 0) {
                lista_alimentos[indice].categoria = CEREAIS_E_DERIVADOS;
            } else if (strcmp(item, "Gorduras e óleos") == 0) {
                lista_alimentos[indice].categoria = GORDURAS_E_OLEOS;
            } else if (strcmp(item, "Leguminosas e derivados") == 0) {
                lista_alimentos[indice].categoria = LEGUMINOSAS_E_DERIVADOS;
            } else if (strcmp(item, "Leite e derivados") == 0) {
                lista_alimentos[indice].categoria = LEITE_E_DERIVADOS;
            } else if (strcmp(item, "Produtos açucarados") == 0) {
                lista_alimentos[indice].categoria = PRODUTOS_ACUCARADOS;
            } else if (strcmp(item, "Verduras hortaliças e derivados") == 0) {
                lista_alimentos[indice].categoria = VERDURAS_HORTALICAS_E_DERIVADOS;
            } else if (strcmp(item, "Frutas e derivados") == 0) {
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
        printf("\n\t[%d]- %s", i + 1, nomes_categoria[i]);
    }
    printf("\n\tinput: ");
    scanf("%d", &categoria_escolha);
    return categoria_escolha;
}

int input_padrao_quantidade_alimentos() {
    int qtd_alimentos_pedidos = 0;
    printf("Insira quantos alimentos você quer visualizar: ");
    scanf("%d", &qtd_alimentos_pedidos);
    return qtd_alimentos_pedidos;
}

void print_categorias(const char* nomes_categoria[]) {
    printf("\ncategorias:\n");
    for (int i = 0; i < 10; i++) {
        printf("- %s\n", nomes_categoria[i]);
    }
}


void imprimir_alimento_energia(struct alimento alim) {
    printf("\t%-70s %.2f kcal\n", alim.descricao, alim.energia);
}
void imprimir_alimento_proteina(struct alimento alim) {
    printf("\t%-70s %.2f g\n", alim.descricao, alim.proteina);
}
void imprimir_alimento_umidade(struct alimento alim) {
    printf("\t%-70s %.2f %%\n", alim.descricao, alim.umidade);
}
void imprimir_alimento_carboidrato(struct alimento alim) {
    printf("\t%-70s %.2f g\n", alim.descricao, alim.carboidrato);
}
void imprimir_alimento_relacao_energia_proteina(struct alimento alim) {
    if (alim.proteina == 0) {
        printf("\t%-70s (proteina zerada)\n", alim.descricao);
    } else {
        printf("\t%-70s %.2f\n", alim.descricao, alim.energia / alim.proteina);
    }
}
void imprimir_alimento_relacao_energia_carboidrato(struct alimento alim) {
    if (alim.carboidrato == 0) {
        printf("\t%-70s (carboidrato zerado)\n", alim.descricao);
    } else {
        printf("\t%-70s %.2f\n", alim.descricao, alim.energia / alim.carboidrato);
    }
}

int comparar_valores_decrescente(const void* a, const void* b) {
    const struct PonteiroAlimento* pa = (const struct PonteiroAlimento*)a;
    const struct PonteiroAlimento* pb = (const struct PonteiroAlimento*)b;

    if (pa->chave_ordenacao.valor_numerico < pb->chave_ordenacao.valor_numerico) {
        return 1;
    } else if (pa->chave_ordenacao.valor_numerico > pb->chave_ordenacao.valor_numerico) {
        return -1;
    }
    return 0;
}


void bubble_sort_ponteiro(int total_alimentos, struct alimento* lista_alimentos, int categoria_escolha,
                          void (*funcao_impressao)(struct alimento),
                          int (*funcao_comparacao)(const void*, const void*),
                          int qtd_alimentos_pedidos, const char* tipo_chave) {

    struct PonteiroAlimento alimentos_para_ordenar[TAMANHO_LISTA];
    int contador_local = 0;

    for (int i = 0; i < total_alimentos; i++) {
        if (lista_alimentos[i].categoria == categoria_escolha - 1) {
            alimentos_para_ordenar[contador_local].original = &lista_alimentos[i];

            if (strcmp(tipo_chave, "energia") == 0) alimentos_para_ordenar[contador_local].chave_ordenacao.valor_numerico = lista_alimentos[i].energia;
            else if (strcmp(tipo_chave, "proteina") == 0) alimentos_para_ordenar[contador_local].chave_ordenacao.valor_numerico = lista_alimentos[i].proteina;
            else if (strcmp(tipo_chave, "umidade") == 0) alimentos_para_ordenar[contador_local].chave_ordenacao.valor_numerico = lista_alimentos[i].umidade;
            else if (strcmp(tipo_chave, "carboidrato") == 0) alimentos_para_ordenar[contador_local].chave_ordenacao.valor_numerico = lista_alimentos[i].carboidrato;
            else if (strcmp(tipo_chave, "rel_energia_proteina") == 0) alimentos_para_ordenar[contador_local].chave_ordenacao.valor_numerico = (lista_alimentos[i].proteina > 0) ? lista_alimentos[i].energia / lista_alimentos[i].proteina : 0;
            else if (strcmp(tipo_chave, "rel_energia_carboidrato") == 0) alimentos_para_ordenar[contador_local].chave_ordenacao.valor_numerico = (lista_alimentos[i].carboidrato > 0) ? lista_alimentos[i].energia / lista_alimentos[i].carboidrato : 0;
            
            contador_local++;
        }
    }

    for (int i = 0; i < contador_local - 1; i++) {
        for (int j = 0; j < contador_local - 1 - i; j++) {
            if (funcao_comparacao(&alimentos_para_ordenar[j], &alimentos_para_ordenar[j + 1]) > 0) {
                struct PonteiroAlimento temp = alimentos_para_ordenar[j];
                alimentos_para_ordenar[j] = alimentos_para_ordenar[j + 1];
                alimentos_para_ordenar[j + 1] = temp;
            }
        }
    }

    int limite_impressao = (qtd_alimentos_pedidos == 0 || qtd_alimentos_pedidos > contador_local) ? contador_local : qtd_alimentos_pedidos;
    for (int i = 0; i < limite_impressao; i++) {
        funcao_impressao(*(alimentos_para_ordenar[i].original));
    }
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




void todos_alimentos_categoria_x_ordem_alfabetica(const char* nomes_categoria[], struct alimento* lista_alimentos, int total_alimentos) {
    int categoria_escolha = input_padrao_categoria(nomes_categoria);
    printf("\n\tAlimentos da categoria: %s\n", nomes_categoria[categoria_escolha - 1]);
    bubble_sort_descricao(total_alimentos, lista_alimentos, categoria_escolha);
}


void alimentos_ordem_decrescente_capacidade_energetica(const char* nomes_categoria[], struct alimento* lista_alimentos, int total_alimentos, int N_limitado) {
    int categoria_escolha = input_padrao_categoria(nomes_categoria);
    int qtd_alimentos_pedidos = 0;

    if (N_limitado) { 
        qtd_alimentos_pedidos = input_padrao_quantidade_alimentos();
        printf("\n\t%d alimentos com maior capacidade energética\n", qtd_alimentos_pedidos);
    } else { 
        printf("\n\tAlimentos em ordem decrescente de capacidade energética\n");
    }
    
    bubble_sort_ponteiro(total_alimentos, lista_alimentos, categoria_escolha, &imprimir_alimento_energia, &comparar_valores_decrescente, qtd_alimentos_pedidos, "energia");
}


void alimentos_ordem_decrescente_quantidade_proteina(const char* nomes_categoria[], struct alimento* lista_alimentos, int total_alimentos) {
    int categoria_escolha = input_padrao_categoria(nomes_categoria);
    int qtd_alimentos_pedidos = input_padrao_quantidade_alimentos();
    printf("\n\t%d alimentos com maior quantidade de proteína\n", qtd_alimentos_pedidos);
    bubble_sort_ponteiro(total_alimentos, lista_alimentos, categoria_escolha, &imprimir_alimento_proteina, &comparar_valores_decrescente, qtd_alimentos_pedidos, "proteina");
}

void alimentos_percentual_de_umidade_decrescente(const char* nomes_categoria[], struct alimento* lista_alimentos, int total_alimentos) {
    int categoria_escolha = input_padrao_categoria(nomes_categoria);
    int qtd_alimentos_pedidos = input_padrao_quantidade_alimentos();
    printf("\n\t%d alimentos com maior percentual de umidade\n", qtd_alimentos_pedidos);
    bubble_sort_ponteiro(total_alimentos, lista_alimentos, categoria_escolha, &imprimir_alimento_umidade, &comparar_valores_decrescente, qtd_alimentos_pedidos, "umidade");
}


void alimentos_quantidade_de_carboidrato_decrescente(const char* nomes_categoria[], struct alimento* lista_alimentos, int total_alimentos) {
    int categoria_escolha = input_padrao_categoria(nomes_categoria);
    int qtd_alimentos_pedidos = input_padrao_quantidade_alimentos();
    printf("\n\t%d alimentos com maior quantidade de carboidrato\n", qtd_alimentos_pedidos);
    bubble_sort_ponteiro(total_alimentos, lista_alimentos, categoria_escolha, &imprimir_alimento_carboidrato, &comparar_valores_decrescente, qtd_alimentos_pedidos, "carboidrato");
}


void alimentos_relacao_entre_energia_e_proteina_decrescente(const char* nomes_categoria[], struct alimento* lista_alimentos, int total_alimentos) {
    int categoria_escolha = input_padrao_categoria(nomes_categoria);
    int qtd_alimentos_pedidos = input_padrao_quantidade_alimentos();
    printf("\n\t%d alimentos com maior relação Energia/Proteína\n", qtd_alimentos_pedidos);
    bubble_sort_ponteiro(total_alimentos, lista_alimentos, categoria_escolha, &imprimir_alimento_relacao_energia_proteina, &comparar_valores_decrescente, qtd_alimentos_pedidos, "rel_energia_proteina");
}


void alimentos_relacao_entre_energia_e_carboidrato_decrescente(const char* nomes_categoria[], struct alimento* lista_alimentos, int total_alimentos) {
    int categoria_escolha = input_padrao_categoria(nomes_categoria);
    int qtd_alimentos_pedidos = input_padrao_quantidade_alimentos();
    printf("\n\t%d alimentos com maior relação Energia/Carboidrato\n", qtd_alimentos_pedidos);
    bubble_sort_ponteiro(total_alimentos, lista_alimentos, categoria_escolha, &imprimir_alimento_relacao_energia_carboidrato, &comparar_valores_decrescente, qtd_alimentos_pedidos, "rel_energia_carboidrato");
}



int main(void) {
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    FILE* texto_alimentos;
    texto_alimentos = fopen("alimentos.txt", "r");
    if (texto_alimentos == NULL) {
        perror("Erro ao abrir o arquivo 'alimentos.txt'");
        return 1;
    }
    struct alimento lista_alimentos[TAMANHO_LISTA];
    char linha[150]; 
    int total_alimentos_lidos = 0;
    const char* nomes_categoria[] = {
        "Alimentos preparados", "Bebidas (alcoólicas e não alcoólicas)", "Carnes e derivados", 
        "Cereais e derivados", "Gorduras e óleos", "Leguminosas e derivados", "Leite e derivados", 
        "Produtos açucarados", "Verduras hortaliças e derivados", "Frutas e derivados"
    };

    while (fgets(linha, sizeof(linha), texto_alimentos) != NULL && total_alimentos_lidos < TAMANHO_LISTA) {
        insere_alimentos_lista(linha, total_alimentos_lidos, lista_alimentos);
        total_alimentos_lidos++;
    }
    fclose(texto_alimentos);

    int escolha = 0;
    while (escolha != 10) {
        printf("\n** MENU DE OPCOES **\n"
            "[1] Listar todas as categorias de alimentos\n"
            "[2] Listar alimentos de uma categoria em ordem alfabetica\n"
            "[3] Listar TODOS os alimentos de uma categoria em ordem decrescente de energia\n"
            "[4] Listar os 'N' alimentos de uma categoria com maior umidade\n"
            "[5] Listar os 'N' alimentos de uma categoria com maior energia\n"
            "[6] Listar os 'N' alimentos de uma categoria com maior proteina\n"
            "[7] Listar os 'N' alimentos de uma categoria com maior carboidrato\n"
            "[8] Listar os 'N' alimentos com maior relacao Energia/Proteina\n"
            "[9] Listar os 'N' alimentos com maior relacao Energia/Carboidrato\n"
            "[10] Sair do programa\n"
            "Escolha uma opcao: ");

        scanf("%d", &escolha);
        
        switch(escolha) {
            case 1:
                print_categorias(nomes_categoria);
                break;
            case 2:
                todos_alimentos_categoria_x_ordem_alfabetica(nomes_categoria, lista_alimentos, total_alimentos_lidos);
                break;
            case 3:
                alimentos_ordem_decrescente_capacidade_energetica(nomes_categoria, lista_alimentos, total_alimentos_lidos, 0); // 0 = sem limite de N
                break;
            case 4:
                alimentos_percentual_de_umidade_decrescente(nomes_categoria, lista_alimentos, total_alimentos_lidos);
                break;
            case 5:
                alimentos_ordem_decrescente_capacidade_energetica(nomes_categoria, lista_alimentos, total_alimentos_lidos, 1); // 1 = com limite de N
                break;
            case 6:
                alimentos_ordem_decrescente_quantidade_proteina(nomes_categoria, lista_alimentos, total_alimentos_lidos);
                break;
            case 7:
                alimentos_quantidade_de_carboidrato_decrescente(nomes_categoria, lista_alimentos, total_alimentos_lidos);
                break;
            case 8:
                alimentos_relacao_entre_energia_e_proteina_decrescente(nomes_categoria, lista_alimentos, total_alimentos_lidos);
                break;
            case 9:
                alimentos_relacao_entre_energia_e_carboidrato_decrescente(nomes_categoria, lista_alimentos, total_alimentos_lidos);
                break;
            case 10:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    }

    return 0;
}