# Bibliotecas e definições

## Bibliotecas

São importadas bibliotecas padrão para:

- **Entrada e saída de dados** (`stdio.h`)
- **Alocação dinâmica de memória** (`stdlib.h`)
- **Uso de tipos booleanos** (`stdbool.h`)
- **Funções específicas do Windows**, como a definição do código de página UTF-8 no console (`windows.h`).

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
```

## Macros max e min

Definem funções inline para calcular o valor máximo e mínimo entre dois valores, permitindo a reutilização dessas operações em diversas partes do código de forma otimizada.

```c
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
```

## Códigos de Cores

Define códigos de cor ANSI para estilizar a saída no console. As cores disponíveis são:

- **Vermelho** (`VERMELHO`)
- **Ciano** (`CIANO`)
- **Branco** (`BRANCO`)

Esses códigos são usados para tornar a interface mais intuitiva ao usuário.
```c
#define VERMELHO "\033[31m"
#define CIANO "\033[36m"
#define BRANCO "\033[37m"
```