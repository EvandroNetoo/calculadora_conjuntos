#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

#define VERMELHO "\033[31m"
#define CIANO "\033[36m"
#define BRANCO "\033[37m"

void imprimir_menu()
{
    printf("0. Sair\n");
    printf("1. Inserir novos conjuntos A e B\n");
    printf("2. A U B\n");
    printf("3. A ∩ B\n");
    printf("4. A - B\n");
    printf("5. B - A\n");
    printf("6. A ∆ B\n");
    printf("7. A x B\n");
}

bool elemento_esta_no_conjunto(int elemento, int *conjunto, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        if (conjunto[i] == elemento)
        {
            return true;
        }
    }
    return false;
}

int *ler_conjunto(char letra_conjunto, int *len)
{
    printf("Digite o tamanho do conjunto %c: ", letra_conjunto);
    scanf("%d", len);

    int *conjunto = (int *)malloc(*len * sizeof(int));

    int valor, i;
    bool tentou;
    for (i = 0; i < *len; i++)
    {
        tentou = false;
        do
        {
            if (tentou)
            {
                printf("O número %d já está no conjunto %c.\n", valor, letra_conjunto);
            }
            printf("Digite o valor %d: ", i + 1);
            scanf("%d", &valor);
            tentou = true;
        } while (elemento_esta_no_conjunto(valor, conjunto, *len));

        conjunto[i] = valor;
    }

    return conjunto;
}

void imprimir(int *conjunto, int len)
{
    int i;

    printf(CIANO "{");
    for (i = 0; i < len; i++)
    {
        if (i < len - 1)
        {
            printf("%d, ", conjunto[i]);
        }
        else
        {
            printf("%d", conjunto[i]);
        }
    }
    printf("}\n" BRANCO);
}

int *uniao(int *conjunto_a, int len_a, int *conjunto_b, int len_b, int *len_res)
{
    int i, len_atual = 0, max_len = len_a + len_b;
    int *conj_resposta = (int *)malloc(max_len * sizeof(int));

    for (i = 0; i < len_a; i++)
    {
        conj_resposta[len_atual++] = conjunto_a[i];
    }

    for (i = 0; i < len_b; i++)
    {
        if (!elemento_esta_no_conjunto(conjunto_b[i], conjunto_a, len_a))
        {
            conj_resposta[len_atual++] = conjunto_b[i];
        }
    }

    *len_res = len_atual;

    conj_resposta = (int *)realloc(conj_resposta, (*len_res) * sizeof(int));

    return conj_resposta;
}

int *interseccao(int *conjunto_a, int len_a, int *conjunto_b, int len_b, int *len_res)
{
    int i, len_atual = 0, max_len = min(len_a, len_b);

    int *conj_resposta = (int *)malloc(max_len * sizeof(int));

    for (i = 0; i < len_a; i++)
    {
        if (elemento_esta_no_conjunto(conjunto_a[i], conjunto_b, len_b))
        {
            conj_resposta[len_atual++] = conjunto_a[i];
        }
    }

    *len_res = len_atual;

    conj_resposta = (int *)realloc(conj_resposta, (*len_res) * sizeof(int));

    return conj_resposta;
}

int *diferenca(int *conjunto_a, int len_a, int *conjunto_b, int len_b, int *len_res)
{
    int i, len_atual = 0, max_len = len_a;
    int *conj_resposta = (int *)malloc(max_len * sizeof(int));

    for (i = 0; i < len_a; i++)
    {
        if (!elemento_esta_no_conjunto(conjunto_a[i], conjunto_b, len_b))
        {
            conj_resposta[len_atual++] = conjunto_a[i];
        }
    }

    *len_res = len_atual;

    conj_resposta = (int *)realloc(conj_resposta, (*len_res) * sizeof(int));

    return conj_resposta;
}

int *diferenca_simetrica(int *conjunto_a, int len_a, int *conjunto_b, int len_b, int *len_res)
{
    int len_uniao, len_interseccao;
    int *conj_uniao = uniao(conjunto_a, len_a, conjunto_b, len_b, &len_uniao);
    int *conj_interseccao = interseccao(conjunto_a, len_a, conjunto_b, len_b, &len_interseccao);

    int *conj_resposta = diferenca(conj_uniao, len_uniao, conj_interseccao, len_interseccao, len_res);

    return conj_resposta;
}

typedef struct
{
    int x;
    int y;
} Coordenada;

void imprimir_produto_cartesiano(Coordenada *conjunto, int len)
{
    int i;
    Coordenada coordenada;

    printf(CIANO "{");
    for (i = 0; i < len; i++)
    {
        coordenada = conjunto[i];
        if (i < len - 1)
        {
            printf("{%d, %d}, ", coordenada.x, coordenada.y);
        }
        else
        {
            printf("{%d, %d}", coordenada.x, coordenada.y);
        }
    }
    printf("}\n" BRANCO);
}

Coordenada *produto_cartesiano(int *conjunto_a, int len_a, int *conjunto_b, int len_b, int *len_res)
{

    int i, j, len_atual = 0;
    Coordenada *plano_cartesiano = (Coordenada *)malloc(len_a * len_b * sizeof(Coordenada));
    Coordenada coordenada;

    for (i = 0; i < len_a; i++)
    {
        for (j = 0; j < len_b; j++)
        {
            coordenada.x = conjunto_a[i];
            coordenada.y = conjunto_b[j];

            plano_cartesiano[len_atual++] = coordenada;
        }
    }

    *len_res = len_atual;

    plano_cartesiano = (Coordenada *)realloc(plano_cartesiano, (*len_res) * sizeof(Coordenada));

    return plano_cartesiano;
}

int comparador(const void* a, const void* b) {
   return (*(int*)a - *(int*)b);
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    int len_a, len_b, len_res;
    int *conj_a = ler_conjunto('A', &len_a);
    qsort(conj_a, len_a, sizeof(int), comparador);
    int *conj_b = ler_conjunto('B', &len_b);
    qsort(conj_b, len_b, sizeof(int), comparador);
    int *conj_resposta;
    int opcao;
    Coordenada *plano_cartesiano;

    while (true)
    {
        imprimir_menu();

        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
            free(conj_a);
            free(conj_b);
            return 0;

        case 1:
            conj_a = ler_conjunto('A', &len_a);
            conj_b = ler_conjunto('B', &len_b);
            break;

        case 2:
            conj_resposta = uniao(conj_a, len_a, conj_b, len_b, &len_res);
            imprimir(conj_resposta, len_res);
            break;

        case 3:
            conj_resposta = interseccao(conj_a, len_a, conj_b, len_b, &len_res);
            imprimir(conj_resposta, len_res);
            break;

        case 4:
            conj_resposta = diferenca(conj_a, len_a, conj_b, len_b, &len_res);
            imprimir(conj_resposta, len_res);
            break;

        case 5:
            conj_resposta = diferenca(conj_b, len_b, conj_a, len_a, &len_res);
            imprimir(conj_resposta, len_res);
            break;

        case 6:
            conj_resposta = diferenca_simetrica(conj_a, len_a, conj_b, len_b, &len_res);
            imprimir(conj_resposta, len_res);
            break;

        case 7:
            plano_cartesiano = produto_cartesiano(conj_a, len_a, conj_b, len_b, &len_res);
            imprimir_produto_cartesiano(plano_cartesiano, len_res);
            break;

        default:
            printf(VERMELHO "Opção inválida\n" BRANCO);
            break;
        }
    }

    free(conj_a);
    free(conj_b);

    return 0;
}
