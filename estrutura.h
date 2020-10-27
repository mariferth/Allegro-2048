
//Atributos do tabuleiro 
#define TAM 4
#define NUM_INI 2

//Atributos da tela
#define LARGURA_TELA 1000
#define ALTURA_TELA 600

//Pontuação, Recorde e cor das celulas
int pont = 0;
int recorde = 0;
int cor_tab; // var para mudar a cor todo jogo


void inicializa_tabuleiro(int tab[TAM][TAM], int* pont);
void imprime_tabuleiro(int tab[4][4], int* recorde, int* pont, ALLEGRO_DISPLAY* janela, ALLEGRO_BITMAP* fundo);
void num_aleatorio(int tab[TAM][TAM]);
void testa_recorde(int* pont, int* recorde);
int verifica_vazio(int tab[4][4]);
int perde(int tab[TAM][TAM]);

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

//Função que imprime o tabuleiro juntamente com os pontos, a melhor pontuação e mostra a opção de novo jogo (pressionando a tecla N).
void imprime_tabuleiro(int tab[4][4], int* recorde, int* pont, ALLEGRO_DISPLAY* janela, ALLEGRO_BITMAP* fundo) {
    int i, j, aux = 1;

    //Inicialização para o uso de fontes
    al_init_font_addon();
    al_init_ttf_addon();

    //Arquivo de fonte
    ALLEGRO_FONT* fonte = NULL;
 
    //Carregando o arquivo de fonte com uma true type font
    fonte = al_load_font("JandaManateeSolid.ttf", 36, 0);

    //Limpa o tabuleiro
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_bitmap(fundo, 0, 0, 0);

    // Texto alinhado à esquerda
    al_draw_textf(fonte, al_map_rgb(0, 0, 0), 75, 50, ALLEGRO_ALIGN_LEFT, "RECORDE:");
    al_draw_textf(fonte, al_map_rgb(50, 50, 50), 100, 100, ALLEGRO_ALIGN_LEFT, "%d", *recorde);

    al_draw_textf(fonte, al_map_rgb(0, 0, 0), 75, 225, ALLEGRO_ALIGN_LEFT, "PLACAR:");
    al_draw_textf(fonte, al_map_rgb(50, 50, 50), 100, 275, ALLEGRO_ALIGN_LEFT, "%d", *pont);

    al_draw_text(fonte, al_map_rgb(0, 0, 0), 75, 400, ALLEGRO_ALIGN_LEFT, "NOVO JOGO:");
    al_draw_textf(fonte, al_map_rgb(50, 50, 50), 100, 450, ALLEGRO_ALIGN_LEFT, "N");
    
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            int x1 = (j * 135) + 410;
            int y1 = (i * 135) + 35;
            int x2 = (j * 135) + 535;
            int y2 = (i * 135) + 160;
            int round = 10;
            int r = (tab[i][j] * cor_tab) % 255;
            int g = (r * cor_tab) % 255;
            int b = (g * cor_tab) % 255;
            ALLEGRO_COLOR cor = al_map_rgb(r,g,b);
            //al_map_rgb((tab[i][j] * 255) % 7, (tab[i][j] * 255) % 11, (tab[i][j] * 255) % 2);
            if (tab[i][j] != 0) {
                al_draw_filled_rounded_rectangle(x1, y1, x2, y2, round, round, cor);
                al_draw_textf(fonte, al_map_rgb(255, 255, 255), x1+62.5, y1+ 32, ALLEGRO_ALIGN_CENTRE, "%d", tab[i][j]);
            }
            else {
                al_draw_filled_rounded_rectangle(x1, y1, x2, y2, round, round, al_map_rgb(205,192,180));
            }
        }
    }

    //Atualiza a tela
    al_flip_display();

    //Desalocação das fontes 
    al_destroy_font(fonte);
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

//Função para atualizar o recorde 
void testa_recorde(int* pont, int* recorde) {
    if (*pont > * recorde)
        *recorde = *pont;
}

//Retorna 1 se tiver algum espaço vazio
int verifica_vazio(int tab[4][4]) { 
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tab[i][j] == 0)
                return 1;
        }
    }
    return 0;
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
    }
    return 0; //Ainda há espaço no tabuleiro para adicionar mais blocos e é possível movimentar algum bloco.
}


