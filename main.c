#include <stdio.h>

#include "animacoes.h"
#include "menu.h"
#include "forca.h"

int main(){
    srand(time(NULL));
    int opcao;

    // exibirBoasVindas();
    do{
        opcao = exibirMenuPrincipal();
        switch(opcao){
            case 1:;
                Forca forca;
                inicializar(&forca);
                jogar(&forca);
            break;

            case 2:
                exibirInstrucoes();
            break;

            case 3:
                exibirSobre();
            break;

            case 4:
                //Sair
            break;

            default:
                //Opcao invalida
            break;
        }
    }while(opcao!=4); //4 == Sair

    return 0;
}