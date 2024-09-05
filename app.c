#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

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

    printf("{");
    for (i = 0; i < len; i++)
    {
        if (i < len - 1)
        {
            printf("%d, ", conjunto[i]);
        }
        else
        {
            printf("%d}\n", conjunto[i]);
        }
    }
}

void imprimir_produto_cartesiano(int *conjunto, int len)
{
    int i;

    printf("{");
    for (i = 0; i < len; i = i + 2)
    {
        if (i < len - 2)
        {
            printf("{%d, %d}, ", conjunto[i], conjunto[i + 1]);
        }
        else
        {
            printf("{%d, %d}}\n", conjunto[i], conjunto[i + 1]);
        }
    }
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

int *produto_cartesiano(int *conjunto_a, int len_a, int *conjunto_b, int len_b, int *len_res)
{
    *len_res = len_a * len_b;

    int i, j, len_atual = 0;
    int *conj_resposta = (int *)malloc(*len_res * sizeof(int));

    for (i = 0; i < len_a; i++)
    {
        for (j = 0; j < len_a; j++)
        {
            conj_resposta[len_atual++] = conjunto_a[i];
            conj_resposta[len_atual++] = conjunto_b[j];
        }
    }

    return conj_resposta;
}



int main()
{
    SetConsoleOutputCP(CP_UTF8);

    int len_a, len_b, len_res;
    int *conj_a = ler_conjunto('A', &len_a);
    int *conj_b = ler_conjunto('B', &len_b);
    int *conj_resposta;
    int opcao;

    while (true)
    {
        printf("0. Sair\n");
        printf("1. Inserir novos conjuntos A e B\n");
        printf("2. A U B\n");
        printf("3. A ∩ B\n");
        printf("4. A - B\n");
        printf("5. B - A\n");
        printf("6. A ∆ B\n");
        printf("7. A x B\n");

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
            conj_resposta = produto_cartesiano(conj_a, len_a, conj_b, len_b, &len_res);
            imprimir_produto_cartesiano(conj_resposta, len_res);
            break;

        default:
            printf("Opção inválida\n");
            break;
        }
    }

    free(conj_a);
    free(conj_b);

    return 0;
}
