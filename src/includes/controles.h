
int movimentos(int tab[4][4], int tecla, int* pont, no** L);
void atualiza_soma(int tab[4][4], int tecla, no** L);

//CONTROLE DOS BLOCOS

int movimentos(int tab[4][4], int tecla, int* pont, no** L) {
    int i, j, aux2, aux, soma, move = 1;
    int cont_mov = 0;

    switch (tecla) {
    case 1: //Seta para a esquerda   
        for (i = 0; i < 4; i++) {
            aux2 = 0; //A variável aux2 delimita o laço "for" com a variável aux.
            for (j = 1; j < 4; j++) { //A coluna j começa no 1, pois se fosse no 0 não teria como ir para a esquerda.
                if (tab[i][j] != 0) { //Verifica se o número nessa posição é diferente de 0 para que haja movimentação.
                    aux = j; //aux é usado para que a variável j (coluna) não seja alterada dentro do loop.
                    for (aux; aux > aux2; aux--) { //Posiciona o número até j = 0 no máximo.
                        if (tab[i][aux - 1] == 0) { //Se o número anterior é 0, há o deslocamento.
                            tab[i][aux - 1] = tab[i][aux];
                            tab[i][aux] = 0;
                            cont_mov++;
                        }
                        else if ((tab[i][aux - 1] == tab[i][aux]) && (tab[i][aux - 1] != -1)) { //Se o número anterior é igual e esse número não é -1, ocorre a soma. 
                            soma = tab[i][aux - 1] + tab[i][aux];
                            PUSH(L, soma); //Armazena o valor da soma em uma pilha.
                            tab[i][aux - 1] = -1; //Para que impessa outra soma neste local novamente.
                            tab[i][aux] = 0;
                            (*pont) += 4; //Pontuação recebe 4 unidades a mais, cada vez que dois blocos iguais são unidos.
                            cont_mov++;
                        }
                    }
                }
            }
        }
        break;
    case 2: //Seta para a direita
        for (i = 0; i < 4; i++) {
            aux2 = 3; //A variável aux2 delimita o laço "for" com a variável aux.
            for (j = 2; j >= 0; j--) { //A coluna j começa no 2, pois se fosse no 3 não teria como ir para a direita.
                if (tab[i][j] != 0) { //Verifica se o número nessa posição é diferente de 0 para que haja movimentação.
                    aux = j; //aux é usado para que a variável j (coluna) não seja alterada dentro do loop.
                    for (aux; aux < aux2; aux++) { //Posiciona o número até j = 3 no máximo.
                        if (tab[i][aux + 1] == 0) { //Se o número posterior é 0, há o deslocamento.
                            tab[i][aux + 1] = tab[i][aux];
                            tab[i][aux] = 0;
                            cont_mov++;
                        }
                        else if ((tab[i][aux + 1] == tab[i][aux]) && (tab[i][aux + 1] != -1)) { //Se o número posterior é igual e esse número não é -1, ocorre a soma.
                            soma = tab[i][aux + 1] + tab[i][aux];
                            PUSH(L, soma); //Armazena o valor da soma em uma pilha.
                            tab[i][aux + 1] = -1; //Para que impessa outra soma neste local novamente
                            tab[i][aux] = 0;
                            (*pont) += 4; //Pontuação recebe 4 unidades a mais, cada vez que dois blocos iguais são unidos.
                            cont_mov++;
                        }
                    }
                }
            }
        }
        break;
    case 3:   //Seta para cima
        for (j = 0; j < 4; j++) {
            aux2 = 0; //A variável aux2 delimita o laço "for" com a variável aux.
            for (i = 1; i < 4; i++) { //A linha i começa no 1, pois se fosse no 0 não teria como ir para cima.
                if (tab[i][j] != 0) { //Verifica se o número nessa posição é diferente de 0 para que haja movimentação.
                    aux = i; //aux é usado para que a variável i (linha) não seja alterada dentro do loop.
                    for (aux; aux > aux2; aux--) { //Posiciona o número até i = 0 no máximo.
                        if (tab[aux - 1][j] == 0) { //Se o número acima é 0, há o deslocamento.
                            tab[aux - 1][j] = tab[aux][j];
                            tab[aux][j] = 0;
                            cont_mov++;
                        }
                        else if ((tab[aux - 1][j] == tab[aux][j]) && (tab[aux - 1][j] != -1)) { //Se o número acima é igual e esse número não é -1, ocorre a soma.
                            soma = tab[aux - 1][j] + tab[aux][j];
                            PUSH(L, soma); //Armazena o valor da soma em uma pilha.
                            tab[aux - 1][j] = -1; //Para que impessa outra soma neste local novamente.
                            tab[aux][j] = 0;
                            (*pont) += 4; //Pontuação recebe 4 unidades a mais, cada vez que dois blocos iguais são unidos.
                            cont_mov++;
                        }
                    }
                }
            }
        }
        break;
    case 4: //Seta para baixo
        for (j = 0; j < 4; j++) {
            aux2 = 3; //A variável aux2 delimita o laço "for" com a variável aux.
            for (i = 2; i >= 0; i--) { //A linha i começa no 2, pois se fosse no 3 não teria como ir para baixo.
                if (tab[i][j] != 0) { //Verifica se o número nessa posição é diferente de 0 para que haja movimentação.
                    aux = i; //aux é usado para que a variável i (linha) não seja alterada dentro do loop.
                    for (aux; aux < aux2; aux++) {  //Posiciona o número até i = 3 no máximo.
                        if (tab[aux + 1][j] == 0) { //Se o número abaixo é 0, há o deslocamento.
                            tab[aux + 1][j] = tab[aux][j];
                            tab[aux][j] = 0;
                            cont_mov++;
                        }
                        else if ((tab[aux + 1][j] == tab[aux][j]) && (tab[aux + 1][j] != -1)) { //Se o número abaixo é igual e esse número não é -1, ocorre a soma.
                            soma = tab[aux + 1][j] + tab[aux][j];
                            PUSH(L, soma); //Armazena o valor da soma em uma pilha.
                            tab[aux + 1][j] = -1; //Para que impessa outra soma neste local novamente.
                            tab[aux][j] = 0;
                            (*pont) += 4; //Pontuação recebe 4 unidades a mais, cada vez que dois blocos iguais são unidos.
                            cont_mov++;
                        }
                    }
                }
            }
        }
        break;
    default:
        move = 0;
        break;
    }
    atualiza_soma(tab, tecla, *&L);
    if ((verifica_vazio(tab) == 0) || (cont_mov == 0))
        move = 0;

    return move;
}

//Função que altera os valores definidos como -1 na função movimentos(), os quais devem ser o resultado da soma.
void atualiza_soma(int tab[4][4], int tecla, no** L) {
    int i, j, x;
    if (tecla == 1) {
        //Seta para esquerda
        for (i = 3; i >= 0; i--) {
            //Começa a reatribuir o valor do resultado da soma, começando pelo último que foi alterado e colocado na pilha.
            for (j = 3; j >= 0; j--) {
                if (tab[i][j] == -1) { //Verifica se o valor na posição é -1 para ser reatribuído.
                    POP(L, &x); //Retira um valor do topo da pilha.
                    tab[i][j] = x; //Valor atribuído novamente.
                }
            }
        }
    }
    else if (tecla == 2) {
        //Seta para direita
        for (i = 3; i >= 0; i--) {
            //Começa a reatribuir o valor do resultado da soma, começando pelo último que foi alterado e colocado na pilha até o primeiro.
            for (j = 0; j < 4; j++) {
                if (tab[i][j] == -1) { //Verifica se o valor na posição é -1 para ser reatribuído.
                    POP(L, &x); //Retira um valor do topo da pilha.
                    tab[i][j] = x; //Valor atribuído novamente.
                }
            }
        }
    }
    else if (tecla == 3) {
        //Seta para cima
        for (j = 3; j >= 0; j--) {
            //Começa a reatribuir o valor do resultado da soma, a partir do último que foi alterado e colocado na pilha até o primeiro.
            for (i = 3; i >= 0; i--) {
                if (tab[i][j] == -1) { //Verifica se o valor na posição é -1 para ser reatribuído.
                    POP(L, &x); //Retira um valor do topo da pilha.
                    tab[i][j] = x; //Valor atribuído novamente.
                }
            }
        }
    }
    else if (tecla == 4) {
        //Seta para baixo
        for (j = 3; j >= 0; j--) {
            //Começa a reatribuir o valor do resultado da soma, começando pelo último que foi alterado e colocado na pilha até o primeiro.
            for (i = 0; i < 4; i++) {
                if (tab[i][j] == -1) { //Verifica se o valor na posição é -1 para ser reatribuído.
                    POP(L, &x); //Retira um valor do topo da pilha.
                    tab[i][j] = x; //Valor atribuído novamente.
                }
            }
        }
    }
}