#include <stdlib.h>

ESTADO *inicializar_estado() {
    ESTADO *e = (ESTADO *) malloc(sizeof(ESTADO));
    int x,y;
    for(y=0;y<8;y++) {
        for (x=0; x<8; x++) {
            e->tab[x][y] = VAZIO;
        }
    }
      
    e->ultima_jogada.x = 4;
    e->ultima_jogada.y = 3; 
    e->tab[4][3] = BRANCA; //posicao da peca branca no inicio do jogo
    e->num_jogadas = 0; 
    e->jogador_atual = 1;
    //e->jogadas

    return e;
}
//int obter_jogador_atual(ESTADO *estado){

int obter_jogador_atual(ESTADO *e) {
    return e->jogador_atual;
}

//int obter_numero_de_jogadas(ESTADO *estado){
int obter_numero_de_jogadas(ESTADO *e) {
return e->num_jogadas;
}

void add_comando(ESTADO *e){
    e->num_comandos += 1;
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

void alterar_casa(ESTADO *e, COORDENADA c)
{
    int x = obter_ultima_jogada(e).x;
    int y = obter_ultima_jogada(e).y;

    e -> tab[x][y] = PRETA;
    e -> tab[c.x][c.y] = BRANCA;
}

int alterar_ultima_jogada(ESTADO *e, COORDENADA c) {
    e->ultima_jogada.x = c.x;
    e->ultima_jogada.y = c.y;
}
