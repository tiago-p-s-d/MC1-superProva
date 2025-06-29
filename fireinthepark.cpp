#include <iostream>
#include <string>
#include <vector>
#include <limits> // Necessário para std::cin.ignore
#include "library/MC1_tiago.h" // Inclui sua biblioteca com as declarações

void pausar_e_limpar() {
    std::cout << "\nPressione Enter para continuar...";
    // cin.get() pode não funcionar como esperado se o buffer não for limpo primeiro
    // especialmente depois de um 'cin >>'. Esta linha garante a limpeza.
    if (std::cin.peek() == '\n') {
        std::cin.ignore();
    }
    std::cin.get();
    
    // --- ESCOLHA A LINHA CORRETA PARA O SEU SISTEMA OPERACIONAL ---
    system("clear"); // Para Linux e macOS
    // system("cls");   // Para Windows
}

int main() {
    int opcao;

    while (true) {
        std::cout << "--- PAINEL DE CONTROLE ---" << std::endl;
        std::cout << "1. Valor Absoluto" << std::endl;
        std::cout << "2. Divisao e Resto (Manual)" << std::endl;
        std::cout << "3. Cifra de Cesar" << std::endl;
        std::cout << "4. Calcular Numeros Primos em Intervalo" << std::endl;
        std::cout << "5. MDC (Fatoracao)" << std::endl;
        std::cout << "6. Identidade de Bezout (MDC Estendido)" << std::endl;
        std::cout << "7. Criptografia/Descriptografia RSA" << std::endl;
        std::cout << "0. Sair" << std::endl;
        std::cout << "--------------------------" << std::endl;
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;

        if (std::cin.fail()) {
            std::cout << "Entrada invalida. Por favor, digite um numero." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Limpa o buffer de entrada para o getline funcionar depois
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (opcao) {
            case 1: {
                int num;
                std::cout << "Digite um numero inteiro: ";
                std::cin >> num;
                std::cout << "Valor Absoluto: " << absolute_value(num) << std::endl;
                break;
            }
            case 2: {
                int dividendo, divisor;
                std::cout << "Digite o dividendo: ";
                std::cin >> dividendo;
                std::cout << "Digite o divisor: ";
                std::cin >> divisor;
                std::cout << "Quociente: " << divisao(dividendo, divisor) << std::endl;
                std::cout << "Resto: " << mod(dividendo, divisor) << std::endl;
                break;
            }
            case 3: {
                std::string texto;
                int chave;
                std::cout << "Digite o texto para a Cifra de Cesar: ";
                std::getline(std::cin, texto);
                std::cout << "Digite a chave (numero inteiro): ";
                std::cin >> chave;
                std::cout << "Resultado: " << cesar(texto, chave) << std::endl;
                break;
            }
            case 4: {
                int inicio, fim;
                std::cout << "Digite o valor inicial do intervalo: ";
                std::cin >> inicio;
                std::cout << "Digite o valor final do intervalo: ";
                std::cin >> fim;
                std::cout << "Numeros primos no intervalo [" << inicio << ", " << fim << "): ";
                calc_primos(inicio, fim);
                std::cout << std::endl;
                break;
            }
            case 5: {
                int a, b;
                std::cout << "Digite dois numeros para o MDC: ";
                std::cin >> a >> b;
                std::cout << "MDC(" << a << ", " << b << ") = " << mdc(a, b) << std::endl;
                break;
            }
            case 6: {
                int a, b;
                std::cout << "Digite dois numeros para a Identidade de Bezout: ";
                std::cin >> a >> b;
                BezoutResult res = identidadeBezout(a, b);
                std::cout << "MDC(" << a << ", " << b << ") = " << res.mdc << std::endl;
                std::cout << "s = " << res.s << ", t = " << res.t << std::endl;
                std::cout << "Equacao: " << res.mdc << " = (" << res.s << ")*" << a << " + (" << res.t << ")*" << b << std::endl;
                break;
            }
            case 7: {
                int p, q, modo;
                std::cout << "Digite dois numeros primos (p e q): ";
                std::cin >> p >> q;
                std::cout << "Digite 1 para criptografar ou 0 para descriptografar: ";
                std::cin >> modo;
                std::cout << "Digite a mensagem: ";
                std::string mensagem;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, mensagem);
                std::string resultado = RSA_BRUH(mensagem, p, q, modo);
                std::cout << "\nResultado Final: " << resultado << std::endl;
                break;
            }
            case 0: {
                std::cout << "Saindo... Tenha um otimo dia!" << std::endl;
                return 0;
            }
            default: {
                std::cout << "Opcao invalida. Tente novamente." << std::endl;
                break;
            }
        }
        pausar_e_limpar();
    }
    return 0;
}