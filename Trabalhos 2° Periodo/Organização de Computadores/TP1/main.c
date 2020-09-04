/*
 *  Leandro Rodrigues Rocha
 *  Turma: 11
 *  Matrícula: 19.2.4085
 */

#include "maquina.h"

int main() {
    int op;
    Maquina M;

    montarRam(&M);
    menu(&op);

    if (op == 1) {
        int n1, n2;
        printf("Digite os dois numeros para serem somados: ");
        scanf("%d %d", &n1, &n2);
        soma(&M, n1, n2);
        printf("Resultado da soma: %d\n", M.RAM[2]);
    }
    else if (op == 2) {
        int n1, n2;
        printf("Digite dividendo e o divisor: ");
        scanf("%d%d", &n1, &n2);
        if (n2 == 0) {
            printf("Indefinido\n");
        }
        else {
            divisao(&M, abs(n1), abs(n2));
            int res = M.RAM[3];
            if ((n1 < 0 && n2 > 0) || (n1 > 0 && n2 < 0)) {
                multiplicacao(&M, -1, res);
                res = M.RAM[1];
            }
            printf("Resultado da divisão: %d\n", res);
            printf("Resto = %d\n", M.RAM[1]);
        }
    }
    else if (op == 3) {
        int n1, n2;
        printf("Digite os dois numeros a serem subtraidos: ");
        scanf("%d %d", &n1, &n2);
        subtracao(&M, n1, n2);
        printf("Resultado da subtração: %d\n", M.RAM[2]);
    }
    else if (op == 4) {
        int n1, n2;
        printf("Digite os dois numeros a serem multiplicados: ");
        scanf("%d %d", &n1, &n2);
        multiplicacao(&M, abs(n1), abs(n2));
        if ((n1 < 0 && n2 > 0) || (n1 > 0 && n2 < 0)) {
            multiplicacao(&M, -1, M.RAM[1]);
        }
        printf("Resultado da multiplicação: %d\n", M.RAM[1]);
    }
    else if (op == 5) {
        aleatorio(&M);
        for (int i = 0; i < 100; i++) {
            printf("RAM[%d] = %d\n", i, M.RAM[i]);
        }
    }
    else if (op == 6) {
        int base, exp, res;
        printf("Digite a base e o expoente: ");
        scanf("%d%d", &base, &exp);
        if (exp == 0) res = 1;
        else {
            exponenciacao(&M, base, exp);
            res = M.RAM[1];
        }
        printf("Resultado de %d elevado a %d = %d\n", base, exp, res);
    }
    else if (op == 7) {
        int a1, an, razao;
        printf("Digite o primeiro e o útimo termo e a razão: ");
        scanf("%d%d%d", &a1, &an, &razao);

        numTermosPA(&M, a1, an, razao);
        int numTermos = M.RAM[2];
        
        printf("Número de termos da PA = %d\n\n", numTermos);
        PAritimetica(&M, a1, an, razao);
        
        printf("Progressão Aritimética: ");
        for (int i = 1; i <= numTermos; i++)
            printf("%d ", M.RAM[i]);
        printf("\n\n");

        somaPA(&M, a1, an, razao, numTermos);
        printf("Soma da PA = %d\n", M.RAM[1]);
    }
    else if (op == 8) {
        int termos;
        printf("Digite o número de termos que você deseja ver: ");
        scanf("%d", &termos);
        fibonacci(&M, termos);
        for (int i = 0; i < termos; i++) {
            printf("%d ", M.RAM[i]);
        }
        printf("\n");
    }
    else if (op == 9) {
        int a1, numTermos, razao;
        printf("Digite o primeiro termo, o número de termos e a razão: ");
        scanf("%d%d%d", &a1, &numTermos, &razao);
        PGeometrica(&M, a1, numTermos, razao);
        
        printf("Progressão Geométrica: ");
        for (int i = 2; i < numTermos + 2; i++)
            printf("%d ", M.RAM[i]);
        printf("\n\n");

        somaPG(&M, a1, numTermos, razao);
        printf("Soma da PG = %d\n", M.RAM[3]);
    }
    else if (op == 10) {
        int n1, n2, qtd;
        printf("Digite dividendo, o divisor e a quantidade de casas decimais: ");
        scanf("%d%d%d", &n1, &n2, &qtd);
        if (n2 == 0) {
            printf("Indefinido\n");
        }
        else {
            divisaoReal(&M, n1, n2, qtd);
            printf("Resultado da divisão: %d.", M.RAM[4]);
            for (int i = 0; i < qtd; i++) {
                printf("%d", M.RAM[i + 5]);
            }
            printf("\n");
        }
    }
    else if (op == 11) {
        int num;
        printf("Dogite um número: ");
        scanf("%d", &num);
        raizQuadrada(&M, num);
        printf("Raiz quadrada de %d = %d\n", num, M.RAM[1]);
    }
    else if (op == 12) {
        int num;
        printf("Digite um número: ");
        scanf("%d", &num);
        fatorial(&M, num);
        printf("Fatorial de %d = %d\n", num, M.RAM[1]);
    }
    return 0;
}