#include "dados.h"
#include <stdlib.h>
#include <math.h>
#include "logica.h"

ESTADO *inicializar_estado() {
    ESTADO *e = (ESTADO *) malloc(sizeof(ESTADO));
    int x,y;
    for(y=0;y<8;y++) {
        for (x=0; x<8; x++) {
            e->tab[x][y] = VAZIO;
        }
    }

    e->ultima_jogada.x = 4;
    e->ultima_jogada.y = 4;
    e->tab[4][4] = BRANCA; //posicao da peca branca no inicio do jogo
    e->num_jogadas = 0;
    e->jogador_atual = 1;
    e->num_comandos = 0;
    //e->jogadas

    return e;
}

int obter_jogador_atual(ESTADO *e) {
    return e->jogador_atual;
}

int obter_numero_de_jogadas(ESTADO *e) {
    return e->num_jogadas;
}

CASA obter_estado_casa(ESTADO *e, COORDENADA c){
    return e->tab[c.x][c.y];
}

CASA obter_casa(ESTADO *e,int x,int y){
    return e->tab[x][y];
}

COORDENADA obter_ultima_jogada(ESTADO *e){
    return e->ultima_jogada;
}

void alterar_ultima_jogada(ESTADO *e, COORDENADA c) {
    e->ultima_jogada.x = c.x;
    e->ultima_jogada.y = c.y;
}

void alterar_casa(ESTADO *e, COORDENADA c)
{
    int x = obter_ultima_jogada(e).x;
    int y = obter_ultima_jogada(e).y;

    e -> tab[x][y] = PRETA;
    e -> tab[c.x][c.y] = BRANCA;
}

void alterar_jogador_atual(ESTADO *e){
    if(obter_jogador_atual (e) == 1) e->jogador_atual = 2;
    else e->jogador_atual = 1;
}

void alterar_jogadas(ESTADO *e, COORDENADA c){

    if(e->jogador_atual == 1){
        e->jogadas[e->num_jogadas].jogador1.x = c.x;
        e->jogadas[e->num_jogadas].jogador1.y = c.y;
    } else {
        e->jogadas[e->num_jogadas].jogador2.x = c.x;
        e->jogadas[e->num_jogadas].jogador2.y = c.y;
    }
}

void alterar_num_jogadas(ESTADO *e){
    if (obter_jogador_atual(e)== 1)
        e->num_jogadas++;
}

void seeline(char const *linha, int nlinha, ESTADO *e) {
    for (int i = 7; i >= 0; i--) {
        if (linha[i] == '*') {
            e->tab[i][nlinha] = BRANCA;
            e->ultima_jogada.x = i;
            e->ultima_jogada.y = nlinha;
        } else if (linha[i] == '#') {
            e->tab[i][nlinha] = PRETA;
        } else e->tab[i][nlinha] = VAZIO;
    }
}

int jogadas_guardadas(ESTADO *e, int i, int j) {
    if (i < e->num_jogadas)
        return 1;
    else if (e->num_jogadas == i) {
        if (e->jogador_atual == 1)
            return 0;
        else if (j == 1)
            return 1;
    }
    return 0;
}

char* str_jogada_guardada(ESTADO *e, int i, int j) {
    char *string = calloc(3, sizeof(char));            //Não pode ser malloc "slack"
    if (j == 1) {
        string[0] = e->jogadas[i].jogador1.x + 'a';
        string[1] = e->jogadas[i].jogador1.y + '1';
    } else {
        string[0] = e->jogadas[i].jogador2.x + 'a';
        string[1] = e->jogadas[i].jogador2.y + '1';
    }
    return string;
}

void jogadas_anteriores_guardadas(ESTADO *e, char c, int n) {
    if (e->jogador_atual == 2) {
        e->jogadas[e->num_jogadas].jogador2.x = c - 'a';
        e->jogadas[e->num_jogadas].jogador2.y = n - 1;
        e->jogador_atual = 1;
        e->num_jogadas++;
    }else{
        e->jogadas[e->num_jogadas].jogador1.x = c - 'a';
        e->jogadas[e->num_jogadas].jogador1.y = n - 1;
        e->jogador_atual = 2;

    }
}

float distancia_euclidiana(COORDENADA c1 ,COORDENADA c2){

    float d = sqrtf(pow(c1.y - c2.y, 2) + pow(c1.x - c2.x, 2));
    return d;
}

LISTA posicoes_possiveis(ESTADO *e, LISTA l){

    COORDENADA c1 = obter_ultima_jogada(e), c2, *ec;

    for (int i = c1.y - 1; i <= c1.y + 1; i++){
        for (int j = c1.x - 1; j <= c1.x + 1; ++j) {
            c2.y = i;
            c2.x = j;
            if (valida_jogada(e, c2)==1){
                ec = malloc(sizeof(COORDENADA));

                ec->y = c2.y;
                ec->x = c2.x;

                l = insere_cabeca(l, ec);
            }
        }
    }
    return l;
}