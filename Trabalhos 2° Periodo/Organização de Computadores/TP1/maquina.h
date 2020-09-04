#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10005

typedef struct {
    int **memoInstrucoes;
    int RAM[MAX];
    int n; // Número de linhas da memória
} Maquina;

/* Funções auxiliares */
int abs(int n);
int *alocaVetor(int n);
int **aloca(int n);
void menu(int *op);
void montarRam(Maquina *M);
void desaloca(int **m, int n);
void maquinaTraduzida(Maquina *M);
void maquinaInterpretada(Maquina *M, int *instrucao);
void geraCasaDecimal(Maquina *M, int divisor, int posRAM);
void setMemoriaInstrucoes(Maquina *M, int opcode, int end1, int end2, int end3, int linha);

/* Programas */
void aleatorio(Maquina *M);
void fatorial(Maquina *M, int num);
void fibonacci(Maquina *M, int termos);
void raizQuadrada(Maquina *M, int num);
void soma(Maquina *M, int num1, int num2);
void divisao(Maquina *M, int num1, int num2);
void subtracao(Maquina *M, int num1, int num2);
void exponenciacao(Maquina *M, int base, int exp);
void multiplicacao(Maquina *M, int num1, int num2);
void somaPG(Maquina *M, int a1, int termos, int razao);
void numTermosPA(Maquina *M, int a1, int an, int razao);
void PAritimetica(Maquina *M, int a1, int an, int razao);
void PGeometrica(Maquina *M, int a1, int termos, int razao);
void somaPA(Maquina *M, int a1, int an, int razao, int termos);
void divisaoReal(Maquina *M, int dividendo, int divisor, int qtd);