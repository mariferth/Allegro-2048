// Allegro 2048.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <stdio.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"

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


//Tabuleiro global
int tab[TAM][TAM] = { 0 };

//Pilha 
no* L;

void jogar(ALLEGRO_DISPLAY* janela, ALLEGRO_BITMAP* fundo, ALLEGRO_EVENT_QUEUE* fila_eventos);
void restart(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, ALLEGRO_BITMAP* fundo);
void sair(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos);

int main() {
    srand(time(NULL)); //Comando para a pseudoaleatoriedade
    
    //Allegro init - janela / fundo 
    ALLEGRO_DISPLAY* janela = NULL;
    ALLEGRO_BITMAP* fundo = NULL;
    ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
    
    al_init();
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();

    //janela
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    al_set_window_position(janela, 100, 100);
    al_set_window_title(janela, "2048");
    al_clear_to_color(al_map_rgb(255, 255, 255));

    //fundo
    fundo = al_load_bitmap("background.png");
    al_draw_bitmap(fundo, 0, 0, 0);
    
    //fila_eventos
    fila_eventos = al_create_event_queue();

    jogar(janela, fundo, fila_eventos);


    return 0;
}

//Função que inicia o jogo
void jogar(ALLEGRO_DISPLAY* janela, ALLEGRO_BITMAP* fundo, ALLEGRO_EVENT_QUEUE* fila_eventos) {
    cor_tab = rand() % 10000;
    
    //Cria fila de eventos para janela e teclado
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());

    //Inicialização tabuleiro
    inicializa_tabuleiro(tab, &pont);
    imprime_tabuleiro(tab, &recorde, &pont, janela, fundo);
    
    /* 
    TECLA 0  -->  NOVO JOGO
    TECLA 1  -->  ESQUERDA
    TECLA 2  -->  DIREITA
    TECLA 3  -->  CIMA
    TECLA 4  -->  BAIXO
    */
    int tecla = NULL;
    int fim = 0;
    while (fim == 0) {
        //Variavel que espera por eventos
        ALLEGRO_EVENT evento;
        al_wait_for_event(fila_eventos, &evento);

        //Se teve eventos e foi um evento de fechar janela, encerra repetição
        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            fim++;
        }

        if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (evento.keyboard.keycode) {
                //N - novo jogo
            case ALLEGRO_KEY_N:
                tecla = 0;
                break;
                //seta para cima
            case ALLEGRO_KEY_LEFT:
                tecla = 1;
                break;
                //seta para baixo
            case ALLEGRO_KEY_RIGHT:
                tecla = 2;
                break;
                //seta para esquerda
            case ALLEGRO_KEY_UP:
                tecla = 3;
                break;
                //seta para direita.
            case ALLEGRO_KEY_DOWN:
                tecla = 4;
                break;
            }

            if (tecla != 0) {
                if (movimentos(tab, tecla, &pont, &L)) {
                    num_aleatorio(tab);
                }
            }
            else if(tecla == 0) {
                restart(janela, fila_eventos, fundo);
                return;
            }
        }

        testa_recorde(&pont, &recorde);
        imprime_tabuleiro(tab, &recorde, &pont, janela, fundo);
        
        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                if (tab[i][j] == 2048) {
                    int ganhou = al_show_native_message_box(janela, "Parabéns! Você ganhou!", "Deseja jogar de novo?", "", NULL, ALLEGRO_MESSAGEBOX_YES_NO);
                    if (ganhou == 1) {
                        restart(janela, fila_eventos, fundo);
                    }
                    else {
                        fim++;
                        break;
                    }
                }
            }
        }

        if (perde(tab) == 1) {
            int perdeu = al_show_native_message_box(janela, "Você perdeu!", "Deseja jogar de novo?", "", NULL, ALLEGRO_MESSAGEBOX_YES_NO);
            if (perdeu == 1) {
                restart(janela, fila_eventos, fundo);
            }
            else {
                fim++;
            }
        }  
    }
    sair(janela, fila_eventos);
}

//Reinicia o jogo
void restart(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, ALLEGRO_BITMAP* fundo){
    sair(janela, fila_eventos);

    //ALLEGRO_DISPLAY* janela = NULL;
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    al_set_window_position(janela, 100, 100);
    al_set_window_title(janela, "2048");
    al_clear_to_color(al_map_rgb(255, 255, 255));

    //ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
    fila_eventos = al_create_event_queue();

    jogar(janela, fundo, fila_eventos);
}

//Exclui a janela e a fila de eventos
void sair (ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos) {
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela);
}

