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

void jogar(ALLEGRO_DISPLAY* janela, ALLEGRO_SAMPLE* pup, ALLEGRO_SAMPLE* win);

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
    
    //Som
    ALLEGRO_SAMPLE* pup = NULL;
    ALLEGRO_SAMPLE* win  = NULL;

    al_reserve_samples(2);

    pup = al_load_sample("pup.ogg");
    win = al_load_sample("win.ogg");

    jogar(janela, pup, win);

    al_destroy_sample(win);
    al_destroy_sample(pup);
    return 0;
}

//Função que inicia o jogo
void jogar(ALLEGRO_DISPLAY* janela, ALLEGRO_SAMPLE* pup, ALLEGRO_SAMPLE* win) {
    cor_tab = rand() % 100;

    //fila_eventos
    ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
    fila_eventos = al_create_event_queue();

    //Cria fila de eventos para janela e teclado
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());

    //Inicialização tabuleiro
    inicializa_tabuleiro(tab, &pont);
    imprime_tabuleiro(tab, &recorde, &pont, janela);
    
    /* 
    TECLA 0  -->  NOVO JOGO
    TECLA 1  -->  ESQUERDA
    TECLA 2  -->  DIREITA
    TECLA 3  -->  CIMA
    TECLA 4  -->  BAIXO
    */

    int tecla = NULL;
    int fim = 0;
    int win_flag = 0;
    while (fim == 0) {
        
        //Variavel que espera por eventos
        ALLEGRO_EVENT evento;
        al_wait_for_event(fila_eventos, &evento);
        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            if (al_show_native_message_box(janela, "", "Deseja realmente sair?", "", NULL, ALLEGRO_MESSAGEBOX_YES_NO) == 1) {
                fim++;
            }
        }
        if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (evento.keyboard.keycode) {
            case ALLEGRO_KEY_N: //N - novo jogo
                tecla = 0;
                break;
            case ALLEGRO_KEY_LEFT: //esquerda
                tecla = 1;
                break;
            case ALLEGRO_KEY_RIGHT://direita
                tecla = 2;
                break;
            case ALLEGRO_KEY_UP://cima
                tecla = 3;
                break;
            case ALLEGRO_KEY_DOWN://baixo
                tecla = 4;
                break;
            case ALLEGRO_KEY_ESCAPE://sair
                tecla = 5;
                break;
            default:
                tecla = -1;
                break;
            }

            if (tecla == 0) { // N
                cor_tab = rand() % 10000;
                win_flag = 0;
                inicializa_tabuleiro(tab, &pont);
            }
            else if (tecla == 5) { // Esc
                if (al_show_native_message_box(janela, "", "Deseja realmente sair?", "", NULL, ALLEGRO_MESSAGEBOX_YES_NO) == 1) {
                    fim++;
                }
            }
            else if (tecla > 0 ) { // Setas
                if (movimentos(tab, tecla, &pont, &L)) {
                    num_aleatorio(tab);
                    al_play_sample(pup, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                }
            } 
        }

        testa_recorde(&pont, &recorde);//Atuliza o record
        imprime_tabuleiro(tab, &recorde, &pont, janela);

        if (verifica_2048(tab) == 1 && win_flag == 0) { // Verifica se chegou a 2048
            al_play_sample(win, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            if (al_show_native_message_box(janela, "Você atingiu 2048!", "Deseja iniciar outra partida?", "", NULL, ALLEGRO_MESSAGEBOX_YES_NO) == 1) {
                inicializa_tabuleiro(tab, &pont);
                imprime_tabuleiro(tab, &recorde, &pont, janela);
                win_flag = 0;
            }
            else {
                win_flag = 1;
            }
        }
        if (perde(tab) == 1) { // Perde a partida
            if (al_show_native_message_box(janela, "Você perdeu!", "Deseja jogar de novo?", "", NULL, ALLEGRO_MESSAGEBOX_YES_NO) == 1) {
                cor_tab = rand() % 100;
                inicializa_tabuleiro(tab, &pont);
                imprime_tabuleiro(tab, &recorde, &pont, janela);
            }
            else {
                fim++;
            }
        }
    }//fim do while 

    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela);
}