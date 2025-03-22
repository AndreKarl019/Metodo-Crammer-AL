#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int m, n;
float det(float B[m][n]);

int main(){
    float detC;
    register int i, j, k;
    register int linha, coluna;
    int check = 1, linhas = -1, colunas = -1, m1, n1;


    while(check==1){
        printf("Insira a quantidade de linhas do sistema: ");
        scanf("%i", &m1);
        while(getchar()!='\n');   
        if(0<m1&&m1<=999){
            check = 0;
        }else{
            printf("A quantidade de linhas eh invalida ou grande demais!\n");
        }    
    }

    check = 1;
    while(check==1){
        printf("Insira a quantidade de colunas do sistema: ");
        scanf("%i", &n1);
        while(getchar()!='\n');
        if(m1 == n1){
            check = 0;
        }else{
            printf("A quantidade de colunas precisa ser igual a de linhas para usar o metode de cramer!\n");
        }
    }
    m = m1;
    n = n1;
    float matriz[m][n], matriz_temp[m][n], fatores[m], Linha1[n], dete[n], resultado[m];

    for(linha = 0; linha <m1; linha++){
        for(coluna = 0; coluna < n1; coluna++){
            printf("Insira o coeficiente A%i%i: ", linha+1, coluna+1);
            scanf("%f", &matriz[linha][coluna]);
            while(getchar()!='\n');
        }
    }
    
    detC = det(matriz);
    
    for( i = 0; i<m1; i++){
        printf("Insira o termo independente B%i: ", i+1);
        scanf("%f", &fatores[i]);
    }

    for(i = 0; i<m1; i++){
        for(j=0;j<n1; j++){
            matriz_temp[i][j] = matriz[i][j];
        }
    }
    
    for(i = 0; i<m1;i++){
        for(j=0;j<n1;j++){
            matriz_temp[j][i] = fatores[j];
        }
        m = m1;
        n = n1;
        dete[i] = det(matriz_temp); 
        for(k = 0; k<n1;k++){
            matriz_temp[k][i] = matriz[k][i];
        }   
    }
   
    for(i = 0; i<m1; i++){
        resultado[i] = dete[i]/detC;
    }
    if(detC!=0){
        printf("\nO resultado eh: {");
        for(i=0; i<m1-1;i++){
            printf("%.2f, ",resultado[i]);
        }

        printf("%.2f}", resultado[m1-1]);
    }else{
        printf("O determinante deu 0! Resultado eh um SI ou um SPI");
    }

    return 0;
}

float det(float B[m][n]){
    int linhas = m;
    int colunas = n;
    if (colunas != linhas){
        printf("Formato invalido, a matriz deve ser quadrada!\n");
        exit(1);
    }else if(linhas == 1){
        return (B[0][0]); //se a matriz for 1x1 retorna o proprio elemento como determinante
    }else if(linhas == 2){
        return (B[0][0]*B[1][1]-B[1][0]*B[0][1]); // se a matriz for 2x2 retorna o produto das diagonais como determinante
    }else{
        float menor[linhas-1][colunas-1]; // matriz reduzida de 1 ordem menor que a original
        int linha_menor, coluna_menor; // variavel pra linhas e colunas da matriz reduzida
        int primeiralinha_colunaindex; //variavel pra representar qual coluna esta removida no momento
        float soma = 0; // variavel do resultado da funcao

        register int linha , coluna; //variaveis internas usadas para qual linha/coluna esta sendo usada pelo for no momento

        for(primeiralinha_colunaindex = 0; primeiralinha_colunaindex< linhas; primeiralinha_colunaindex++){
            
            linha_menor = 0; // linha da matriz reduzida iniciada no valor 0

            for(linha = 1; linha < linhas; linha++){

                coluna_menor = 0; //coluna da matriz reduzida iniciada no valor 0

                for(coluna = 0; coluna< colunas; coluna++){
                    if(coluna == primeiralinha_colunaindex){
                        continue; // se a coluna for a mesma do do index pula pra realizar a remoção da coluna
                    }else{
                    menor[linha_menor][coluna_menor] = B[linha][coluna]; //subistitui o A atual pelo da matriz de entrada da função
                    }
                    coluna_menor++; // apos a subistituição incrementa o valor da coluna para subistitui o proximo elemento
                }
                linha_menor++; // apos a subistituição incrementa o valor da linha para subistitui o proximo elemento
            }
            m = linha_menor; //re atribuindo o valor de m e n para o da matriz menor caso ela precise ser reduzida mais ainda no proximo loop iniciado pelo "det" no final
            n = coluna_menor;
            if(primeiralinha_colunaindex % 2 == 0){
                soma += B[0][primeiralinha_colunaindex]*det(menor); //caso o index seja par incrementa o valor na variavel soma caso impar subtrai
            }else{
                soma -= B[0][primeiralinha_colunaindex]*det(menor); //nesse ponto caso a matriz menor for tamanho 1x1 ou 2x2 o codigo retornara o determinante dela, caso contrario ira reduzi-la mais ate ficar no tamanho 2x2
            }
        }
        return soma;
    }
}