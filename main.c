#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "menu.h"

#define TAM_PAL 21
#define QUANT_ARQS 4
#define QUANT_CATEGORIAS 3
#define QUANT_PALAVRAS 5
#define QUANT_TEMPO 60

typedef struct tipo_categorias{
    char nomeCategoria[21];
    char palavras[QUANT_PALAVRAS][21];
}Categoria;

typedef struct tipo_forca{
    char palavra[TAM_PAL ];
    char visualizacao[TAM_PAL];
    char dica[TAM_PAL];
    char digitadas[27];
    int  contagem;
    int  quantLetras;
}Forca;



void escolherPalavra(Forca * forca);
void mostrarPalavra (Forca * forca);
int fazerJogada     (Forca * forca);
void jogar       (Forca * forca);
void exibirMensagemVitoria();
void exibirMensagemDerrota();

void inicializar(Forca * forca){
    int i;

    for(i=0; i<TAM_PAL; i++){
        forca->palavra[i] = ' ';
        forca->visualizacao[i] = ' ';
        forca->dica[i] = ' ';
    }

    forca->palavra[i] = '\0';
    forca->visualizacao[i] = '\0';
    forca->dica[i] = '\0';

    for(i=0; i<27; i++){
        forca->digitadas[i] = ' ';
    }
    forca->digitadas[i] = '\0';

    forca->contagem = 0;
    forca->quantLetras = 0;
}

int main(){
    srand(time(NULL));
    if(menu() == 1){
        Forca forca;
        inicializar(&forca);
        escolherPalavra(&forca);
        jogar(&forca);
    }
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
        return;
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

    unsigned int i;
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

void mostrarPalavra(Forca * forca){
    for(int i=0;i<forca->quantLetras;i++){
        printf("%c ", forca->visualizacao[i]);
    }

    printf("\n\n");
}

int fazerJogada(Forca * forca){
    int encontrou=0;
    char letra;

    printf("\n\nDigite uma letra: ");
    
    if(kbhit()){
        letra = getch();

        letra = toupper(letra);
        
        for(int i=0; i<=forca->contagem; i++){
            if(forca->digitadas[i] == letra){
                return -1;
            }
        }
        
            forca->digitadas[forca->contagem] = letra;
            forca->contagem++;
        
        /*forca->digitadas[forca->contagem] = letra;
        forca->contagem++;*/

        for(int i=0; i<forca->quantLetras; i++){
            if(letra == forca->palavra[i]){
                forca->visualizacao[i] = forca->palavra[i];
                encontrou++;
            }
        }

        return encontrou;
    }

    return -2;
}

void jogar(Forca * forca){

    textcolor(RED);
    backgroundcolor(BLACK);

    int encontrados=0, erros=7, contador=0;
    time_t tempoFinal, tempoAtual;
    system("cls");

    tempoFinal = time(NULL) + 10;

    do{
        tempoAtual = time(NULL);

        printf("Voce tem %i segundos restantes!\n", tempoFinal - tempoAtual);

        printf("Letras Digitadas: ");
        for(int i=0;forca->digitadas[i]!='\0';i++){
            printf("%c ", forca->digitadas[i]);
        }

        printf("\n\n");
        printf("DICA: %s", forca->dica);
        printf("\n\n");

        printf("  _______       \n");
        printf(" |/      |      \n");
        printf(" |      %s      \n", erros < 7 ? "(_)":" ");
        printf(" |      %c%c%c    \n",erros < 4 ? '\\':' ', erros < 6 ? '|':' ', erros < 3? '/':' ');
        printf(" |       %c      \n", erros < 5 ? '|' : ' ');
        printf(" |      %c %c    \n", erros < 2 ? '/':' ', erros < 1 ? '\\': ' ');
        printf(" |              \n");
        printf("_|___           \n\n");

        mostrarPalavra(forca);
        encontrados = fazerJogada(forca);

        if(encontrados == -1){
            printf("Letra ja digitada!\n");
            continue;
        }
        else if(encontrados == 0){
            erros--;
            printf("\n\nVoce so pode errar mais %d vez(es)\n\n", erros);
        }

        contador += encontrados;

        if(erros==0){
            exibirMensagemDerrota();
            return;
        }

        if(contador==forca->quantLetras){
            exibirMensagemVitoria();
            return;
        }

        system("cls");

    }while(tempoFinal != tempoAtual);

    printf("O tempo acabou!");
    exibirMensagemDerrota();
}

void exibirMensagemVitoria(){
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

void exibirMensagemDerrota(){
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