#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "console.h"

bool verificarPosicao(int pos, int * vet){
    for(int i=0; i<50; i++){
        if(vet[i] == pos){
            return true;
        }
    }

    return false;
}

void exibirMensagemBemVindo(){
    char fogo[5][60] = {
        {"            *             (       ) (        )   "}, //50
        {"   (      (  `            )\\ ) ( /( )\\ )  ( /(   "}, //50
        {" ( )\\ (   )\\))(    (   ( (()/( )\\())()/(  )\\())  "}, //50
        {" )((_))\\ ((_)()\\   )\\  )\\ /(_))(_)\\ /(_))((_)\\   "}, //50
        {"((_)_((_)(_()((_) ((_)((_)_))  _((_)_))_   ((_)  "} //450
    };

    gotoxy(1,5);
    textcolor(RED);
    printf("  _ _  _  _    _    _   _ _    _  _ _  _     _  \n"); 
    printf(" | _ ) __|  \\/  | \\ \\ / /|_ _|| \\| ||   \\ / _ \\ \n"); 
    printf(" | _ \\ _|| |\\/| |  \\ V /  | | | .` || |) | (_) |\n"); 
    printf(" |___/___|_|  |_|   \\_/  |___||_|\\_||___/ \\___/ \n");

    for(int i=5; i>0; i--){
        int posUsadas[50] = {0};

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

        for(int cont=0; cont<50; cont++){
            int posAle = 1 + rand() % 50;

            while(verificarPosicao(posAle, posUsadas)){
                posAle = posAle<50 ? posAle+1 : 1;
            }

            posUsadas[cont] = posAle;
            gotoxy(posAle, i);
            printf("%c", fogo[i-1][posAle-1]);
            Sleep(1+rand()%10);
        }
    }

    for(int i=0; i<3; i++){
        gotoxy(1,5);
        textcolor(WHITE);
        printf("%s\n", fogo[4]);

        Sleep(200); 
        gotoxy(1,4);
        textcolor(WHITE);
        printf("%s\n", fogo[3]); 
        gotoxy(1,5);
        textcolor(YELLOW);
        printf("%s\n", fogo[4]);

        Sleep(200); 
        gotoxy(1,3);
        textcolor(WHITE);
        printf("%s\n", fogo[2]); 
        gotoxy(1,4);
        textcolor(YELLOW);
        printf("%s\n", fogo[3]); 
        gotoxy(1,5);
        textcolor(BROWN);
        printf("%s\n", fogo[4]);

        Sleep(200);
        gotoxy(1,3);
        textcolor(YELLOW);
        printf("%s\n", fogo[2]); 
        gotoxy(1,4);
        textcolor(BROWN);
        printf("%s\n", fogo[3]); 
        gotoxy(1,5);
        textcolor(RED);
        printf("%s\n", fogo[4]);

        Sleep(200);
        gotoxy(1,2);
        textcolor(YELLOW);
        printf("%s\n", fogo[1]); 
        gotoxy(1,3);
        textcolor(BROWN);
        printf("%s\n", fogo[2]); 
        gotoxy(1,4);
        textcolor(RED);
        printf("%s\n", fogo[3]); 
        gotoxy(1,5);
        textcolor(RED);
        printf("%s\n", fogo[4]);
    }

    gotoxy(1,3);
    textcolor(RED);
    printf("%s\n", fogo[2]);

    Sleep(250);
    gotoxy(1,2);
    textcolor(RED);
    printf("%s\n", fogo[1]);
    
    Sleep(250);
    gotoxy(1,3);
    textcolor(BROWN);
    printf("%s\n", fogo[2]);

    Sleep(250);
    gotoxy(1,1);
    textcolor(RED);
    printf("%s\n", fogo[0]);

    Sleep(250);
    gotoxy(1,2);
    textcolor(YELLOW);
    printf("%s\n", fogo[1]);
    
    Sleep(250);
    gotoxy(1,1);
    textcolor(WHITE);
    printf("%s\n", fogo[0]);
}

void exibirLoading(){
    textcolor(RED);

    printf(" __    _____ _____ ____  _____ _____ _____   \n");
    printf("|  |  |     |  _  |    \\|     |   | |   __| \n");
    printf("|  |__|  |  |     |  |  |-   -| | | |  |  |  \n");
    printf("|_____|_____|__|__|____/|_____|_|___|_____|  \n");
    Sleep(600);

    for(int i=0;i<6;i++){
        switch(i){
            case 0:
            case 3:
                gotoxy(49, 3);
                printf("            ");
                gotoxy(48, 4);
                printf("            ");

                gotoxy(45, 3);
                printf("_");
                gotoxy(44, 4);
                printf("|_|");
                break;
                
            case 1:
            case 4:
                gotoxy(49, 3);
                printf("_");
                gotoxy(48, 4);
                printf("|_|");
                break;

            case 2:
            case 5:
                gotoxy(53, 3);
                printf("_");
                gotoxy(52, 4);
                printf("|_|");
                break;
        }

        Sleep(600);
    }
}

void exibirMenuPrincipal(){
    int randomizador;

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
    printf("  %c SOBRE", 250);
    printf("                      |       ");
    textcolor(WHITE);
    printf("|        \n");
    textcolor(RED);
    Sleep(50);
    printf("                               |      ");
    textcolor(WHITE);
    printf("/ \\        \n");
    textcolor(RED);
    Sleep(50);
    printf("                               |              \n");
    Sleep(50);
    printf("                              _|___           \n\n");
}

void animacaoPiscar(){
    int randomizador = rand() % 40000;

    /*
        Cabeca: 38, 7
        Braco esquerdo: 38, 8
        Perna direita: 40, 10
    */

//    printf("%i\n", randomizador);

   if(randomizador>=0&&randomizador<=3){
       textcolor(WHITE);
       backgroundcolor(BLACK);

       switch(randomizador){
           case 0:
               gotoxy(41, 10);
                printf("  ");
            break;

            case 1:
                gotoxy(39, 8);
                printf(" ");
            break;

            case 2:
                gotoxy(39, 7);
                printf("   ");
            break;   
        }

        Sleep(50);

        gotoxy(39, 7);
        printf("(_)");
        gotoxy(39, 8);
        printf("\\");
        gotoxy(41, 10);
        printf("\\");
        gotoxy(1, 1);
   }
}

int selecionarOpcao(){
    int opcao=1, opcaoAntiga=1;
    int tecla;

    /*
        opcao 1 = lin: 7  col: 3
    */


    do{
        if(kbhit()){
            textcolor(RED);


            tecla = getch();

            if(tecla == 72 || tecla == 80){
                gotoxy(1, opcao+6);
                backgroundcolor(BLACK);
                printf("  %c %s", 250, opcao==1?"JOGAR":opcao==2?"INSTRUCOES":opcao==3?"SOBRE":"Erro");

                switch(tecla){
                    case 72:
                        opcao = opcao!=1 ? opcao-1:3;
                        break;

                    case 80:
                        opcao = opcao!=3 ? opcao+1:1;
                        break;
                }
            }

            gotoxy(1, opcao+6);
            backgroundcolor(YELLOW);
            printf("  %c %s", 175, opcao==1?"JOGAR":opcao==2?"INSTRUCOES":opcao==3?"SOBRE":"Erro");
            gotoxy(1,1);
        }
        else{
            //animacao
            animacaoPiscar();
        }
    }while(tecla != 13); //13 = Enter

    return opcao;
}

int menu(){
    exibirMensagemBemVindo();

    Sleep(1000);
    system("cls");

    exibirLoading();

    system("cls");
    Sleep(500);

    exibirMenuPrincipal();
    return selecionarOpcao();
}

#endif /* MENU_H_INCLUDED */