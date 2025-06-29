#include "MC1_tiago.h"
#include <bits/stdc++.h>

//rapaz, trabalhinho q deu fzr rsa viu
//overall, gostei do trabalho, muito divertido quebrar a cabeça tentando fzr os codigos
//tbh, tentei fzr tudo sem usar nenhuma ajuda externa, mas precisei de ajuda na rsa
//do mais é isso

int absolute_value(int x){
    return (x < 0) ? -x : x; 
}
int divisao(float dividendo, int divisor){
    int resto = dividendo, q = 0;
    // se o divisor for maior que o dividendo, o resto é o proprio dividendo, e o quociente é 0


    //avaliando em retrospectiva, talvez while seja melhor. mas eu to com preguiça de aprender while
    for(; !((resto >=0) && resto < absolute_value(divisor)); ){
        
        
        if(dividendo > 0 && divisor > 0){
            q++;
        }
        else if(dividendo > 0 && divisor < 0){
            q--;
        }
        else if(dividendo < 0 && divisor > 0){
            q--;
        }
        else if(dividendo < 0 && divisor < 0){
            q++;
        }
       resto = dividendo - divisor*q;
    }
    return q;

}
int piso(float value){
    float newvalue = divisao(value, 1);
    if(value < 0 && newvalue != value){
        newvalue--;
    }
    return newvalue;
}
int teto(float value){
    float newvalue = divisao(value, 1);
    if(value > 0 && newvalue != value){
        newvalue++;
    }
    return newvalue;
}
int mod(int value1, int value2){
    if(value2 == 0){
        return 0; 
    }
    int resto = value1 - divisao(value1, value2) * value2;
    return resto;
}

void calc_primos(int value1, int value2){
    int count = 0;
    for(int i = value1; i < value2; i++){
        bool eh_primo = true;
        for(int k = 1; k < i; k++){
            if(mod(i, k)==0){
                count++;
                if(count > 2) {
                    eh_primo = false;
                     // se o número tiver mais de dois divisores
                }
            }
        }
        if(eh_primo && i > 1){ 
            std::cout << i << " ";
        }
        count = 0; // resetando o contador de divisores
    }
}

int find_index(std::string texto, char letra){
    for(int i = 0; i < texto.size(); i++){
        if(texto[i] == letra){
            return i;
        }
    }
    return -1; // se a letra não for encontrada, retorna -1
}
bool is_uppercase(char letra){
    std::string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i = 0; i < ABC.size(); i++){
        if(ABC[i] == letra){
            return true;
        }
    }
    return false; // se a letra não for maiúscula, retorna false
}
std::string cesar(std::string texto_a_codificar, int chave){
    std::string abc = "abcdefghijklmnopqrstuvwxyz";
    std::string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string resultado = "";
    int __chave;
    chave = mod(chave, 26);
    std::cout << chave << " essa eh a chave" << std::endl; // garantindo que a chave esteja entre 0 e 25
    if(chave < 0){
        __chave = 26 + chave; // convertendo chave negativa para positiva
    }
    else{
        __chave = chave;
    }

    for(int i = 0; i < texto_a_codificar.size(); i++){
        if(texto_a_codificar[i] == ' '){
            resultado += ' '; // preservando espaços
            continue;
        }
        if(is_uppercase(texto_a_codificar[i])){
            resultado = resultado + ABC[mod(find_index(ABC, texto_a_codificar[i]) + __chave, 26)];
        }else{
            resultado = resultado + abc[mod(find_index(abc, texto_a_codificar[i])+ __chave, 26)];
        }
    }
    return resultado;
}

int mdc(int a, int b){
    bool mdcFound = false;
    int mdcValue = 1;

    for(int k = 2; k <= a && k <= b; k++){
        // ENQUANTO k for um divisor comum, continue dividindo
        while (mod(a, k) == 0 && mod(b, k) == 0) {
            std::cout << a << ", " << b << " | " << k << " ✅" << std::endl;
            mdcValue = mdcValue * k; // Acumula o fator no MDC
            a = divisao(a, k);       // Atualiza o valor de a
            b = divisao(b, k);       // Atualiza o valor de b
        }
    }
    
    return mdcValue;
}




BezoutResult identidadeBezout(int a, int b) {
    // Caso base da recursão
    if (b == 0) {
        return {a, 1, 0};
    }

    BezoutResult resultado_recursivo = identidadeBezout(b, mod(a, b));
    int s = resultado_recursivo.t;
    int t = resultado_recursivo.s - divisao(a, b) * resultado_recursivo.t;

    return {resultado_recursivo.mdc, s, t};
}

const std::string ALFABETO = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 .,;:?!@#%&*";



int letraPraNumero(char c) {
    size_t pos = ALFABETO.find(c); // Procura o caractere na string ALFABETO
    if (pos != std::string::npos) { // 'npos' significa "não encontrado"
        return pos + 10; // 'A' (índice 0) -> 10, 'B' (índice 1) -> 11, etc.
    }
    return -1; // Retorna -1 para caracteres que não estão no nosso alfabeto
}

char numeroPraLetra(int num) {
    int index = num - 10; // Remove o offset para achar o índice
    // Verifica se o índice é válido para o tamanho do nosso alfabeto
    if (index >= 0 && index < ALFABETO.length()) {
        return ALFABETO[index];
    }
    return '?'; // Retorna '?' se o número for inválido
}

int modInverse(int a, int m) {
    BezoutResult res = identidadeBezout(a, m); 
    if (res.mdc != 1) {
        return -1; 
    }
    return (res.s % m + m) % m;
}

int modular_pow_int(int base, int exp, int mod) {
    int res = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (1LL * res * base) % mod; 
            // 1LL é um truque para garantir que a multiplicação não cause overflow
        }
        base = (1LL * base * base) % mod;
        // Novamente, 1LL é um truque. A versão pura seria base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

std::vector<long long> encodeMessage(const std::string& message, long long n) {
    std::vector<long long> encodedBlocks;
    for (char c : message) {
        int num = letraPraNumero(c);
        
        // Sua função letraPraNumero retorna 0 para inválidos (como espaço)
        if (num == 0) {
            continue; // Pula o caractere inválido
        }

        // Tenta juntar o número do caractere atual ao último bloco existente
        if (!encodedBlocks.empty() && (encodedBlocks.back() * 100 + num) < n) {
            encodedBlocks.back() = encodedBlocks.back() * 100 + num;
        } else {
            // Se não puder juntar (ou se for o primeiro bloco), cria um novo
            encodedBlocks.push_back(num);
            //push back tira o ultimo numero se n me engano
        }
    }
    return encodedBlocks;
}

// Substitua sua decodeMessage por esta
std::string decodeMessage(const std::vector<long long>& decryptedBlocks) {
    std::string finalMessage = "";
    for (long long block : decryptedBlocks) {
        std::string blockMessage = "";
        if (block == 0) continue;

        long long tempBlock = block; // Usa uma cópia para não alterar o original
        do {
            int num = tempBlock % 100;
            tempBlock /= 100;
            // Garante que o número é válido antes de tentar converter
            if (numeroPraLetra(num) != '?') {
                blockMessage = numeroPraLetra(num) + blockMessage;
            }
        } while (tempBlock > 0);

        finalMessage += blockMessage;
    }
    return finalMessage;
}
// --- FUNÇÃO RSA UNIFICADA (A que sua main chama) ---
std::string RSA_BRUH(std::string mensagem, int p, int q, int modo) {
    // Parte comum: Preparação das chaves
    long long n = (long long)p * q;
    long long phi = (long long)(p - 1) * (q - 1);
    long long e = 3;
    while (mdc(e, phi) != 1) {
        e += 2;
    }

    // Parte específica: Criptografar ou Descriptografar
    if (modo == 1) { // MODO CRIPTOGRAFAR
        std::vector<long long> blocos_M = encodeMessage(mensagem, n);
        std::stringstream resultado_cifrado;
        for (size_t i = 0; i < blocos_M.size(); ++i) {
            long long c_bloco = modular_pow_int(blocos_M[i], e, n);
            resultado_cifrado << c_bloco << (i < blocos_M.size() - 1 ? " " : "");
        }
        return resultado_cifrado.str();
    } 
    else if (modo == 0) { // MODO DESCRIPTOGRAFAR
        long long d = modInverse(e, phi);
        std::vector<long long> blocos_C;
        std::stringstream ss(mensagem);
        long long bloco_num;
        while (ss >> bloco_num) {
            blocos_C.push_back(bloco_num);
        }
        std::vector<long long> blocos_M_decifrados;
        for (long long c_bloco : blocos_C) {
            blocos_M_decifrados.push_back(modular_pow_int(c_bloco, d, n));
        }
        return decodeMessage(blocos_M_decifrados);
    }
    
    return "Modo invalido. Use 1 para criptografar ou 0 para descriptografar.";
}
