#include "animacoes.h"
#include "menu.h"
#include "forca.h"

int main(){
    srand(time(NULL));
    int opcao;

    exibirBoasVindas();

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
                adicionarPalavra();
            break;

            case 4:
                exibirSobre();
            break;

            case 5:
                //Sair
            break;

            default:
                //Opcao invalida
            break;
        }
    }while(opcao!=5); //5 == Sair

    return 0;
}