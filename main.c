#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define TAM_PAL 21
#define QUANT_ARQS 4
#define QUANT_CATEGORIAS 3
#define QUANT_PALAVRAS 5

typedef struct tipo_categorias{
    char nomeCategoria[21];
    char palavras[QUANT_PALAVRAS][21];
}Categoria;

typedef struct tipo_forca{
    char palavra[TAM_PAL ];
    char visualizacao[TAM_PAL];
    char dica[TAM_PAL];
    int quantLetras;
}Forca;

int contagem=0;

void escolherPalavra(Forca * forca);
void mostrarPalavra(char palavraEscondida[], char dica[]);
int fazerJogada(char palavraEscolhida[], char palavraEscondida[]);
int interface(char palavraEscolhida[], char palavraEscondida[], char dica[]);

int main(){
    srand(time(NULL));
    Forca forca;
    escolherPalavra(&forca);
    interface(forca.palavra, forca.visualizacao, forca.dica);
    return 0;
}

void escolherPalavra(Forca * forca){
    FILE * f_Arq;

    char arquivos[QUANT_ARQS][30] = {
        {"palavras\\animais.txt"},
        {"palavras\\comidas.txt"},
        {"palavras\\veiculos.txt"},
        {"palavras\\objetos.txt"}
    };

    int arqAle = rand() % QUANT_ARQS;
    f_Arq = fopen(arquivos[arqAle], "r");

    if(f_Arq == NULL){
        f_Arq = fopen(arquivos[arqAle], "w");
        fprintf(f_Arq, "Arquivo: '%s'\n", arquivos[arqAle]);
        fclose(f_Arq);
        return 0;
    }

    switch(arqAle){
        case 0:
            strcpy(forca->dica, "Animal");
            break;

        case 1:
            strcpy(forca->dica, "Comida");
            break;

        case 2:
            strcpy(forca->dica, "Veiculo");
            break;

        case 3:
            strcpy(forca->dica, "Objetos");
            break;
    }

    char temp[TAM_PAL];
    int quantPal=0;

    while(fgets(temp, TAM_PAL, f_Arq)!=NULL){
        quantPal++;
    }

    rewind(f_Arq);

    int palAle = rand() % quantPal;

    for(int i=0; i<=palAle; i++){
        fgets(forca->palavra, TAM_PAL, f_Arq);
    }

    forca->palavra[strlen(forca->palavra)-1] = '\0';

    fclose(f_Arq);

    int i;
    forca->quantLetras = 0;

    for(i=0; i<strlen(forca->palavra); i++){
        if(forca->palavra[i] != '-'){
            forca->visualizacao[i] = '_';
            forca->quantLetras++;
        }
        else{
            forca->visualizacao[i] = '-';
        }
    }

    forca->visualizacao[i] = '\0';

    // printf("Quantidade de palavras: %i\n\n", quantPal);

    // printf("Cod. Pal: %i\n", palAle);
    // printf("Palavra: %s\n", forca->palavra);
    // printf("Visuali: %s\n", forca->visualizacao);
    // printf("Dica:    %s\n", forca->dica);
    // printf("Q Letra: %i\n\n", forca->quantLetras);
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
