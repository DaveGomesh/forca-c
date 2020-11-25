#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdlib.h>

#include "animacoes.h"

#define QUANT_OPCOES 4

// Seleciona a opcao pelo teclado e retorna a opcao selecionada
int selecionarOpcao(){
    int opcao=1, opcaoAntiga=1;
    int tecla;

    /*
        opcao 1 = lin: 7  col: 3
        opcao 2 = lin: 8  col: 3
        opcao 3 = lin: 9  col: 3
    */

    do{
        //Se alguma tecla for pressionada
        if(kbhit()){
            textcolor(RED);

            tecla = getch();

            //Se for a seta de navegacao para cima ou para baixo
            if(tecla == 72 || tecla == 80){
                //Deixa a opcao atual com o funco preto
                gotoxy(1, opcao+6);
                backgroundcolor(BLACK);
                printf("  %c %s", 250, opcao==1?"JOGAR":opcao==2?"INSTRUCOES":opcao==3?"SOBRE":opcao==4?"SAIR":"Erro");

                //Verifica para qual opcao sera alterada
                switch(tecla){
                    case 72:
                    opcao = opcao!=1 ? opcao-1:QUANT_OPCOES;
                    break;

                    case 80:
                    opcao = opcao!=QUANT_OPCOES ? opcao+1:1;
                    break;
                }
            }

            //Deixa a nova opcao com o fundo amarelo
            gotoxy(1, opcao+6);
            backgroundcolor(YELLOW);
            printf("  %c %s", 175, opcao==1?"JOGAR":opcao==2?"INSTRUCOES":opcao==3?"SOBRE":opcao==4?"SAIR":"Erro");

            gotoxy(1,1);
        }
        //Se nao for pressionada nenhuma tecla, exibe a animacao do boneco
        else{
            //animacao
            animacaoPiscar();
        }
    }while(tecla != 13); //13 = Enter

    //Retorna a opcao selecionada com o enter
    return opcao;
}

// Exibe o menu principal e retorna a opcao selecionada
int exibirMenuPrincipal(){
    system("cls");
    Sleep(500);

    exibirConteudoMenuPrincipal();
    return selecionarOpcao();
}

// Exibe as instrucoes do jogo
void exibirInstrucoes(){
    //Instrucoes
    setCorPadrao();
}

// Exibe informacoes sobre o software
void exibirSobre(){
    //Sobre
    setCorPadrao();
}

#endif /* MENU_H_INCLUDED */