// Allegro 2048.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
using namespace std;

#include "allegro5/allegro.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"

#include "pilha.h" 
#include "estrutura.h"
#include "controles.h"


//Tabuleiro global
int tab[TAM][TAM] = { 0 };

//Pilha 
no* L;

void jogar(ALLEGRO_DISPLAY* janela, ALLEGRO_BITMAP* fundo, ALLEGRO_SAMPLE* pup);
void restart(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, ALLEGRO_BITMAP* fundo, ALLEGRO_SAMPLE* pup);
void sair(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos);

int main() {
    //Comando para a pseudoaleatoriedade
    srand(time(NULL));

    //Allegro init - janela / fundo 
    al_init();
    al_install_keyboard();
    al_install_audio();
    al_init_acodec_addon();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_native_dialog_addon();

    //Janela
    ALLEGRO_DISPLAY* janela = NULL;
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    al_set_window_position(janela, 100, 100);
    al_set_window_title(janela, "2048");
    al_clear_to_color(al_map_rgb(255, 255, 255));

    //Fundo 
    ALLEGRO_BITMAP* fundo = NULL;
    fundo = al_load_bitmap("background.png");
    al_draw_bitmap(fundo, 0, 0, 0);
    
    //Som
    ALLEGRO_SAMPLE* pup = NULL;

    al_reserve_samples(1);

    pup = al_load_sample("pup.ogg");

    jogar(janela, fundo, pup);

    al_destroy_sample(pup);
    al_destroy_bitmap(fundo);
    return 0;
}

//Função que inicia o jogo
void jogar(ALLEGRO_DISPLAY* janela, ALLEGRO_BITMAP* fundo, ALLEGRO_SAMPLE* pup) {
    cor_tab = rand() % 10000;

    //fila_eventos
    ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
    fila_eventos = al_create_event_queue();

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
    int fim = NULL;
    while (fim == 0) {
        //Variavel que espera por eventos
        ALLEGRO_EVENT evento;
        al_wait_for_event(fila_eventos, &evento);

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
            case ALLEGRO_KEY_ESCAPE:
                tecla = 5;
                break;
            default:
                tecla = -1;
                break;
            }
            if (tecla == 5) {
                fim++;
            }
            else if (tecla != 0) {
                if (movimentos(tab, tecla, &pont, &L)) {
                    num_aleatorio(tab);
                    al_play_sample(pup, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                }
            }
            else if (tecla == 0) {
                fim++;
            }
        }

        testa_recorde(&pont, &recorde);
        imprime_tabuleiro(tab, &recorde, &pont, janela, fundo);
        
        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                if (tab[i][j] == 2048) {
                    fim++;
                }
            }
        }

        if (perde(tab) == 1) {
            fim++;
        }  
    }
    if (perde(tab) == 1) {
        int perdeu = al_show_native_message_box(janela, "Você perdeu!", "Deseja jogar de novo?", "", NULL, ALLEGRO_MESSAGEBOX_YES_NO);
        if (perdeu == 1) {
            sair(janela, fila_eventos);
            restart(janela, fila_eventos, fundo, pup);
        }
        else {
            sair(janela, fila_eventos);
        }
    } 
    else if (tecla == 0) {
        sair(janela, fila_eventos);
        restart(janela, fila_eventos, fundo, pup);
    }

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tab[i][j] == 2048) {
                int ganhou = al_show_native_message_box(janela, "Parabéns! Você ganhou!", "Deseja jogar de novo?", "", NULL, ALLEGRO_MESSAGEBOX_YES_NO);
                if (ganhou == 1) {
                    sair(janela, fila_eventos);
                    restart(janela, fila_eventos, fundo, pup);
                }
                else {
                    sair(janela, fila_eventos);
                }
            }
        }
    }
    
}

//Reinicia o jogo
void restart(ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos, ALLEGRO_BITMAP* fundo, ALLEGRO_SAMPLE* pup){
    //sair(janela, fila_eventos);

    //ALLEGRO_DISPLAY* janela = NULL;
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    al_set_window_position(janela, 100, 100);
    al_set_window_title(janela, "2048");
    al_clear_to_color(al_map_rgb(255, 255, 255));

    /*fila_eventos = NULL;
    fila_eventos = al_create_event_queue();*/

    jogar(janela, fundo, pup);
}

//Exclui a janela e a fila de eventos
void sair (ALLEGRO_DISPLAY* janela, ALLEGRO_EVENT_QUEUE* fila_eventos) {
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela);
}
