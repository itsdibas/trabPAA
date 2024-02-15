#!/bin/bash

# Ativa o modo de depuração
set -x

echo "Iniciando script"

# Compila o programa
gcc -o programa trabPAA2.c

# Verifica se a compilação foi bem-sucedida
if [ $? -ne 0 ]
then
    echo "A compilação falhou!"
    exit 1
fi

# Loop sobre todos os arquivos de entrada
for i in {1..10}
do
   echo "Testando ex02-$i.in..."
   
   # Executa o programa com o arquivo de entrada e salva a saída
   ./programa < ex02-$i.in > saida_real$i.txt
   
   # Compara a saída real com a saída esperada
   diff -Z saida_real$i.txt ex02-$i.out
   
   if [ $? -eq 0 ]
   then
       echo "Teste $i passou!"
   else
       echo "Teste $i falhou!"
   fi
done

echo "Script concluído"

read -p "Pressione qualquer tecla para continuar . . ."