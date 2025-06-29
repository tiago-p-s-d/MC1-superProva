#ifndef MC1_tiago
#define MC1_tiago

#include <string>


int absolute_value(int x);
int divisao(float dividendo, int divisor);
int piso(float value);
int teto(float value);
int mod(int value1, int value2);
void calc_primos(int value1, int value2);
std::string cesar(std::string texto_a_codificar, int chave);
    int find_index(std::string texto, char letra);
    bool is_uppercase(char letra);
int mdc(int a, int b);
struct BezoutResult {
    int mdc;
    int s;
    int t;
};
BezoutResult identidadeBezout(int a, int b);
std::string retornar_bezout(BezoutResult resultado);

std::string RSA_BRUH(std::string texto_a_codificar, int p, int q, int anderson);

#endif