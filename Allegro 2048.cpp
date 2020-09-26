// Allegro 2048.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <stdio.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_native_dialog.h"
#include <iostream>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#include "Pilha_LE.h" 
#include "estrutura.h"
#include "controles.h"


/*inicio do jogo*/
#define TAM 4

//Def de variaveis globais
int tab[TAM][TAM] = { 0 };

char tecla = 0;
char resp = 0;
no* L;

void jogar(ALLEGRO_DISPLAY* janela);
void restart(ALLEGRO_DISPLAY* janela);

int main() {
    srand(time(NULL)); //Comando para a pseudoaleatoriedade
    al_init();
    //Janela
    ALLEGRO_DISPLAY* janela = NULL;
    //Cria a janela
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    al_set_window_position(janela, 100, 100);
    al_set_window_title(janela, "2048 game");
    // Preenche a tela com a cor branca
    al_clear_to_color(al_map_rgb(255, 255, 255));

    //Declara a fila de eventos
    ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
    //Cria fila de eventos
    fila_eventos = al_create_event_queue();

    //registra eventos da janela em fila_eventos
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));

    inicializa_tabuleiro(tab, &pont);
    imprime_tabuleiro(tab, &recorde, &pont, janela);
    //jogar(janela);
    while (1) {
        //declara variavel que recebe evento e timeout
        ALLEGRO_EVENT evento;
        //espero por um evento da fila, e guarda em evento
        al_wait_for_event(fila_eventos, &evento);

        //Se teve eventos e foi um evento de fechar janela, encerra repetição
        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            int resp = al_show_native_message_box(janela, "Fechar", "Deseja sair do jogo?", "", NULL, ALLEGRO_MESSAGEBOX_YES_NO);
            if (resp)
                break;
        }
        al_flip_display();
    }

    //destroi janela e fila de eventos ao fim
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);

    return 0;
}

void restart(ALLEGRO_DISPLAY* janela) {
    int flag = 0;
    if (perde(tab) == 1) {
        printf("\nVoc%c perdeu!\n", 136);
        printf("PLACAR: %d\n", pont);
        printf("Gostaria de jogar novamente? (S / N)\n");
        do {
            //resp = getch();
            if ((resp == 's') || (resp == 'S')) {
                system("cls");
                jogar(janela);
                flag++;
            }
            else if ((resp == 'n') || (resp == 'N')) {
                printf("\nObrigado por jogar!\n");
                printf("Seu recorde: %d\n", recorde);
                system("PAUSE");
                flag++;
            }
        } while (flag == 0);
    }
}

void jogar(ALLEGRO_DISPLAY* janela) {
    int i, j;
    inicializa_tabuleiro(tab, &pont);
    imprime_tabuleiro(tab, &recorde, &pont, janela);
    do {
        //tecla = getch();
        if ((tecla == 'N') || (tecla == 'n'))
            inicializa_tabuleiro(tab, &pont);
        if (movimentos(tab, tecla, &pont, &L) == 1)
            num_aleatorio(tab);
        system("cls");
        testa_recorde(&pont, &recorde);
        imprime_tabuleiro(tab, &recorde, &pont, janela);
        for (i = 0; i < TAM; i++) {
            for (j = 0; j < TAM; j++) {
                if (tab[i][j] == 2048) {
                    printf("\nParab%cns! Voc%c ganhou!\n", 130, 136);
                    printf("PLACAR: %d\n", pont);
                    printf("Gostaria de jogar novamente? (S / N)\n");
                    //resp = getch();
                    if ((resp == 's') || (resp == 'S'))
                        jogar(janela);
                }
            }
        }
    } while ((tecla != 27) && (perde(tab) != 1));
    restart(janela);
}

