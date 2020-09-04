#include "maquina.h"

/*
 *   0       1      2      3
 * opcode - end1 - end2 - end3

 * OPCODE |   FUNCAO:
    00    |   salvar na memória RAM
    01    |   somar
    02    |   subtrair
    03    |   pegar da memória RAM
    -1    |   halt        
*/

int abs(int n) {
    return (n < 0) ? -n : n;
}

int *alocaVetor(int n) {
    int *v = malloc(n * sizeof(int));
    return v;
}

int **aloca(int n) {
    int **mat = malloc(n * sizeof(int*));
    return mat;
}

void desaloca(int **m, int n) {
    for (int i = 0; i < n; i++)
        free(m[i]);
    free(m);
}

void menu(int *op) {
    printf("Digite a operação que deseja realizar:\n");
    printf("------------------------\n");
    printf("| 1  - SOMA            |\n");
    printf("|                      |\n");
    printf("| 2  - DIVISÃO INTEIRA |\n");
    printf("|                      |\n");
    printf("| 3  - SUBTRAÇÃO       |\n");
    printf("|                      |\n");
    printf("| 4  - MULTIPLICAÇÃO   |\n");
    printf("|                      |\n");
    printf("| 5  - ALEATORIO       |\n");
    printf("|                      |\n");
    printf("| 6  - EXPONENCIAÇÃO   |\n");
    printf("|                      |\n");
    printf("| 7  - P. ARITMÉTICA   |\n");
    printf("|                      |\n");
    printf("| 8  - FIBONACCI       |\n");
    printf("|                      |\n");
    printf("| 9  - P. GEOMÉTRICA   |\n");
    printf("|                      |\n");
    printf("| 10 - DIVISÃO REAL    |\n");
    printf("|                      |\n");
    printf("| 11 - RAIZ QUADRADA   |\n");
    printf("|                      |\n");
    printf("| 12 - FATORIAL        |\n");
    printf("------------------------\n");
    scanf("%d", op);
    system("clear");
}

void montarRam(Maquina *M) {
    srand(time(NULL));
    for (int i = 0; i < MAX; i++) {
        M->RAM[i] = random() % 1000;
    }
}

void maquinaTraduzida(Maquina *M) {
    int pos = 0;
    do {
        int *instrucao = M->memoInstrucoes[pos];
        maquinaInterpretada(M, instrucao);
        pos++;
    } while (pos < M->n);
    desaloca(M->memoInstrucoes, M->n);
}

void maquinaInterpretada(Maquina *M, int *instrucao) {
    int opcode = instrucao[0];
    // Levar para a RAM
    if (opcode == 0) {
        M->RAM[instrucao[2]] = instrucao[1];
    }
    // Somar
    else if (opcode == 1) {
        int end1 = instrucao[1];
        int end2 = instrucao[2];
        int end3 = instrucao[3];
        int soma = M->RAM[end1] + M->RAM[end2];
        M->RAM[end3] = soma;
    }
    // Subtrair
    else if (opcode == 2) {
        int end1 = instrucao[1];
        int end2 = instrucao[2];
        int end3 = instrucao[3];
        int subtracao = M->RAM[end1] - M->RAM[end2];
        M->RAM[end3] = subtracao;
    }
    // Pegar da RAM
    else if (opcode == 3) {
        instrucao[1] = M->RAM[instrucao[2]];
    }
}

void setMemoriaInstrucoes(Maquina *M, int opcode, int end1, int end2, int end3, int linha) {
    int *instrucao = alocaVetor(4);
    instrucao[0] = opcode;
    instrucao[1] = end1;
    instrucao[2] = end2;
    instrucao[3] = end3;
    M->memoInstrucoes[linha] = instrucao;
}

void aleatorio(Maquina *M) {
    srand(time(NULL));
    M->memoInstrucoes = aloca(10);
    M->n = 10;
    for (int i = 0; i < 9; i++) {
        int op = random() % 3;
        int e1 = random() % 100;
        int e2 = random() % 100;
        int e3 = random() % 100;
        setMemoriaInstrucoes(M, op, e1, e2, e3, i);
    }
    setMemoriaInstrucoes(M, -1, -1, -1, -1, 9);
    maquinaTraduzida(M);
}

void soma(Maquina *M, int num1, int num2) {
    M->memoInstrucoes = aloca(4);
    M->n = 4;
    setMemoriaInstrucoes(M, 0, num1, 0, -1, 0);
    setMemoriaInstrucoes(M, 0, num2, 1, -1, 1);
    setMemoriaInstrucoes(M, 1, 0, 1, 2, 2);
    setMemoriaInstrucoes(M, -1, -1, -1, -1, 3);
    maquinaTraduzida(M);
}

void subtracao(Maquina *M, int num1, int num2) {
    M->memoInstrucoes = aloca(4);
    M->n = 4;
    setMemoriaInstrucoes(M, 0, num1, 0, -1, 0);
    setMemoriaInstrucoes(M, 0, num2, 1, -1, 1);
    setMemoriaInstrucoes(M, 2, 0, 1, 2, 2);
    setMemoriaInstrucoes(M, -1, -1, -1, -1, 3);
    maquinaTraduzida(M);
}

void multiplicacao(Maquina *M, int num1, int num2) {
    M->memoInstrucoes = aloca(num2 + 3);
    M->n = num2 + 3;
    setMemoriaInstrucoes(M, 0, num1, 0, -1, 0);
    setMemoriaInstrucoes(M, 0, 0, 1, -1, 1);
    setMemoriaInstrucoes(M, -1, -1, -1, -1, num2 + 2);
    for (int i = 2; i < num2 + 2; i++) {
        setMemoriaInstrucoes(M, 1, 0, 1, 1, i);
    }
    maquinaTraduzida(M);
}

void divisao(Maquina *M, int num1, int num2) {
    M->memoInstrucoes = aloca(5);
    M->n = 5;

    setMemoriaInstrucoes(M, 0, num2, 0, -1, 0);
    setMemoriaInstrucoes(M, 0, num1, 1, -1, 1);
    setMemoriaInstrucoes(M, 0, 1, 2, -1, 2);
    setMemoriaInstrucoes(M, 0, 0, 3, -1, 3);
    setMemoriaInstrucoes(M, -1, -1, -1, -1, 4);
    maquinaTraduzida(M);

    int *instrucao = alocaVetor(4);
    instrucao[0] = 3;
    instrucao[1] = -1;
    instrucao[2] = 1;
    instrucao[3] = -1;
    maquinaInterpretada(M, instrucao);
    int dividendo = instrucao[1];

    instrucao[0] = 3;
    instrucao[1] = -1;
    instrucao[2] = 0;
    instrucao[3] = -1;
    maquinaInterpretada(M, instrucao);
    int divisor = instrucao[1];

    while (dividendo >= divisor) {
        instrucao[0] = 2;
        instrucao[1] = 1;
        instrucao[2] = 0;
        instrucao[3] = 1;
        maquinaInterpretada(M, instrucao);

        instrucao[0] = 1;
        instrucao[1] = 2;
        instrucao[2] = 3;
        instrucao[3] = 3;
        maquinaInterpretada(M, instrucao);

        instrucao[0] = 3;
        instrucao[1] = -1;
        instrucao[2] = 1;
        instrucao[3] = -1;
        maquinaInterpretada(M, instrucao);
        dividendo = instrucao[1];
    }
    free(instrucao);
}

void exponenciacao(Maquina *M, int base, int exp) {
    M->memoInstrucoes = aloca(3);
    M->n = 3;
    setMemoriaInstrucoes(M, 0, base, 3, -1, 0);
    setMemoriaInstrucoes(M, 0, 1, 1, -1, 1);
    setMemoriaInstrucoes(M, -1, -1, -1, -1, 2);
    maquinaTraduzida(M);
    
    int *instrucao = alocaVetor(4);
    instrucao[0] = 3;
    instrucao[1] = -1;
    instrucao[2] = 3;
    instrucao[3] = -1;
    maquinaInterpretada(M, instrucao);
    int b = instrucao[1];

    for (int i = 0; i < exp; i++) {
        instrucao[0] = 3;
        instrucao[1] = -1;
        instrucao[2] = 1;
        instrucao[3] = -1;
        maquinaInterpretada(M, instrucao);
        int prod = instrucao[1];
        multiplicacao(M, b, prod);
    }
    free(instrucao);
}

void PAritimetica(Maquina *M, int a1, int an, int razao) {
    numTermosPA(M, a1, an, razao);
    int *instrucao = alocaVetor(4);
    instrucao[0] = 3;
    instrucao[1] = -1;
    instrucao[2] = 2;
    instrucao[3] = -1;
    maquinaInterpretada(M, instrucao);
    int numTermos = instrucao[1];
    free(instrucao);

    M->memoInstrucoes = aloca(numTermos + 3);
    M->n = numTermos + 3;
    setMemoriaInstrucoes(M, 0, razao, 0, -1, 0);
    setMemoriaInstrucoes(M, 0, a1, 1, -1, 1);
    setMemoriaInstrucoes(M, -1, -1, -1, -1, numTermos + 2);
    for (int i = 2; i < numTermos + 2; i++) {
        setMemoriaInstrucoes(M, 1, 0, i - 1, i, i);
    }
    maquinaTraduzida(M);
}

void numTermosPA(Maquina *M, int a1, int an, int razao) {
    // Número de termos da PA = 1 + (an - a1) / razao
    int *instrucao = alocaVetor(4);
    subtracao(M, an, a1);
    instrucao[0] = 3;
    instrucao[1] = -1;
    instrucao[2] = 2;
    instrucao[3] = -1;
    maquinaInterpretada(M, instrucao);
    int numerador = instrucao[1];

    divisao(M, numerador, razao);
    instrucao[0] = 3;
    instrucao[1] = -1;
    instrucao[2] = 3;
    instrucao[3] = -1;
    maquinaInterpretada(M, instrucao);
    int numTermos = instrucao[1];

    soma(M, numTermos, 1);
    instrucao[0] = 3;
    instrucao[1] = -1;
    instrucao[2] = 2;
    instrucao[3] = -1;
    maquinaInterpretada(M, instrucao);
    numTermos = instrucao[1];
    free(instrucao);
}

void PGeometrica(Maquina *M, int a1, int termos, int razao) {
    M->memoInstrucoes = aloca(3);
    M->n = 3;
    setMemoriaInstrucoes(M, 0, razao, 0, -1, 0);
    setMemoriaInstrucoes(M, 0, a1, 2, -1, 1);
    setMemoriaInstrucoes(M, -1, -1, -1, -1, 2);
    maquinaTraduzida(M);

    int *instrucao = alocaVetor(4);
    for (int i = 3; i < termos + 3; i++) {
        instrucao[0] = 3;
        instrucao[1] = -1;
        instrucao[2] = i - 1;
        instrucao[3] = -1;
        maquinaInterpretada(M, instrucao);
        int anterior = instrucao[1];

        multiplicacao(M, anterior, razao);
        instrucao[0] = 3;
        instrucao[1] = -1;
        instrucao[2] = 1;
        instrucao[3] = -1;
        maquinaInterpretada(M, instrucao);
        int termoAtual = instrucao[1];

        instrucao[0] = 0;
        instrucao[1] = termoAtual;
        instrucao[2] = i;
        instrucao[3] = -1;
        maquinaInterpretada(M, instrucao);
    }
    free(instrucao);
}

void fibonacci(Maquina *M, int termos) {
    M->memoInstrucoes = aloca(termos + 1);
    M->n = termos + 1;
    setMemoriaInstrucoes(M, 0, 1, 0, -1, 0);
    setMemoriaInstrucoes(M, 0, 1, 1, -1, 1);
    setMemoriaInstrucoes(M, -1, -1, -1, -1, termos);
    for (int i = 2; i < termos; i++) {
        setMemoriaInstrucoes(M, 1, i - 1, i - 2, i, i);
    }
    maquinaTraduzida(M);
}

void somaPA(Maquina *M, int a1, int an, int razao, int termos) {
    M->memoInstrucoes = aloca(termos);
    M->n = termos;
    for (int i = 2; i <= termos; i++) {
        setMemoriaInstrucoes(M, 1, 1, i, 1, i - 2);
    }
    setMemoriaInstrucoes(M, -1, -1, -1, -1, termos - 1);
    maquinaTraduzida(M);
}

void somaPG(Maquina *M, int a1, int termos, int razao) {
    // Soma da PG = (a1 * (q^n - 1)) / (q - 1)
    exponenciacao(M, razao, termos);
    int *instrucao = alocaVetor(4);
    instrucao[0] = 3;
    instrucao[1] = -1;
    instrucao[2] = 1;
    instrucao[3] = -1;
    maquinaInterpretada(M, instrucao);
    int exp = instrucao[1];

    subtracao(M, exp, 1);
    instrucao[0] = 3;
    instrucao[1] = -1;
    instrucao[2] = 2;
    instrucao[3] = -1;
    maquinaInterpretada(M, instrucao);
    exp = instrucao[1];

    multiplicacao(M, a1, exp);
    instrucao[0] = 3;
    instrucao[1] = -1;
    instrucao[2] = 1;
    instrucao[3] = -1;
    maquinaInterpretada(M, instrucao);
    int numerador = instrucao[1];

    subtracao(M, razao, 1);
    instrucao[0] = 3;
    instrucao[1] = -1;
    instrucao[2] = 2;
    instrucao[3] = -1;
    maquinaInterpretada(M, instrucao);
    int denominador = instrucao[1];

    divisao(M, numerador, denominador);
}

void fatorial(Maquina *M, int num) {
    int *instrucao = alocaVetor(4);
    instrucao[0] = 0;
    instrucao[1] = 1;
    instrucao[2] = 1;
    instrucao[3] = -1;
    maquinaInterpretada(M, instrucao);

    for (int i = 2; i <= num; i++) {
        instrucao[0] = 3;
        instrucao[1] = -1;
        instrucao[2] = 1;
        instrucao[3] = -1;
        maquinaInterpretada(M, instrucao);
        int fat = instrucao[1];
        multiplicacao(M, fat, i);
    }
    free(instrucao);
}

void raizQuadrada(Maquina *M, int num) {
    int *instrucao = alocaVetor(4);
    for (int i = 1; i <= num; i++) {
        multiplicacao(M, i, i);
        instrucao[0] = 3;
        instrucao[1] = -1;
        instrucao[2] = 1;
        instrucao[3] = -1;
        maquinaInterpretada(M, instrucao);
        int quadrado = instrucao[1];
        
        if (quadrado >= num) {
            instrucao[0] = 0;
            instrucao[1] = i;
            instrucao[2] = 1;
            instrucao[3] = 0;
            maquinaInterpretada(M, instrucao);    
            break;
        }
    }
    free(instrucao);
}

void geraCasaDecimal(Maquina *M, int divisor, int posRAM) {
    int *instrucao = alocaVetor(4);
    // Pega o resto da RAM
    instrucao[0] = 3;
    instrucao[1] = -1;
    instrucao[2] = 1;
    instrucao[3] = -1;
    maquinaInterpretada(M, instrucao);
    int decimal = instrucao[1];

    multiplicacao(M, decimal, 10);
    // Pega o resultado da multiplicação
    instrucao[0] = 3;
    instrucao[1] = -1;
    instrucao[2] = 1;
    instrucao[3] = -1;
    maquinaInterpretada(M, instrucao);
    decimal = instrucao[1];

    divisao(M, decimal, divisor);
    // Pega a parte decimal da RAM
    instrucao[0] = 3;
    instrucao[1] = -1;
    instrucao[2] = 3;
    instrucao[3] = -1;
    maquinaInterpretada(M, instrucao);
    int inteiro = instrucao[1];

    // Leva a parte decimal para a posição da RAM
    instrucao[0] = 0;
    instrucao[1] = inteiro;
    instrucao[2] = posRAM;
    instrucao[3] = -1;
    maquinaInterpretada(M, instrucao);
    free(instrucao);
}

void divisaoReal(Maquina *M, int dividendo, int divisor, int qtd) {
    divisao(M, dividendo, divisor);
    int *instrucao = alocaVetor(4);

    instrucao[0] = 3;
    instrucao[1] = -1;
    instrucao[2] = 3;
    instrucao[3] = -1;
    maquinaInterpretada(M, instrucao);
    int inteiro = instrucao[1];

    instrucao[0] = 0;
    instrucao[1] = inteiro;
    instrucao[2] = 4;
    instrucao[3] = -1;
    maquinaInterpretada(M, instrucao);

    for (int i = 0; i < qtd; i++) {
        geraCasaDecimal(M, divisor, i + 5);
    }
    free(instrucao);
}