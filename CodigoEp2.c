#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct
{
    int chave;
    int campoDaEstrutura[1];
} Registro1;

int lerEntradaSent(const char *arquivo, int *tamanho, Registro1 **vetor)
{

    FILE *entrada;
    entrada = fopen(arquivo, "r");

    if (entrada == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    fscanf(entrada, "%d", tamanho);

    // criar dinamicamente um vetor de estruturas registro1 de tamanho tamanho
    *vetor = (Registro1 *)malloc(sizeof(Registro1) * (*tamanho + 1));

    if (*vetor == NULL)
    {
        printf("Erro ao alocar memória!\n");
        fclose(entrada);
        return 1;
    }
    // inicializar o campo chave dos elementos do vetor com os numeros do arquivo
    int i;
    (*vetor)[0].chave = INT_MIN;
    for (i = 1; i <= *tamanho; i++)
    {
        if (fscanf(entrada, "%d", &(*vetor)[i].chave) != 1)
        {
            printf("Erro na leitura do arquivo ou dados insuficientes.\n");
            break; // Sai do loop se ocorrer erro de leitura
        }
    }
    return 0;
}

int lerEntrada(const char *arquivo, int *tamanho, Registro1 **vetor)
{

    FILE *entrada;
    entrada = fopen(arquivo, "r");

    if (entrada == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    fscanf(entrada, "%d", tamanho);

    // criar dinamicamente um vetor de estruturas registro1 de tamanho tamanho
    *vetor = (Registro1 *)malloc(sizeof(Registro1) * (*tamanho));

    if (*vetor == NULL)
    {
        printf("Erro ao alocar memória!\n");
        fclose(entrada);
        return 1;
    }
    // inicializar o campo chave dos elementos do vetor com os numeros do arquivo
    int i;
    for (i = 0; i < *tamanho; i++)
    {
        if (fscanf(entrada, "%d", &(*vetor)[i].chave) != 1)
        {
            printf("Erro na leitura do arquivo ou dados insuficientes.\n");
            break; // Sai do loop se ocorrer erro de leitura
        }
    }
    return 0;
}

void insercao(int n, Registro1 v[], const char *arquivo, int registro, int numerochaves)
{
    int i, j, mov, comp;
    mov = 0;
    comp = 0;
    Registro1 ch;
    v[0].chave = INT_MIN;
    clock_t hora_inicio, hora_fim;
    hora_inicio = clock();

    Registro1 *copia = (Registro1 *)malloc((n + 1) * sizeof(Registro1));

    if (copia == NULL)
    {
        printf("Erro ao alocar memória para a cópia do vetor!\n");
        return;
    }

    // Copiar o vetor original para a cópia
    for (i = 0; i < n; i++)
    {
        copia[i] = v[i];
    }

    copia[0].chave = INT_MIN;
    // Ordenação por inserção
    for (j = 2; j <= n; j++)
    {
        ch = copia[j];
        mov++;
        i = j - 1;
        while (copia[i].chave > ch.chave)
        {
            comp++;
            copia[i + 1] = copia[i];
            mov++;
            i = i - 1;
        }
        copia[i + 1] = ch;
        mov++;
    }
    comp++;
    hora_fim = clock();
    double tempo = ((double) (hora_fim - hora_inicio)) / CLOCKS_PER_SEC * 1000000.0;
    FILE *arq = fopen(arquivo, "a");
    fprintf(arq, "Insertion sort, %d, %d, %.2f, %d, %d\n", mov, comp, tempo, numerochaves, registro);
    fclose(arq);
    free(copia);
}

void selecao(int n, Registro1 v[], const char *arquivo, int registro, int numerochaves)
{
    int i, j, min, mov, comp;
    mov = 0;
    comp = 0;

    Registro1 x;

    Registro1 *copia = (Registro1 *)malloc(n * sizeof(Registro1));

    if (copia == NULL)
    {
        printf("Erro ao alocar memória para a cópia do vetor!\n");
        return;
    }

    // Copiar o vetor original para a cópia
    for (i = 0; i < n; i++)
    {
        copia[i] = v[i];
    }

    clock_t hora_inicio, hora_fim;
    hora_inicio = clock();

    for (int i = 0; i < n - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < n; j++)
        {
            comp++;
            if (copia[j].chave < copia[min].chave)
            {
                min = j;
            }
        }

        x = copia[i];
        mov++;
        copia[i] = copia[min];
        mov++;
        copia[min] = x;
        mov++;
    }

    hora_fim = clock();
     double tempo = ((double) (hora_fim - hora_inicio)) / CLOCKS_PER_SEC * 1000000.0;
     FILE *arq = fopen(arquivo, "a");
    fprintf(arq, "Selection sort, %d, %d, %.2f, %d, %d\n", mov, comp, tempo, numerochaves, registro);
    fclose(arq);
    free(copia);
}

void bolha(int n, Registro1 v[], const char *arquivo, int registro, int numerochaves)
{
    int ivet, j, comp, mov;
    mov = 0;
    comp = 0;
    Registro1 temp;
    bool flag = false;

    Registro1 *copia = (Registro1 *)malloc(n * sizeof(Registro1));

    if (copia == NULL)
    {
        printf("Erro ao alocar memória para a cópia do vetor!\n");
        return;
    }

    // Copiar o vetor original para a cópia
    for (int i = 0; i < n; i++)
    {
        copia[i] = v[i];
   
    }


    clock_t hora_inicio, hora_fim;
    hora_inicio = clock();

    // ivet é o “final” do vetor para onde deve ir o maior elemento (do fim para o início)
    for (ivet = n - 1; ivet > 0; ivet--) 
    {
        flag = false;
        // a cada passagem o maior elemento é descolado para a sua posição correta
        for (j = 0; j < ivet; j++) {
            // se ordem está errada para dois números consecutivos, troca os números
            comp++;
            if (copia[j].chave > copia[j + 1].chave)
            {
                flag = true;
                temp = copia[j];
                mov++;
                copia[j] = copia[j + 1];
                mov++;
                copia[j + 1] = temp;
                mov++;
            }
        }
        if (!flag)
            break;
    }

    hora_fim = clock();
double tempo = ((double) (hora_fim - hora_inicio)) / CLOCKS_PER_SEC * 1000000.0;    
FILE *arq = fopen(arquivo, "a");
    fprintf(arq, "Bubble sort, %d, %d, %.2f, %d, %d\n", mov, comp, tempo, numerochaves, registro);
    fclose(arq);
    free(copia);
}

void shellSort(int n, Registro1 v[], const char *arquivo, int registro, int numerochaves)
{
    int i, j, h, mov, comp;
    mov = 0;
    comp = 1;
    Registro1 ch;
    Registro1 *copia = malloc(sizeof(Registro1) * n);
    for (int i = 0; i < n; i++)
    {
        copia[i] = v[i];
    }
clock_t hora_inicio, hora_fim;
    hora_inicio = clock();

    for (h = 1; h < n; h = 3 * h + 1);
    while (h > 0)
    {
        h = (h - 1) / 3;
        for (j = h; j < n; j++)
        {
            ch = copia[j];
            mov++;
            i = j;
            comp++;
            while (i >= h && copia[i - h].chave > ch.chave)
            {
                
                copia[i] = copia[i - h];
                mov++;
                i = i - h;
            }
            copia[i] = ch;
            mov++;
        }
    }

hora_fim = clock();
double tempo = ((double) (hora_fim - hora_inicio)) / CLOCKS_PER_SEC * 1000000.0;
    FILE *arq = fopen(arquivo, "a");
    fprintf(arq, "Shell Sort, %d, %d, %.2f, %d, %d\n", mov, comp, tempo, numerochaves, registro);
    fclose(arq);
    free(copia);

}

void merge(Registro1 v[], int i, int m, int f, int *comp, int *mov)
{
    int n1 = m - i + 1;
    int n2 = f - m;

    Registro1 *L = malloc((n1 + 1) * sizeof(Registro1));
    Registro1 *R = malloc((n2 + 1) * sizeof(Registro1));

    L[n1].chave = INT_MAX;
    R[n2].chave = INT_MAX;

    for (int j = 0; j < n1; j++)
    {
        L[j] = v[i + j];
        (*mov)++;
    }

    for (int j = 0; j < n2; j++)
    {
        R[j] = v[m + j + 1];
        (*mov)++;
    }
    int kL = 0;
    int kR = 0;
    for (int k = i; k <= f; k++)
    {
        (*comp)++;
        if (L[kL].chave <= R[kR].chave)
        {
            v[k] = L[kL];
            (*mov)++;
            kL++;
        }
        else
        {
            v[k] = R[kR];
            (*mov)++;
            kR++;
        }
    }
}

void mergeSort(Registro1 v[], int i, int f, int *comp, int *mov)
{
    if (f > i)
    {
        int m = (f + i) / 2;
        mergeSort(v, i, m, comp, mov);
        mergeSort(v, m + 1, f, comp, mov);
        merge(v, i, m, f, comp, mov);
    }
}


void peneira(Registro1 v[], int raiz, int fundo, int* comp, int* mov);

void heapsort(int n, Registro1 v[], const char *arquivo, int registro, int numerochaves) {
	int i, mov, comp;
    Registro1 tmp;
    mov = 0;
    comp = 0;
    Registro1* copia = malloc(sizeof(Registro1)*n);

    for (int i = 0; i<n; i++) {
        copia[i] = v[i];
    }
clock_t hora_inicio, hora_fim;
    hora_inicio = clock();

	for (i = (n / 2); i >= 0; i--) {
		peneira(copia, i, n - 1, &comp, &mov);
	}

	for (i = n-1; i >= 1; i--) {
		tmp = copia[0];
        mov++;
		copia[0] = copia[i];
        mov++;
		copia[i] = tmp;
        mov++;
		peneira(copia, 0, i-1, &comp, &mov);
	}


hora_fim = clock();
double tempo = ((double) (hora_fim - hora_inicio)) / CLOCKS_PER_SEC * 1000000.0;
    FILE *arq = fopen(arquivo, "a");
    fprintf(arq, "Heap Sort, %d, %d, %.2f, %d, %d\n", mov, comp, tempo, numerochaves, registro);
    fclose(arq);
    free(copia);

}

void peneira(Registro1 v[], int raiz, int fundo, int* comp, int* mov) {
	int pronto, filhoMax;
    Registro1 tmp;

	pronto = 0;
	while ((raiz*2 <= fundo) && (!pronto)) {
        if (raiz*2 == fundo) {
			filhoMax = raiz * 2;
        }

		else if (v[raiz * 2].chave > v[raiz * 2 + 1].chave) {
			filhoMax = raiz * 2;
            (*comp)++;
		
        }
        
		else {
			filhoMax = raiz * 2 + 1;
		    (*comp)++;

        }

	if (v[raiz].chave < v[filhoMax].chave) {
		(*comp)++;
        tmp = v[raiz];
        (*mov)++;
		v[raiz] = v[filhoMax];
        (*mov)++;
		v[filhoMax] = tmp;
        (*mov)++;
		raiz = filhoMax;
    }
	else {
      pronto = 1;
	}
  
  
  
  
  
  }
}

int particao(Registro1 A[], int p, int r, int *mov, int *comp) {
    int x = A[r].chave; // Pivô é a chave do último elemento
    int i = p - 1;
    Registro1 temp;

    for (int j = p; j <= r - 1; j++) {
        (*comp)++;
        if (A[j].chave <= x) {
            i++;
            // Troca A[i] com A[j]
            temp = A[i];
            (*mov)++;
            A[i] = A[j];
            (*mov)++;
            A[j] = temp;
            (*mov)++;
        }
    }

    // Troca A[i + 1] com A[r]
    temp = A[i + 1];
    (*mov)++;
    A[i + 1] = A[r];
    (*mov)++;
    A[r] = temp;
    (*mov)++;

    return i + 1;
}

int particaoAleatoria(Registro1 A[], int p, int r, int *mov, int* comp) {
    int i;
    Registro1 temp;
    time_t t;

    // Inicializa gerador de número aleatório
    srand((unsigned) time(&t));

    // Escolhe um índice aleatório entre p e r
    i = p + rand() % (r - p + 1);

    // Troca A[i] com A[r]
    temp = A[r];
    (*mov)++;
    A[r] = A[i];
    (*mov)++;
    A[i] = temp;
    (*mov)++;

    // Chama a função de partição
    return particao(A, p, r, mov, comp);
}



void quickSortAleatorio(Registro1 A[], int p, int r, int *mov, int *comp) {
    if (p < r) {
        int q = particaoAleatoria(A, p, r, mov, comp);
        quickSortAleatorio(A, p, q - 1, mov, comp);
        quickSortAleatorio(A, q + 1, r, mov, comp);
    }
}

void auxrecursao(int n, Registro1 v[], const char *arquivo, int registro, int numerochaves, void (*funcao)(), int tipo)
{
    int mov = 0;
    int comp = 0;

    // Copiar o vetor original para a cópia
        Registro1 *copia = (Registro1 *)malloc(n * sizeof(Registro1));
        for (int i = 0; i < n; i++)
        {
            copia[i] = v[i];
          
        }

      if (tipo == 89)
    {

        clock_t hora_inicio, hora_fim;
        hora_inicio = clock();
        ((void (*)(Registro1[], int, int, int *, int *))funcao)(copia, 0, n - 1, &comp, &mov); // Casting para função quicksort
    hora_fim = clock();
double tempo = ((double) (hora_fim - hora_inicio)) / CLOCKS_PER_SEC * 1000000.0;
        FILE *arq = fopen(arquivo, "a");
        fprintf(arq, "Quick sort, %d, %d, %.2f, %d, %d\n", mov, comp, tempo, numerochaves, registro);
        fclose(arq);
        free(copia);
   
    }
    else if (tipo == 90)
    {
        clock_t hora_inicio, hora_fim;
        hora_inicio = clock();

        ((void (*)(Registro1[], int, int, int *, int *))funcao)(copia, 0, n - 1, &comp, &mov); // Casting para função com int como parâmetro

        hora_fim = clock();
double tempo = ((double) (hora_fim - hora_inicio)) / CLOCKS_PER_SEC * 1000000.0;
        FILE *arq = fopen(arquivo, "a");
        fprintf(arq, "Merge sort, %d, %d, %.2f, %d, %d\n", mov, comp, tempo, numerochaves, registro);
        fclose(arq);
        free(copia);
    }
}
void escrevenoarquivo (const char* entrada, const char* saida) {
 int tamanho;
 Registro1 *vetor;
    Registro1 *vetorsent;
lerEntradaSent(entrada, &tamanho, &vetorsent);
    insercao(tamanho, vetorsent, saida, 1, tamanho);

    lerEntrada(entrada, &tamanho, &vetor);
    selecao(tamanho, vetor, saida, 1, tamanho);
    bolha(tamanho, vetor, saida, 1, tamanho);
    shellSort(tamanho, vetor, saida, 1, tamanho);
    auxrecursao(tamanho, vetor, saida, 1, tamanho, (void *)mergeSort, 90); /*mergesort*/
    heapsort(tamanho, vetor, saida, 1, tamanho);
    auxrecursao(tamanho, vetor, saida, 1, tamanho, (void *)quickSortAleatorio, 89);
} 

int main(int argc, char *argv[])
{   
// dados aleatorios
FILE *a = fopen("dadosaleatorio.csv", "a");
    fprintf(a, "Algoritmo, Movimentação, Comparação, Tempo, Numero de Chaves, Registro\n");
    fclose(a);
escrevenoarquivo("100_aleatorio.txt", "dadosaleatorio.csv");
escrevenoarquivo("1000_aleatorio.txt", "dadosaleatorio.csv");
escrevenoarquivo("10000_aleatorio.txt", "dadosaleatorio.csv");

// dados crescente
FILE *b = fopen("dadoscrescente.csv","a");
    fprintf(b, "Algoritmo, Movimentação, Comparação, Tempo, Numero de Chaves, Registro\n");
    fclose(b);
escrevenoarquivo("100_crescente.txt", "dadoscrescente.csv");
escrevenoarquivo("1000_crescente.txt", "dadoscrescente.csv");
escrevenoarquivo("10000_crescente.txt", "dadoscrescente.csv");

// dados decrescente
FILE *c = fopen("dadosdecrescente.csv", "a");
    fprintf(c, "Algoritmo, Movimentação, Comparação, Tempo, Numero de Chaves, Registro\n");
    fclose(c);
escrevenoarquivo("100_decrescente.txt", "dadosdecrescente.csv");
escrevenoarquivo("1000_decrescente.txt", "dadosdecrescente.csv");
escrevenoarquivo("10000_decrescente.txt", "dadosdecrescente.csv");


 
    return 0;
}
