#pragma once
/*funçoes para:
    tabuleiro do jogo
    geração de peças
    combinação de peças
*/
#define TAM 4
#define NUM_INI 2

//Atributos da tela
#define LARGURA_TELA 1000
#define ALTURA_TELA 600

int pont = 0;
int recorde = 0; 

void imprime_tabuleiro(int tab[4][4], int* recorde, int* pont, ALLEGRO_DISPLAY* janela);
void num_aleatorio(int tab[TAM][TAM]);
int perde(int tab[TAM][TAM]);
void inicializa_tabuleiro(int tab[TAM][TAM], int* pont);
void testa_recorde(int* pont, int* recorde);

void testa_recorde(int* pont, int* recorde) {
    if (*pont > * recorde)
        *recorde = *pont;
}

void fecha_tabuleiro(int *i, int *j, ALLEGRO_FONT* tabuleiro) {
    al_draw_text(tabuleiro, al_map_rgb(0, 0, 0), LARGURA_TELA / 3 + 100 * ((*j) + 1), 300 + 52 * (*i), ALLEGRO_ALIGN_LEFT, "|");
}

//Função que imprime o tabuleiro juntamente com os pontos, a melhor pontuação e mostra a opção de novo jogo (pressionando a tecla N).
// Obs: ainda falta criar uma função para mostrar a melhor pontuação e uma que associe a tecla N à função inicializa_tabuleiro(tab, &pont).
void imprime_tabuleiro(int tab[4][4], int* recorde, int* pont, ALLEGRO_DISPLAY* janela) {
    int i, j, aux = 1;

    //Inicialização para o uso de fontes
    al_init_font_addon();
    al_init_ttf_addon();

    //Arquivo de fonte
    ALLEGRO_FONT* fonte = NULL;
    ALLEGRO_FONT* tabuleiro = NULL;
 
    //Carregando o arquivo de fonte com uma true type font
    fonte = al_load_font("YARDSALE.ttf", 36, 0);
    tabuleiro = al_load_font("YARDSALE.ttf", 48, 0);

    // Texto alinhado à esquerda
    al_draw_textf(fonte, al_map_rgb(0, 0, 0), 10, 10, ALLEGRO_ALIGN_LEFT, "RECORDE: %d", *recorde);

    al_draw_textf(fonte, al_map_rgb(0, 0, 0), 10, 50, ALLEGRO_ALIGN_LEFT, "PLACAR: %d", *pont);

    al_draw_text(fonte, al_map_rgb(0, 0, 0), 10, 90, ALLEGRO_ALIGN_LEFT, "NOVO JOGO - N");

    //al_draw_text(fonte, al_map_rgb(0, 0, 0), 10, 130, ALLEGRO_ALIGN_LEFT, "SAIR - Esc");

    
    for (i = 0; i < 4; i++) {
         al_draw_text(tabuleiro, al_map_rgb(0, 0, 0), LARGURA_TELA/3, 300 + 50*i, ALLEGRO_ALIGN_LEFT, "|");
        for (j = 0; j < 4; j++) {
            switch (tab[i][j]) {
            case 2:
                al_draw_textf(fonte, al_map_rgb(255, 20, 147), LARGURA_TELA / 3 + 100 * (j + 1/2), 300 + 52 * i, ALLEGRO_ALIGN_LEFT, "%*d", 5, tab[i][j]);
                fecha_tabuleiro(&i, &j, tabuleiro);
                break;
            case 4:
                al_draw_textf(fonte, al_map_rgb(0, 255, 255), LARGURA_TELA / 3 + 100 * (j + 1 / 2), 300 + 52 * i, ALLEGRO_ALIGN_LEFT, "%*d", 5, tab[i][j]);
                fecha_tabuleiro(&i, &j, tabuleiro);
                break;
            case 8:
                al_draw_textf(fonte, al_map_rgb(0, 255, 0), LARGURA_TELA / 3 + 100 * (j + 1 / 2), 300 + 52 * i, ALLEGRO_ALIGN_LEFT, "%*d", 4, tab[i][j]);
                fecha_tabuleiro(&i, &j, tabuleiro);
                break;
            case 16:
                al_draw_textf(fonte, al_map_rgb(255, 0, 0), LARGURA_TELA / 3 + 100 * (j + 1 / 2), 300 + 52 * i, ALLEGRO_ALIGN_LEFT, "%*d", 4, tab[i][j]);
                fecha_tabuleiro(&i, &j, tabuleiro);
                break;
            case 32:
                al_draw_textf(fonte, al_map_rgb(0, 0, 255), LARGURA_TELA / 3 + 100 * (j + 1 / 2), 300 + 52 * i, ALLEGRO_ALIGN_LEFT, "%*d", 4, tab[i][j]);
                fecha_tabuleiro(&i, &j, tabuleiro);
                break;
            case 64:
                al_draw_textf(fonte, al_map_rgb(255, 0, 255), LARGURA_TELA / 3 + 100 * (j + 1 / 2), 300 + 52 * i, ALLEGRO_ALIGN_LEFT, "%*d", 4, tab[i][j]);
                fecha_tabuleiro(&i, &j, tabuleiro);
                break;
            case 128:
                al_draw_textf(fonte, al_map_rgb(255, 100, 0), LARGURA_TELA / 3 + 100 * (j + 1 / 2), 300 + 52 * i, ALLEGRO_ALIGN_LEFT, "%*d", 3, tab[i][j]);
                fecha_tabuleiro(&i, &j, tabuleiro);
                break;
            case 256:
                al_draw_textf(fonte, al_map_rgb(0, 100, 100), LARGURA_TELA / 3 + 100 * (j + 1 / 2), 300 + 52 * i, ALLEGRO_ALIGN_LEFT, "%*d", 3, tab[i][j]);
                fecha_tabuleiro(&i, &j, tabuleiro);
                break;
            case 512:
                al_draw_textf(fonte, al_map_rgb(75, 25, 100), LARGURA_TELA / 3 + 100 * (j + 1 / 2), 300 + 52 * i, ALLEGRO_ALIGN_LEFT, "%*d", 3, tab[i][j]);
                fecha_tabuleiro(&i, &j, tabuleiro);
                break;
            case 1024:
                al_draw_textf(fonte, al_map_rgb(125, 125, 125), LARGURA_TELA / 3 + 100 * (j + 1 / 2), 300 + 52 * i, ALLEGRO_ALIGN_LEFT, "%*d", 2, tab[i][j]);
                fecha_tabuleiro(&i, &j, tabuleiro);
                break;
            case 2048:
                al_draw_textf(fonte, al_map_rgb(245, 79, 85), LARGURA_TELA / 3 + 100 * (j + 1 / 2), 300 + 52 * i, ALLEGRO_ALIGN_LEFT, "%*d", 2, tab[i][j]);
                fecha_tabuleiro(&i, &j, tabuleiro);
                break;
            default:
                al_draw_text(tabuleiro, al_map_rgb(0, 0, 0), LARGURA_TELA/3 + 100*(j+1), 300 + 52*i, ALLEGRO_ALIGN_LEFT, "|");
                break;
            }
        }
    }
    //Atualiza a tela
    al_flip_display();

    //Desalocação das fontes 
    al_destroy_font(fonte);
    al_destroy_font(tabuleiro);
}

int verifica_vazio(int tab[4][4]) { // retorna 1 se tiver algum espaço, ou retorna 0 se estiver cheio
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tab[i][j] == 0)
                return 1;
        }
    }
    return 0;
}

//Função que adiciona um número aleatório após a moviventação das peças do jogo a cada rodada, podendo ser 2 ou 4.
void num_aleatorio(int tab[TAM][TAM]) {
    int i, j, aux = 0;
    while (aux < 1) {
        i = rand() % 4;
        j = rand() % 4;
        if (tab[i][j] == 0) {
            tab[i][j] = (rand() & 3) ? 2 : 4; //Possibilidades: 60% de gerar o número 2 e 40% o número 4.         
            aux++;
        }
    }
}

//Função que percorre todo o tabuleiro procurando espaços, se não houver nenhum espaço, o jogador perdeu.
int perde(int tab[TAM][TAM]) {
    int cont = 0;
    if (!verifica_vazio(tab)) { // se tiver espaço livre ele ignora
        for (int i = 1; i <= (TAM / 2); i++) {
            for (int j = 0; j < TAM; j++) {
                if ((tab[i][j] == tab[i + 1][j]) || (tab[i][j] == tab[i - 1][j])) //Verifica se ainda pode ocorrer algum movimento somando valores.
                    cont++;
            }
        }
        for (int j = 1; j <= (TAM / 2); j++) {
            for (int i = 0; i < TAM; i++) {
                if ((tab[i][j] == tab[i][j + 1]) || (tab[i][j] == tab[i][j - 1])) //Verifica se ainda pode ocorrer algum movimento somando valores.
                    cont++;
            }
        }
        if (cont == 0) //Significa que não há espaços para adicionar mais blocos no tabuleiro e não pode ocorrer nenhum movimento.(Fim de Jogo)
            return 1;

        return 0; //Ainda há espaço no tabuleiro para adicionar mais blocos e é possível movimentar algum bloco.
    }
}

//Função que zera o tabuleiro e o valor da pontuação.
void inicializa_tabuleiro(int tab[TAM][TAM], int* pont) {
    *pont = 0;
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tab[i][j] = 0;
        }
    }
    for (int i = 0; i < NUM_INI; i++) { //geração dos primeiros números aleátorios
        num_aleatorio(tab);
    }
}