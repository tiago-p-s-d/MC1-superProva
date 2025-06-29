#!/bin/bash

# --- SCRIPT DE TESTE PARA OPERAÇÃO MÓDULO EUCLIDIANO ---

# Função de referência que implementa a Divisão Euclidiana.
# A regra é que o resto (r) deve ser sempre não-negativo: 0 <= r < |divisor|.
function referencia_mod_euclidiano() {
    local dividendo=$1
    local divisor=$2

    if [ $divisor -eq 0 ]; then
        echo 0
        return
    fi

    # 1. Calcula o resto padrão do Bash (que pode ser negativo)
    local resto_padrao=$((dividendo % divisor))

    # 2. Se o resto for negativo, ajusta para ser positivo.
    #    - Para divisor positivo: r = r + d
    #    - Para divisor negativo: r = r + (-d) ou r = r - d
    if [ $resto_padrao -lt 0 ]; then
        if [ $divisor -gt 0 ]; then
            echo $((resto_padrao + divisor))
        else
            echo $((resto_padrao - divisor)) # Subtrai um número negativo (equivale a somar seu valor absoluto)
        fi
    else
        # Se o resto já for positivo, ele está correto.
        echo $resto_padrao
    fi
}


# --- ESTRUTURA PRINCIPAL DE TESTES (Idêntica à anterior) ---

# Verificação inicial: checar se o arquivo ./mod existe
if [ ! -f ./mod ]; then
    echo "ERRO: O arquivo executável './mod' não foi encontrado."
    exit 1
fi

# Inicializar contadores
test_count=0
passed=0
failed=0
# ... (o resto do script continua igual)
erros_positivos=0
erros_negativos=0
erros_misto1=0
erros_misto2=0

echo "Iniciando testes para a operação 'mod' (Regra Euclidiana)..."
echo "===================================="

while [ $test_count -lt 100 ]; do
    dividendo=$((RANDOM % 2001 - 1000))
    divisor=$((RANDOM % 2001 - 1000))
    while [ $divisor -eq 0 ]; do
        divisor=$((RANDOM % 2001 - 1000))
    done

    result=$(echo "$dividendo $divisor" | ./mod)
    
    # AGORA CHAMA A NOVA FUNÇÃO DE REFERÊNCIA
    expected=$(referencia_mod_euclidiano $dividendo $divisor)

    if [ "$result" == "$expected" ]; then
        echo "✅ PASS: $dividendo mod $divisor = $result (Esperado: $expected)"
        ((passed++))
    else
        echo "❌ FAIL: $dividendo mod $divisor = $result (Esperado: $expected)"
        ((failed++))

        if [ $dividendo -ge 0 ] && [ $divisor -gt 0 ]; then
            ((erros_positivos++))
        elif [ $dividendo -lt 0 ] && [ $divisor -lt 0 ]; then
            ((erros_negativos++))
        elif [ $dividendo -lt 0 ] && [ $divisor -gt 0 ]; then
            ((erros_misto1++))
        else
            ((erros_misto2++))
        fi
    fi
    ((test_count++))
done

# --- RELATÓRIO FINAL ---
echo "===================================="
echo "RELATÓRIO DE ERROS DETALHADO (MOD EUCLIDIANO):"
echo "Total de testes: $test_count"
echo "Aprovados: $passed"
echo "Falhas: $failed"
echo ""
echo "Distribuição dos erros:"
echo "- Ambos positivos: $erros_positivos erros"
echo "- Ambos negativos: $erros_negativos erros"
echo "- Dividendo negativo / Divisor positivo: $erros_misto1 erros"
echo "- Dividendo positivo / Divisor negativo: $erros_misto2 erros"
echo "===================================="

if [ $failed -eq 0 ]; then
    echo "🎉 Todos os testes passaram!"
    exit 0
else
    echo "⚠️ Alguns testes falharam. Verifique os padrões de erro acima."
    exit 1
fi