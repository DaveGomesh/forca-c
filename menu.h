#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdlib.h>
#include <locale.h>

#include "forca.h"
#include "animacoes.h"

#define QUANT_OPCOES 5

// Seleciona a opcao pelo teclado e retorna a opcao selecionada
int selecionarOpcao(){
    int opcao=1;
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
                printf("  %c %s", 250, opcao==1?"JOGAR":opcao==2?"INSTRUCOES":opcao==3?"NEW WORD":opcao==4?"SOBRE":opcao==5?"SAIR":"Erro");

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
            printf("  %c %s", 175, opcao==1?"JOGAR":opcao==2?"INSTRUCOES":opcao==3?"NEW WORD":opcao==4?"SOBRE":opcao==5?"SAIR":"Erro");

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

// Adiciona novas palavras no jogo
void adicionarPalavra(){
    setCorPadrao();

    char palavra[TAM_PALAVRAS];
    int opcao;

    do{
        system("cls");
    
        //Abre o arquivo no modo append (acrescentar)
        FILE * f_Arq = fopen("palavras\\outros.txt", "a");

        printf("ADICIONAR PALAVRAS\n\n");

        printf("Digite a palavra: ");

        textcolor(LIGHTGRAY);
        fgets(palavra, TAM_PALAVRAS, stdin);
        textcolor(RED);

        //Coloca todas as letras da palavra em maiusculo
        strupr(palavra);
        
        //Guarda a palavra no arquivo
        fwrite(palavra, strlen(palavra), 1, f_Arq);
        
        fclose(f_Arq);

        do{
            system("cls");
            printf("Deseja continuar adicionando?\n");
            printf("Enter para continuar e ESC para sair.\n");

            opcao = getch();

        }while(opcao != 13 && opcao != 27); //13 == Enter e 27 == ESC

        if(opcao == 27){
            break;
        }

    }while(opcao == 13);


    setbuf(stdin, NULL);
}

// Exibe as instrucoes do jogo
void exibirInstrucoes(){
    setCorPadrao();
    system("cls");

    char caveira[23][70] = {
        {"         _,.-------.,_ \n"},
        {"     ,;~'             '~;, \n"},
        {"   ,;                     ;, \n"},
        {"  ;                         ; \n"},
        {" ,'                         ', \n"},
        {",;                           ;, \n"},
        {"; ;      .           .      ; ; \n"},
        {"| ;   ______       ______   ; | \n"},
        {"|  `/~\"     ~\" . \"~     \"~\'   | \n"},
        {"|  ~  ,-~~~^~, | ,~^~~~-,  ~  | \n"},
        {" |   |        }:{        |   | \n"},
        {" |   l       / | \\       !   | \n"},
        {" .~  (__,.--\" .^. \"--.,__)  ~. \n"},
        {" |     ---;' / | \\ `;---     | \n"},
        {"  \\__.       \\/^\\/       .__/ \n"},
        {"   V| \\                 / |V \n"},
        {"    | |T~\\___!___!___/~T| | \n"},
        {"    | |`IIII_I_I_I_IIII'| | \n"},
        {"    |  \\,III I I I III,/  | \n"},
        {"     \\   `~~~~~~~~~~'    / \n"},
        {"       \\   .       .   /      \n"},
        {"         \\.    ^    ./ \n"},
        {"           ^~~~^~~~^ \n\n\n"}
    };

    char instrucoes[7][70] = {
        {"QUER SABER AS REGRAS DESTE IMENSO DESAFIO?"},
        {"VOCE IRA SE ARREPENDER, MAS IREI LHE CONTAR."},
        {"VOCE TEM APENAS 60 SEGUNDOS PARA PEQUENAS PALAVRAS."},
        {"MAS COMO SOU PIEDOSO, EM GRANDES DESAFIOS DAREI 90 SEGUNDOS."},
        {"O DESAFIO E VOCE ACERTAR A PALAVRA ESCONDIDA EM 7 TENTATIVAS."},
        {"SE SUAS CHANCES ACABAREM OU O SEU TEMPO ENCERRAR"},
        {"VOCE TERA UMA MORTE DOLOROSA, MUAHAHAHA!!!"}
    };
    
    for(int i=0; i<23; i++){
        printf("%s", caveira[i]);
        Sleep(20);
    }

    Sleep(1500);

    int aumentador=0;

    for(int i=0;i<7;i++){
        gotoxy(35, i+aumentador+5);
        for(int j=0; instrucoes[i][j]!='\0';j++){
            if(
                (i==2 && (j>=16 && j<=26)) ||
                (i==3 && (j>=48 && j<=62)) ||
                (i==4 && (j>=48 && j<=62)) ||
                (i==6 && (j>=14 && j<=27))
            ){
                textcolor(LIGHTGRAY);
            }else{
                textcolor(RED);
            }
            
            printf("%c", instrucoes[i][j]);
            Sleep(65);
        }
        aumentador++;
        Sleep(700);
    }

    setbuf(stdin, NULL);
    getch();
}

// Exibe informacoes sobre o software
void exibirSobre(){
    setCorPadrao();
    system("cls");

    printf("---------------------------------------------------------------------\n");

    printf("\n Desenvolvido por ");
    textcolor(LIGHTGRAY);
    printf(" David Gomes e Lucas Nadler\n");
    textcolor(RED);
    Sleep(65);

    printf(" Versao 5                    11/2020\n\n");
    Sleep(65);

    printf(" 2a Atividade avaliativa.\n");
    Sleep(65);

    printf(" Disciplina: ");
    textcolor(LIGHTGRAY);
    printf(" Linguagem de Programacao I\n");
    textcolor(RED);
    Sleep(65);

    printf(" Profa: ");
    textcolor(LIGHTGRAY);
    printf(" Evaldinolia Gilbertoni Moreira\n\n");
    textcolor(RED);
    Sleep(65);


    printf(" Instituto Federal de Educacao, Ciencia e Tecnologia do Maranhao\n");
    printf(" Campus Sao Luis - Monte Castelo.\n\n");
    Sleep(65);

    textcolor(LIGHTGRAY);
    printf(" Copyright (c) 2020 David Gomesh e Lucas Nadler\n\n");
    textcolor(RED);
    Sleep(65);

    printf("---------------------------------------------------------------------");

    getch();

}

#endif /* MENU_H_INCLUDED */

