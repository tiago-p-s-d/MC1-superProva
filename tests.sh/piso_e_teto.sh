#!/bin/bash



# Funções de referência CORRIGIDAS
function piso_referencia() {
    local num=$1
    echo $(awk "BEGIN {print int($num) - ($num < 0 && $num != int($num))}")
}

function teto_referencia() {
    local num=$1
    echo $(awk "BEGIN {print int($num) + ($num > 0 && $num != int($num))}")
}

# Inicializa contadores
total_pass=0
total_fail=0
pos_pass=0
pos_fail=0
neg_pass=0
neg_fail=0

echo "Iniciando 100 testes aleatórios..."
echo "----------------------------------"

for i in {1..100}; do
    # Gera números aleatórios com maior variedade
    int1=$(( (RANDOM % 20001) - 10000 ))  # -1000 a 1000
    int2=$(( (RANDOM % 1000) + 1 ))     # 1 a 1000 (evita divisão por zero)
    
    # Cria número float
    float_input=$(awk "BEGIN {printf \"%.6f\", $int1/$int2}")

    # Executa o programa C++
    read piso_output teto_output <<< $(echo "$float_input" | ./piso_teto)

    # Obtém valores de referência CORRETOS
    piso_esperado=$(piso_referencia $float_input)
    teto_esperado=$(teto_referencia $float_input)

    # Verificação
    if [ "$piso_output" -eq "$piso_esperado" ] && [ "$teto_output" -eq "$teto_esperado" ]; then
        echo "✅ PASS: NUMERO: $float_input PISO: $piso_esperado(recebido $piso_output) TETO: $teto_esperado(recebido $teto_output)"
        ((total_pass++))
        
        if (( $(echo "$float_input >= 0" | bc -l) )); then
            ((pos_pass++))
        else
            ((neg_pass++))
        fi
    else
        echo "❌ FAIL: NUMERO: $float_input PISO: $piso_esperado(recebido $piso_output) TETO: $teto_esperado(recebido $teto_output)"
        ((total_fail++))
        
        if (( $(echo "$float_input >= 0" | bc -l) )); then
            ((pos_fail++))
        else
            ((neg_fail++))
        fi
    fi
done

# Relatório final
echo -e "\n\nRELATÓRIO FINAL:"
echo "----------------------------------------"
echo "TOTAL DE TESTES: 100"
echo "✅ ACERTOS: $total_pass"
echo "❌ ERROS: $total_fail"
echo "TAXA DE SUCESSO: $((total_pass))%"
echo ""
echo "NÚMEROS POSITIVOS:"
echo "✅ ACERTOS: $pos_pass"
echo "❌ ERROS: $pos_fail"
echo ""
echo "NÚMEROS NEGATIVOS:"
echo "✅ ACERTOS: $neg_pass"
echo "❌ ERROS: $neg_fail"
echo "----------------------------------------"

if [ $total_fail -eq 0 ]; then
    echo "🎉 Todos os testes passaram!"
    exit 0
else
    echo "⚠️ Alguns testes falharam. Verifique os resultados acima."
    exit 1
fi