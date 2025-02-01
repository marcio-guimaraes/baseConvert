#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Função para converter parte inteira de qualquer base para decimal
long long ToDecimalInteger(char *num, int baseOrigem) {
    long long decimal = 0;
    int len = strlen(num);
    for (int i = 0; i < len; i++) {
        char c = toupper(num[i]);
        int valor;
        if (isdigit(c)) {
            valor = c - '0';
        } else if (isalpha(c)) {
            valor = c - 'A' + 10;
        } else {
            printf("Caractere inválido na base %d: %c\n", baseOrigem, c);
            return -1;
        }
        if (valor >= baseOrigem) {
            printf("Caractere fora do limite da base %d: %c\n", baseOrigem, c);
            return -1;
        }
        decimal = decimal * baseOrigem + valor;
    }
    return decimal;
}

// Função para converter parte fracionária de qualquer base para decimal
double ToDecimalFraction(char *num, int baseOrigem) {
    double decimal = 0.0;
    double fator = 1.0 / baseOrigem;

    for (int i = 0; num[i] != '\0'; i++) {
        char c = toupper(num[i]);
        int valor;
        if (isdigit(c)) {
            valor = c - '0';
        } else if (isalpha(c)) {
            valor = c - 'A' + 10;
        } else {
            printf("Caractere inválido na base %d: %c\n", baseOrigem, c);
            return -1.0;
        }
        if (valor >= baseOrigem) {
            printf("Caractere fora do limite da base %d: %c\n", baseOrigem, c);
            return -1.0;
        }
        decimal += valor * fator;
        fator /= baseOrigem;
    }
    return decimal;
}

// Função para converter de decimal para qualquer base (parte inteira)
void FromDecimalInteger(long long decimal, int baseDestino, char *resultado) {
    char tabela[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i = 0;

    if (decimal == 0) {
        resultado[i++] = '0';
    }

    while (decimal > 0) {
        resultado[i++] = tabela[decimal % baseDestino];
        decimal /= baseDestino;
    }

    // Inverter o resultado para exibir na ordem correta
    resultado[i] = '\0';
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = resultado[j];
        resultado[j] = resultado[k];
        resultado[k] = temp;
    }
}

// Função para converter de decimal para qualquer base (parte fracionária)
void FromDecimalFraction(double decimal, int baseDestino, char *resultado, int precisao) {
    char tabela[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i = 0;

    while (precisao-- > 0 && decimal > 0.0) {
        decimal *= baseDestino;
        int parteInteira = (int)decimal;
        resultado[i++] = tabela[parteInteira];
        decimal -= parteInteira;
    }
    resultado[i] = '\0';
}

int main() {
    char numero[64], parteInteira[32], parteFracionaria[32];
    char resultadoInteira[64], resultadoFracionaria[64];
    int baseOrigem, baseDestino;
    long long decimalInteiro;
    double decimalFracionario;

    printf("Digite o número (use ponto como separador decimal, ex: 10.25): ");
    scanf("%s", numero);

    printf("Digite a base de origem (2 a 36): ");
    scanf("%d", &baseOrigem);

    printf("Digite a base de destino (2 a 36): ");
    scanf("%d", &baseDestino);

    if (baseOrigem < 2 || baseOrigem > 36 || baseDestino < 2 || baseDestino > 36) {
        printf("As bases devem estar entre 2 e 36.\n");
        return 1;
    }

    // Dividir número em parte inteira e fracionária
    char *ponto = strchr(numero, '.');
    if (ponto) {
        strncpy(parteInteira, numero, ponto - numero);
        parteInteira[ponto - numero] = '\0';
        strcpy(parteFracionaria, ponto + 1);
    } else {
        strcpy(parteInteira, numero);
        parteFracionaria[0] = '\0';
    }

    // Converter parte inteira e fracionária para decimal
    decimalInteiro = ToDecimalInteger(parteInteira, baseOrigem);
    if (decimalInteiro < 0) return 1;

    decimalFracionario = ToDecimalFraction(parteFracionaria, baseOrigem);
    if (decimalFracionario < 0) return 1;

    // Converter de decimal para a base destino
    FromDecimalInteger(decimalInteiro, baseDestino, resultadoInteira);
    FromDecimalFraction(decimalFracionario, baseDestino, resultadoFracionaria, 10); // Precisão de 10 casas decimais

    // Exibir resultado
    printf("Número convertido: %s.%s\n", resultadoInteira, resultadoFracionaria);

    return 0;
}
