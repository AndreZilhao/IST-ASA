# ASA-IST
Algoritmos de Sintese de Dados - Projecto 2

# Descrição da Solução

 - Algoritmo de verificação de caminho com menor custo usando Bellman-Ford como base inicial.
 - Detecção de ciclos infinitos.
 - Inclui optimizações para reduzir o tamanho do grafo, e flags de optimização para grafos sem ciclos infinitos.
 - Inclui um gerador de testes providenciado pelo docente.

# O Problema

A empresa Coelho e Caracol Lda. faz transporte de mercadorias. O Sr. Coelho passa o dia
na camioneta a andar de local para local, enquanto o Sr. Caracol fica no escritório a fazer o
planeamento das rotas. No entanto, devido à expansão da empresa, a tarefa do Sr. Caracol está
mais díficil. A quantidade de rotas a planear é cada vez maior. Neste projeto iremos desenvolver
software para resolver este problema automaticamente.
Uma rota consiste numa sequência de localidades, sendo que entre cada par de localidades
pode ser transportado um tipo de mercadoria. O transporte de mercadorias gera receita,
enquanto que a deslocação tem um custo, combustível, portagens, etc.
O Sr. Caracol simplifica esta complexidade associando a cada par de localidades um valor
de perda, que resulta de subtrair a receita ao custo. Portanto, se a receita for maior que o custo, o
valor será negativo. Se o valor for positivo significa que o custo supera a receita. Naturalmente,
o Sr. Caracol prefere ter valores negativos entre duas localidades. Nesse sentido, alinha a
estratégia da empresa por forma a que esses valores sejam o menor possível, sendo que entre
um determinado par de localidades é considerada no máximo um valor de perda.
Feita esta seleção inicial, o objetivo é estabelecer para cada localidade qual é o percurso
que, com origem na sede da empresa, minimiza o valor de perda total. Ao fazer esta análise o
Sr. Caracol tem tristezas e alegrias. De vez em quando constata que não é possível chegar a
uma determinada localidade. Por outro lado, às vezes constata, com muita alegria, que há uma
sequência de localidades que, se iterada um número suficientemente grande de vezes, produz
um ganho tão grande quanto se queira.

#Input

O ficheiro de entrada deverá conter a informação sobre as perdas entre localidades. O input é
definido da seguinte forma:
• Uma linha com o número de localidades N (N ≥ 2) e o número de custos conhecidos C,
separados por um espaço em branco.

• Uma linha com o número entre 1 e N que identifica a sede da empresa.

• Uma lista de C linhas, em que cada linha contém três inteiros u, v e w (separados por um
espaço em branco). Cada linha indica que a deslocação de u para v tem perda w.

Assume-se que a identificação das localidades é um inteiro entre 1 e N.

#Output

Para cada localidade queremos determinar a perda mínima até esse ponto, partindo da sede. O
programa deverá escrever no output a seguinte informação:

• Uma sequência de N linhas em que a linha i (1 ≤ i ≤ N) corresponde à perda mínima do
ponto i. Caso seja impossível definir essa perda, a linha deve conter apenas o carácter
’I’. Caso não existam deslocamentos suficientes para determinar essa perda deve conter
apenas o carácter ’U’.

#Exemplos

**input 1**  
9 0  
7  
2 3 -100  
3 4 -100  
1 2 -100  
4 5 -100  
5 1 -300  
7 8 100  
5 6 400  
7 1 100  


**output 1**  
I  
I  
I  
I  
I  
I  
0  
100  
U    

**input 2**  
6 8  
1  
1 2 -100  
2 3 -100  
1 3 -198  
3 4 -100  
1 4 -280  
4 5 -100  
5 1 450  
6 1 100 

**output 2**  
0  
-100  
-200  
-300  
-400  
U   

#Relatório  

O  relatório do projecto pode ser encontrado em:
https://docs.google.com/document/d/1bUuSznnLrFosNloa5GjRjc9U8s5fB5f1xQwvPVvSLxg/pub
