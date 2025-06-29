#!/bin/bash

# Função de referência para verificação
function referencia() {
    local dividendo=$1
    local divisor=$2
    if [ $divisor -eq 0 ]; then
        echo 0
        return
    fi
    
    if [ $dividendo -ge 0 ] && [ $divisor -gt 0 ]; then
        echo $((dividendo / divisor))
    elif [ $dividendo -ge 0 ] && [ $divisor -lt 0 ]; then
        echo $((-(dividendo / (-divisor))))
    elif [ $dividendo -lt 0 ] && [ $divisor -gt 0 ]; then
        echo $((-((-dividendo + divisor - 1) / divisor)))
    else
        echo $(((-dividendo + (-divisor) - 1) / (-divisor)))
    fi
}

# Inicializar contadores
test_count=0
passed=0
failed=0
erros_positivos=0
erros_negativos=0
erros_misto1=0    # dividendo -, divisor +
erros_misto2=0    # dividendo +, divisor -

echo "Iniciando testes..."
echo "===================================="

while [ $test_count -lt 100 ]; do
    # Gerar números aleatórios entre -1000 e 1000 (exceto divisor 0)
    dividendo=$((RANDOM % 2001 - 1000))
    divisor=$((RANDOM % 2000 - 1000))
    
    # Garantir que divisor não seja zero
    while [ $divisor -eq 0 ]; do
        divisor=$((RANDOM % 2000 - 1000))
    done
    
    # Executar o programa C++
    result=$(echo "$dividendo $divisor" | ./div)
    
    # Obter resultado de referência
    expected=$(referencia $dividendo $divisor)
    
    # Verificar se está correto
    if [ "$result" == "$expected" ]; then
        echo "✅ PASS: $dividendo / $divisor = $result (Esperado: $expected)"
        ((passed++))
    else
        echo "❌ FAIL: $dividendo / $divisor = $result (Esperado: $expected)"
        ((failed++))
        
        # Classificar o erro
        if [ $dividendo -gt 0 ] && [ $divisor -gt 0 ]; then
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

echo "===================================="
echo "RELATÓRIO DE ERROS DETALHADO:"
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