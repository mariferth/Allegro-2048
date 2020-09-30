
int movimentos(int tab[4][4], int tecla, int* pont, no** L);
void atualiza_soma(int tab[4][4], int tecla, no** L);

//CONTROLE DOS BLOCOS

int movimentos(int tab[4][4], int tecla, int* pont, no** L) {
    int i, j, aux2, aux, soma, move = 1;
    int cont_mov = 0;
    switch (tecla) {
    case 1: //Seta para a esquerda   
        for (i = 0; i < 4; i++) {
            aux2 = 0; //A vari�vel aux2 delimita o la�o "for" com a vari�vel aux.
            for (j = 1; j < 4; j++) { //A coluna j come�a no 1, pois se fosse no 0 n�o teria como ir para a esquerda.
                if (tab[i][j] != 0) { //Verifica se o n�mero nessa posi��o � diferente de 0 para que haja movimenta��o.
                    aux = j; //aux � usado para que a vari�vel j (coluna) n�o seja alterada dentro do loop.
                    for (aux; aux > aux2; aux--) { //Posiciona o n�mero at� j = 0 no m�ximo.
                        if (tab[i][aux - 1] == 0) { //Se o n�mero anterior � 0, h� o deslocamento.
                            tab[i][aux - 1] = tab[i][aux];
                            tab[i][aux] = 0;
                            cont_mov++;
                        }
                        else if ((tab[i][aux - 1] == tab[i][aux]) && (tab[i][aux - 1] != -1)) { //Se o n�mero anterior � igual e esse n�mero n�o � -1, ocorre a soma. 
                            soma = tab[i][aux - 1] + tab[i][aux];
                            PUSH(L, soma); //Armazena o valor da soma em uma pilha.
                            tab[i][aux - 1] = -1; //Para que impessa outra soma neste local novamente.
                            tab[i][aux] = 0;
                            (*pont) += 4; //Pontua��o recebe 4 unidades a mais, cada vez que dois blocos iguais s�o unidos.
                            cont_mov++;
                        }
                    }
                }
            }
        }
        break;
    case 2: //Seta para a direita
        for (i = 0; i < 4; i++) {
            aux2 = 3; //A vari�vel aux2 delimita o la�o "for" com a vari�vel aux.
            for (j = 2; j >= 0; j--) { //A coluna j come�a no 2, pois se fosse no 3 n�o teria como ir para a direita.
                if (tab[i][j] != 0) { //Verifica se o n�mero nessa posi��o � diferente de 0 para que haja movimenta��o.
                    aux = j; //aux � usado para que a vari�vel j (coluna) n�o seja alterada dentro do loop.
                    for (aux; aux < aux2; aux++) { //Posiciona o n�mero at� j = 3 no m�ximo.
                        if (tab[i][aux + 1] == 0) { //Se o n�mero posterior � 0, h� o deslocamento.
                            tab[i][aux + 1] = tab[i][aux];
                            tab[i][aux] = 0;
                            cont_mov++;
                        }
                        else if ((tab[i][aux + 1] == tab[i][aux]) && (tab[i][aux + 1] != -1)) { //Se o n�mero posterior � igual e esse n�mero n�o � -1, ocorre a soma.
                            soma = tab[i][aux + 1] + tab[i][aux];
                            PUSH(L, soma); //Armazena o valor da soma em uma pilha.
                            tab[i][aux + 1] = -1; //Para que impessa outra soma neste local novamente
                            tab[i][aux] = 0;
                            (*pont) += 4; //Pontua��o recebe 4 unidades a mais, cada vez que dois blocos iguais s�o unidos.
                            cont_mov++;
                        }
                    }
                }
            }
        }
        break;
    case 3:   //Seta para cima
        for (j = 0; j < 4; j++) {
            aux2 = 0; //A vari�vel aux2 delimita o la�o "for" com a vari�vel aux.
            for (i = 1; i < 4; i++) { //A linha i come�a no 1, pois se fosse no 0 n�o teria como ir para cima.
                if (tab[i][j] != 0) { //Verifica se o n�mero nessa posi��o � diferente de 0 para que haja movimenta��o.
                    aux = i; //aux � usado para que a vari�vel i (linha) n�o seja alterada dentro do loop.
                    for (aux; aux > aux2; aux--) { //Posiciona o n�mero at� i = 0 no m�ximo.
                        if (tab[aux - 1][j] == 0) { //Se o n�mero acima � 0, h� o deslocamento.
                            tab[aux - 1][j] = tab[aux][j];
                            tab[aux][j] = 0;
                            cont_mov++;
                        }
                        else if ((tab[aux - 1][j] == tab[aux][j]) && (tab[aux - 1][j] != -1)) { //Se o n�mero acima � igual e esse n�mero n�o � -1, ocorre a soma.
                            soma = tab[aux - 1][j] + tab[aux][j];
                            PUSH(L, soma); //Armazena o valor da soma em uma pilha.
                            tab[aux - 1][j] = -1; //Para que impessa outra soma neste local novamente.
                            tab[aux][j] = 0;
                            (*pont) += 4; //Pontua��o recebe 4 unidades a mais, cada vez que dois blocos iguais s�o unidos.
                            cont_mov++;
                        }
                    }
                }
            }
        }
        break;
    case 4: //Seta para baixo
        for (j = 0; j < 4; j++) {
            aux2 = 3; //A vari�vel aux2 delimita o la�o "for" com a vari�vel aux.
            for (i = 2; i >= 0; i--) { //A linha i come�a no 2, pois se fosse no 3 n�o teria como ir para baixo.
                if (tab[i][j] != 0) { //Verifica se o n�mero nessa posi��o � diferente de 0 para que haja movimenta��o.
                    aux = i; //aux � usado para que a vari�vel i (linha) n�o seja alterada dentro do loop.
                    for (aux; aux < aux2; aux++) {  //Posiciona o n�mero at� i = 3 no m�ximo.
                        if (tab[aux + 1][j] == 0) { //Se o n�mero abaixo � 0, h� o deslocamento.
                            tab[aux + 1][j] = tab[aux][j];
                            tab[aux][j] = 0;
                            cont_mov++;
                        }
                        else if ((tab[aux + 1][j] == tab[aux][j]) && (tab[aux + 1][j] != -1)) { //Se o n�mero abaixo � igual e esse n�mero n�o � -1, ocorre a soma.
                            soma = tab[aux + 1][j] + tab[aux][j];
                            PUSH(L, soma); //Armazena o valor da soma em uma pilha.
                            tab[aux + 1][j] = -1; //Para que impessa outra soma neste local novamente.
                            tab[aux][j] = 0;
                            (*pont) += 4; //Pontua��o recebe 4 unidades a mais, cada vez que dois blocos iguais s�o unidos.
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

//Fun��o que altera os valores definidos como -1 na fun��o movimentos(), os quais devem ser o resultado da soma.
void atualiza_soma(int tab[4][4], int tecla, no** L) {
    int i, j, x;
    if (tecla == 1) {
        //Seta para esquerda
        for (i = 3; i >= 0; i--) {
            //Come�a a reatribuir o valor do resultado da soma, come�ando pelo �ltimo que foi alterado e colocado na pilha.
            for (j = 3; j >= 0; j--) {
                if (tab[i][j] == -1) { //Verifica se o valor na posi��o � -1 para ser reatribu�do.
                    POP(L, &x); //Retira um valor do topo da pilha.
                    tab[i][j] = x; //Valor atribu�do novamente.
                }
            }
        }
    }
    else if (tecla == 2) {
        //Seta para direita
        for (i = 3; i >= 0; i--) {
            //Come�a a reatribuir o valor do resultado da soma, come�ando pelo �ltimo que foi alterado e colocado na pilha at� o primeiro.
            for (j = 0; j < 4; j++) {
                if (tab[i][j] == -1) { //Verifica se o valor na posi��o � -1 para ser reatribu�do.
                    POP(L, &x); //Retira um valor do topo da pilha.
                    tab[i][j] = x; //Valor atribu�do novamente.
                }
            }
        }
    }
    else if (tecla == 3) {
        //Seta para cima
        for (j = 3; j >= 0; j--) {
            //Come�a a reatribuir o valor do resultado da soma, a partir do �ltimo que foi alterado e colocado na pilha at� o primeiro.
            for (i = 3; i >= 0; i--) {
                if (tab[i][j] == -1) { //Verifica se o valor na posi��o � -1 para ser reatribu�do.
                    POP(L, &x); //Retira um valor do topo da pilha.
                    tab[i][j] = x; //Valor atribu�do novamente.
                }
            }
        }
    }
    else if (tecla == 4) {
        //Seta para baixo
        for (j = 3; j >= 0; j--) {
            //Come�a a reatribuir o valor do resultado da soma, come�ando pelo �ltimo que foi alterado e colocado na pilha at� o primeiro.
            for (i = 0; i < 4; i++) {
                if (tab[i][j] == -1) { //Verifica se o valor na posi��o � -1 para ser reatribu�do.
                    POP(L, &x); //Retira um valor do topo da pilha.
                    tab[i][j] = x; //Valor atribu�do novamente.
                }
            }
        }
    }
}