#ifndef ANIMACOES_H_INCLUDED
#define ANIMACOES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>

#include "console.h"

// Verifica se uma posicao consta no vetor de posicoes utilizadas
bool verificarPosicao(int pos, int * vet){
    for(int i=0; i<50; i++){
        if(vet[i] == pos){
            return true;
        }
    }

    return false;
}

// Exibe a mensagem de Bem Vindo
void exibirMensagemBemVindo(){
    //Guarda o desenho da chama
    char fogo[5][60] = {
        {"            *             (       ) (        )   "}, //50
        {"   (      (  `            )\\ ) ( /( )\\ )  ( /(   "}, //50
        {" ( )\\ (   )\\))(    (   ( (()/( )\\())()/(  )\\())  "}, //50
        {" )((_))\\ ((_)()\\   )\\  )\\ /(_))(_)\\ /(_))((_)\\   "}, //50
        {"((_)_((_)(_()((_) ((_)((_)_))  _((_)_))_   ((_)  "} //450
    };

    char bemVindo[4][55] = {
        {"  _ _  _  _    _    _   _ _    _  _ _  _     _  \n"},
        {" | _ ) __|  \\/  | \\ \\ / /|_ _|| \\| ||   \\ / _ \\ \n"},
        {" | _ \\ _|| |\\/| |  \\ V /  | | | .` || |) | (_) |\n"},
        {" |___/___|_|  |_|   \\_/  |___||_|\\_||___/ \\___/ \n\n"}
    };

    //Coloca a mensagem de bem vindo
    textcolor(RED);
    for(int i=3; i>=0; i--){
        gotoxy(1,i+5);
        printf("%s", bemVindo[i]);
        Sleep(80);
    }

    //Exibe o fogo de baixo pra cima e modo aleatorio na horizontal
    for(int i=5; i>0; i--){
        int posUsadas[50] = {0};

        //Controla a cor que cada parte da chama tera
        switch(i){
            case 5:
            case 4:
                textcolor(RED);
                break;
            
            case 3:
                textcolor(BROWN);
                break;
            
            case 2:
                textcolor(YELLOW);
                break;
            
            case 1:
                textcolor(WHITE);
                break;
        }

        //Exibe a linha atual da chama, mas de maneira aleatoria
        for(int cont=0; cont<50; cont++){
            int posAle = 1 + rand() % 50;

            //Caso a posicao aleatoria gerada ja tenha sido exibida, procura-se uma nova posicao
            while(verificarPosicao(posAle, posUsadas)){
                posAle = posAle<50 ? posAle+1 : 1;
            }

            //Guarda essa posicao para nao ser usada mais
            posUsadas[cont] = posAle;

            //Exibe a posicao atual da chama
            gotoxy(posAle, i);
            printf("%c", fogo[i-1][posAle-1]);
            Sleep(rand()%3);
        }
    }

    //Guarda as cores a serem usadas na animacao
    int cores[] = {RED, RED, BROWN, YELLOW, WHITE};

    //Animacao de cores no fogo (nao tente entender kk)
    for(int i=0; i<3; i++){ //A animacao sera executada 3 vezes
        for(int j=5; j>0; j--){ //Serao feitas 5 permutas de cores
            for(int k=j, l=4; k<=5; k++){ //Controla a permuta de cores
                gotoxy(1, k);
                textcolor(cores[l--]);
                printf("%s\n", fogo[k-1]);
            }
            Sleep(200);
        }
    }
}

// Coloca os pontos da animacao de Loading
void exibirPontos(int col, int lin){
    gotoxy(col, lin);
    printf("_");
    gotoxy(--col, ++lin);
    printf("|_|");
}

// Remove os pontos da animacao de Loading
void removerPontos(int col, int lin){
    gotoxy(col, lin);
    printf("            ");
    gotoxy(--col, ++lin);
    printf("            ");
}

// Exibe a tela de Loading
void exibirLoading(){
    //Mostra o loading
    textcolor(RED);
    printf(" __    _____ _____ ____  _____ _____ _____   \n");
    printf("|  |  |     |  _  |    \\|     |   | |   __| \n");
    textcolor(WHITE);
    printf("|  |__|  |  |     |  |  |-   -| | | |  |  |  \n");
    textcolor(RED);
    printf("|_____|_____|__|__|____/|_____|_|___|_____|  \n");
    Sleep(100);

    char copyrigths[70] = "\nCopyright (c) 2020 David Gomesh e Lucas Nadler\n";

    textcolor(LIGHTGRAY);
    for(int i=0; copyrigths[i]!='\0'; i++){
        printf("%c", copyrigths[i]);
        Sleep(10);
    }
    textcolor(RED);

    //Controla a animacao dos pontos do Loading, fazendo os aparecer e desaparecer 3 vezes
    for(int i=0;i<6;i++){
        switch(i){
            case 0:
            case 3:
                removerPontos(49, 3);
                exibirPontos(45, 3);
            break;
                
            case 1:
            case 4:
                exibirPontos(49, 3);
            break;

            case 2:
            case 5:
                exibirPontos(53, 3);
            break;
        }

        Sleep(500);
    }
}

// Exibe o conteudo do menu principal
void exibirConteudoMenuPrincipal(){
    textcolor(RED);
    printf("    __ _____ _____ _____    ____  _____    _____ _____ _____ _____ _____ \n");
    Sleep(50);
    printf(" __|  |     |   __|     |  |    \\|  _  |  |   __|     | __  |     |  _  |\n");
    Sleep(50);
    textcolor(WHITE);
    printf("|  |  |  |  |  |  |  |  |  |  |  |     |  |   __|  |  |    -|   --|     |\n");
    Sleep(50);
    textcolor(RED);
    printf("|_____|_____|_____|_____|  |____/|__|__|  |__|  |_____|__|__|_____|__|__|\n");
    Sleep(50);
    textcolor(YELLOW);
    printf("== DAVID G. E LUCAS N. ==");
    textcolor(RED);
    printf("       _______       \n");
    Sleep(50);
    printf("                               |/      |      \n");
    Sleep(50);
    backgroundcolor(YELLOW);
    printf("  %c JOGAR", 175);
    backgroundcolor(BLACK);
    printf("                      |      ");
    textcolor(WHITE);
    printf("(_)      \n");
    textcolor(RED);
    Sleep(50);
    printf("  %c INSTRUCOES", 250);
    printf("                 |      ");
    textcolor(WHITE);
    printf("\\|/        \n");
    textcolor(RED);
    Sleep(50);
    printf("  %c NEW WORD", 250);
    printf("                   |       ");
    textcolor(WHITE);
    printf("|        \n");
    textcolor(RED);
    Sleep(50);
    printf("  %c SOBRE", 250);
    printf("                      |      ");
    textcolor(WHITE);
    printf("/ \\        \n");
    textcolor(RED);
    Sleep(50);
    printf("  %c SAIR", 250);
    printf("                       |              \n");
    Sleep(50);
    printf("                              _|___           \n\n");
}

// Faz a animacao do boneco piscar
void animacaoPiscar(){

    //A chance da animacao acontecer eh de 0.0075% a cada chamada da funcao
    register int randomizador = rand() % 40000;

    /*
        Cabeca: 39, 7
        Braco esquerdo: 39, 8
        Perna direita: 41, 10
    */

    //Se cair os numeros que ativarao a animacao
    if(randomizador>=0 && randomizador<=3){
        textcolor(WHITE);
        backgroundcolor(BLACK);

        switch(randomizador){
            case 0://Pisca a perna direita
                gotoxy(41, 10);
                printf("  ");
                Sleep(50);
                gotoxy(41, 10);
                printf("\\");
            break;

            case 1://Pisca o braco esquerdo
                gotoxy(39, 8);
                printf(" ");
                Sleep(50);
                gotoxy(39, 8);
                printf("\\");
            break;

            case 2://Pisca a cabeca
                gotoxy(39, 7);
                printf("   ");
                Sleep(50);
                gotoxy(39, 7);
                printf("(_)");
            break;   
        }
        
        //Coloca o cursor no canto da tela
        gotoxy(1, 1);
    }
}

// Mostra as telas iniciais
void exibirBoasVindas(){
    exibirMensagemBemVindo();

    Sleep(1000);
    system("cls");

    exibirLoading();
}

#endif /* ANIMACOES_H_INCLUDED */