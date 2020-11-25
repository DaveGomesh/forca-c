#ifndef FORCA_H_INCLUDED
#define FORCA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

// Constantes importantes do jogo
#define TAM_PALAVRAS 71
#define QUANT_ARQS 4
#define QUANT_CATEGORIAS 3
#define QUANT_PALAVRAS 5
#define QUANT_TEMPO 60

// Estrutura do jogo
typedef struct tipo_forca{
    char palavra[TAM_PALAVRAS];
    char visualizacao[TAM_PALAVRAS];
    char dica[TAM_PALAVRAS];
    char digitadas[27];
    int  quantLetras;
    int  quantLetrasDiferentes;
} Forca;

// Declaracao de Funcoes
void escolherPalavra(Forca * forca);
void inicializar(Forca * forca);
int  fazerJogada(Forca * forca);
void jogar(Forca * forca);
// Funcoes de exibicao
void exibirTempoRestante(int tempRest);
void exibirLetrasDigitadas(Forca * forca);
void exibirDica(Forca * forca);
void exibirForca(int chances);
void exibirPalavra(Forca * forca);
void exibirChances(int chances);
void exibirMensagemVitoria();
void exibirMensagemDerrota();
//Funcao de controle de cor
void setCorPadrao();

// Implementacao de funcoes
// Abre um arquivo aleatorio e escolhe uma palavra aleatoria dentro dele
void escolherPalavra(Forca * forca){
    FILE * f_Arq;

    //Guarda o caminho dos arquivos
    char arquivos[QUANT_ARQS][30] = {
        {"palavras\\animais.txt"},
        {"palavras\\comidas.txt"},
        {"palavras\\veiculos.txt"},
        {"palavras\\objetos.txt"}
    };

    //Gera um numero aleatorio pra abrir o arquivo
    int arqAle = rand() % QUANT_ARQS;
    f_Arq = fopen(arquivos[arqAle], "r");

    //Caso esse arquivo nao possa ser aberto ele sera criado
    if(f_Arq == NULL){
        f_Arq = fopen(arquivos[arqAle], "w");
        fprintf(f_Arq, "Arquivo: '%s'\n", arquivos[arqAle]);
        fclose(f_Arq);
        return;
    }

    //Com base no arquivo aberto, sera atribuido uma dica ao jogo
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

    char temp[TAM_PALAVRAS];
    int quantPalavras=0;

    //Conta quantas palavras tem no arquivo selecionado
    while(fgets(temp, TAM_PALAVRAS, f_Arq)!=NULL){
        quantPalavras++;
    }

    //Move o cursor de volta para o comeco do arquivo
    rewind(f_Arq);

    //Gera um numero aleatorio para selecionar uma palavra dentro do arquivo
    int palAle = rand() % quantPalavras;

    //Busca a palavra correspondente no arquivo
    for(int i=0; i<=palAle; i++){
        fgets(forca->palavra, TAM_PALAVRAS, f_Arq);
    }

    //Remove o '\n' e coloca o '\0' na string
    forca->palavra[strlen(forca->palavra)-1] = '\0';

    //Fecha o arquivo
    fclose(f_Arq);

    unsigned int i;

    //Prepara a string de visualizacao, isto e,
    //coloca '_' onde tem letra, para esconde-las, aproveitando para contar as letras,
    //E deixa o '-' onde tem hifen. O hifen nao eh contado
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
}

// Prepara todas as variaveis para iniciar o jogo
void inicializar(Forca * forca){
    //Zera as variaveis de controle
    forca->digitadas[0] = '\0';
    forca->quantLetrasDiferentes = 0;
    forca->quantLetras = 0;

    //Escolhe uma palavra
    escolherPalavra(forca);

    //Define a cor padrap
    setCorPadrao();
}

// Recebe uma letra digitada pelo usuario e a verifica, retornando a quantidade de ocorrencias
int fazerJogada(Forca * forca){
    int encontrou=0;
    char letra;
    
    //Se alguma tecla for pressionada
    if(kbhit()){
        //Guarda esse tecla
        letra = getch();

        //Converte para maiusculas
        letra = toupper(letra);

        //Se nao for uma letra digitada, ignora essa tecla digitada
        if(letra < 65 || letra > 90){
            return -2;
        }

        //Verifica se essa letra ja foi digitada e retorna -1 se sim
        for(int i=0; i<=forca->quantLetrasDiferentes; i++){
            if(forca->digitadas[i] == letra){
                return -1;
            }
        }

        //Como a letra ainda nao foi digitada, ela eh guardada para que nao possa mais ser utilizada
        forca->digitadas[forca->quantLetrasDiferentes] = letra;
        forca->quantLetrasDiferentes++;
        
        forca->digitadas[forca->quantLetrasDiferentes] = '\0';

        //Procura essa letra na palavra, guardando quantas vezes ela foi encontrada
        for(int i=0; i<strlen(forca->palavra); i++){
            if(letra == forca->palavra[i]){
                forca->visualizacao[i] = forca->palavra[i];
                encontrou++;
            }
        }

        //Retorna quantas vezes a letra foi encontrada na palavra
        return encontrou;
    }

    //Retorna -2 caso nenhuma tecla tenha sido pressionada
    return -2;
}

// Controla o jogo
void jogar(Forca * forca){
    int quantLetrasEncontradas=-2, chances=7, quantLetrasCorretas=0;

    time_t tempoFinal, tempoAtual;
    int tempoRestante;
    
    system("cls");

    //Obtem o tempo final do jogo
    tempoFinal = time(NULL) + QUANT_TEMPO;
    tempoRestante = QUANT_TEMPO;

    //Exibe a interface do jogo inicial
    exibirTempoRestante(tempoRestante);
    exibirLetrasDigitadas(forca);
    exibirDica(forca);
    exibirForca(chances);
    exibirPalavra(forca);
    exibirChances(chances);

    do{
        //Obtem o tempo atual
        tempoAtual = time(NULL);

        //Se tiver passado 1 segundo desde a ultima vez que o tempo atual foi obtido
        if(tempoFinal - tempoAtual != tempoRestante){
            //Atualiza o tempo na interface
            tempoRestante = tempoFinal - tempoAtual;
            exibirTempoRestante(tempoRestante);
        }

        switch(quantLetrasEncontradas){
            //Nenhuma letra digitada
            case -2:
            break;

            //Letra ja foi digitada
            case -1:
                gotoxy(1, 19);
                printf("LETRA JA DIGITADA!\n");
            break;

            //Letra incorreta digitada
            case 0:
                exibirLetrasDigitadas(forca);
                chances--;
                exibirForca(chances);
                exibirChances(chances);
            break;

            //Letra correta digitada
            default:
                gotoxy(1, 15);
                exibirLetrasDigitadas(forca);
                exibirPalavra(forca);

                //Remove uma possivel mensagem de "Letra ja digitada" que talvez possa ter
                gotoxy(1, 19);
                printf("                   \n");
            break;
        }
        
        //Chama a funcao de fazer a jogada e guarda a quantidade de letras encontradas ou os valores de controle da funcao
        quantLetrasEncontradas = fazerJogada(forca);

        //Se todas as chances se acabarem, encerra o jogo com derrota
        if(chances==0){
            system("cls");
            exibirMensagemDerrota();
            return;
        }

        //Se for retornado um valor de controle passa para a proxima iteracao do laco
        if(quantLetrasEncontradas == -1 || quantLetrasEncontradas == -2){
            continue;
        }

        //Atualiza a quantidade de letras corretas digitadas
        quantLetrasCorretas += quantLetrasEncontradas;

        //Se todas as letras corretas forem encontradas, encerra o jogo com vitoria
        if(quantLetrasCorretas==forca->quantLetras){
            system("cls");
            printf("PALAVRA: %s\n", forca->palavra);
            exibirMensagemVitoria();
            return;
        }

        // gotoxy(1, 20);
        // printf("Detalhes (temp):\n");
        // printf("Quant Let Atu: %i\n", quantLetrasEncontradas);
        // printf("Quant Let Enc: %i\n", quantLetrasCorretas);
        // printf("Tam Word: %i\n", forca->quantLetras);

    //Enquanto o tempo nao zerar
    }while(tempoFinal != tempoAtual);

    system("cls");
    printf("O TEMPO ACABOU!");
    exibirMensagemDerrota();
}

// Exibe o tempo restante para acabar o jogo
void exibirTempoRestante(int tempRest){
    gotoxy(1,1);
    printf("Voce tem %i segundos restantes!\n", tempRest);
}

// Exibe as letras digitadas no jogo
void exibirLetrasDigitadas(Forca * forca){
    gotoxy(1, 2);
    printf("Letras Digitadas: ");
    for(int i=0;forca->digitadas[i]!='\0';i++){
        printf("%c ", forca->digitadas[i]);
    }
}

// Exibe a dica do jogo
void exibirDica(Forca * forca){
    printf("\n\nDICA: %s\n\n", forca->dica);
}

// Exibe a forca e o boneco com base nas chances restantes
void exibirForca(int chances){
    gotoxy(1, 6);
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      ");

    textcolor(WHITE);
    printf("%s      \n", chances < 7 ? "(_)":" ");
    textcolor(RED);

    printf(" |      ");
    
    textcolor(WHITE);
    printf("%c%c%c  \n", chances < 4 ? '\\':' ', chances < 6 ? '|':' ', chances < 3? '/':' ');
    textcolor(RED);

    printf(" |       ");

    textcolor(WHITE);
    printf("%c     \n", chances < 5 ? '|' : ' ');
    textcolor(RED);

    printf(" |      ");

    textcolor(WHITE);
    printf("%c %c   \n", chances < 2 ? '/':' ', chances < 1 ? '\\': ' ');
    textcolor(RED);

    printf(" |              \n");
    printf("_|___           \n\n");
}

// Exibe o que esta guardado em visualizacao
void exibirPalavra(Forca * forca){
    gotoxy(1, 15);
    for(int i=0;i<strlen(forca->palavra);i++){
        printf("%c ", forca->visualizacao[i]);
    }

    printf("\n\n");
}

// Exibe a quantidade de chances restantes
void exibirChances(int chances){
    gotoxy(1, 17);
    printf("CHANCES: %i\n", chances);

    //Remove uma possivel mensagem de "Letra ja digitada" que talvez possa ter
    gotoxy(1, 19);
    printf("                   \n");
}

// Mensagem de vitoria
void exibirMensagemVitoria(){
    printf("\nPARABENS, VOCE VENCEU\n\n");
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
    printf("Dessa vez voce escapou...\n");
    printf("Pressione qualquer tecla para continuar...");
    getch();
}

// Mensagem de derrota
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
    printf("Pressione qualquer tecla para continuar...");
    getch();
}

// Reseta a cor padrao do jogo
void setCorPadrao(){
    textcolor(RED);
    backgroundcolor(BLACK);
}

#endif /* FORCA_H_INCLUDED */