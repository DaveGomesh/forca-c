#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define QUANT_CATEGORIAS 3
#define QUANT_PALAVRAS 5

typedef struct tipo_categorias{
    char nomeCategoria[21];
    char palavras[QUANT_PALAVRAS][21];
}Categoria;

int contagem=0;

int escolherPalavra(Categoria categorias[], char palavraEscolhida[], char palavraEscondida[]){
    int i=0, j=0, k=0;

    i = rand() % QUANT_CATEGORIAS;
    j = rand() % QUANT_PALAVRAS;

    strcpy(palavraEscolhida, categorias[i].palavras[j]);

    for(k=0; k<strlen(palavraEscolhida); k++){
        if(palavraEscolhida[k]!='-'){
            palavraEscondida[k] = '_';
        }
        else{
            palavraEscondida[k] = '-';
        }
    }

    palavraEscondida[k] = '\0';

    return i;
}

void mostrarPalavra(char palavraEscondida[], char dica[]){

    printf("Dica: %s\n\n", dica);

    for(int j=0;j<strlen(palavraEscondida);j++){
        printf("%c ", palavraEscondida[j]);
    }

    printf("\n\n");
}

int fazerJogada(char palavraEscolhida[], char palavraEscondida[]){
    int encontrou=0;
    char letra;

    printf("\n\nDigite uma letra: ");
    scanf("%c", &letra);
    setbuf(stdin, NULL);

    letra = toupper(letra);

    for(int i=0; i<strlen(palavraEscolhida); i++){
        if(letra == palavraEscolhida[i]){
            encontrou++;

            palavraEscondida[i] = palavraEscolhida[i];
        }
    }

    return encontrou;
}

int interface(char palavraEscolhida[], char palavraEscondida[], char dica[]){

    int encontrados=0, erros=7, contador=0;
    
    while(erros!=0 && contador!=strlen(palavraEscolhida)){
        printf("  _______       \n");
        printf(" |/      |      \n");
        printf(" |      %s      \n", erros < 7 ? "(_)":" ");
        printf(" |      %c%c%c    \n",erros < 4 ? '\\':' ', erros < 6 ? '|':' ', erros < 3? '/':' ');
        printf(" |       %c      \n", erros < 5 ? '|' : ' ');
        printf(" |      %c %c    \n", erros < 2 ? '/':' ', erros < 1 ? '\\': ' ');
        printf(" |              \n");
        printf("_|___           \n\n");
        
        mostrarPalavra(palavraEscondida, dica);
        encontrados = fazerJogada(palavraEscolhida, palavraEscondida);

        if(encontrados == 0){
            erros--;
            printf("\n\nVoce so pode errar mais %d vez(es)\n\n", erros);
        }
        
        
        contador += encontrados;

        system("pause");
        system("cls");
    }
    
    mostrarPalavra(palavraEscondida, dica);

    if(erros != 0){
        printf("\n\nPARABENS, VOCE VENCEU\n\n");
        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
    }
    else{
        printf("\n\nQUE PENA, VOCE PERDEU\n\n");
        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n\n");
    }

    system("pause");
}

int main(){
    srand(time(NULL));

    Categoria categorias[QUANT_CATEGORIAS] = {
        {"Animal", {"LAGARTO", "GATO", "CACHORRO", "ELEFANTE", "BODE"}},
        {"Veiculo", {"ONIBUS", "CAMINHAO", "CARRO", "AVIAO", "HELICOPTERO"}},
        {"Comida", {"ARROZ", "FEIJAO", "MACARRAO", "CAMAROADA", "HAMBURGUER"}}
    };

    char palavraEscolhida[21];

    char palavraEscondida[21];

    int dica = escolherPalavra(categorias, palavraEscolhida, palavraEscondida);

    interface(palavraEscolhida, palavraEscondida, categorias[dica].nomeCategoria);


}