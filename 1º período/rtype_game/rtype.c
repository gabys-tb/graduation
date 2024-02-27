#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <string.h>

const float FPS = 100;  

const int SCREEN_W = 960;
const int SCREEN_H = 540;
const int NAVE_W = 100;
const int NAVE_H = 50;
const int VELOCIDADE_NAVE = 2;
const float RAIO_TIRO = 4.0;

typedef struct Nave{
	int x,y;
	int dir_x, dir_y;
	int vel;
	ALLEGRO_COLOR cor;
}Nave;

typedef struct Bloco{
	int x,y;
	int w, h;
	ALLEGRO_COLOR cor;
}Bloco;

typedef struct Tiro {
	float x, y, r;
	ALLEGRO_COLOR cor;
}Tiro ;

typedef struct Inimigo{
	float x, y, r, vel;
	ALLEGRO_COLOR cor;
}Inimigo;

void desenha_cenario(){
	al_clear_to_color(al_map_rgb(250, 190, 40));
}

float randf(){
	return (float)rand()/RAND_MAX;
}


void initNave(Nave *nave ){
	nave -> x = 10 + NAVE_W;
	nave -> y = SCREEN_H/2;
	nave -> dir_x = 0;
	nave -> dir_y = 0;
	nave -> cor = al_map_rgb(240, 73, 112);
	nave -> vel = VELOCIDADE_NAVE;
}

void initBloco(Bloco *bloco){
	bloco->x = SCREEN_W + rand()%(SCREEN_W);
	bloco->y = SCREEN_H/5 + rand()%(2*SCREEN_H/7);
	bloco->w = SCREEN_W + rand()%(2*SCREEN_W/5);
	bloco->h = (2*SCREEN_H/3) * randf();
	bloco->cor = al_map_rgb(0, 193, 118);
}

void initTiro (Tiro  *tiro, Nave nave){
	tiro->x = nave.x;
	tiro->y = nave.y;
	tiro->cor = al_map_rgb(255, 0, 0);
	tiro->r = RAIO_TIRO;
}


void init_inimigo(Inimigo **array_enemies, int j){
	do{
		(*array_enemies)[j].x = SCREEN_W + 3000*randf();
		(*array_enemies)[j].y = SCREEN_H*randf();
		(*array_enemies)[j].r = 30 + 50*randf();
		(*array_enemies)[j].vel = 2 + 2*randf();
		(*array_enemies)[j].cor = al_map_rgb(255*randf(), 255*randf(), 255*randf());
	}
	while((*array_enemies)[j].y - (*array_enemies)[j].r < 0 || (*array_enemies)[j].y + (*array_enemies)[j].r > SCREEN_H);
}

void init_todos_inimigos(Inimigo **array_enemies, int num_enemies){
	for(int j=0; j<num_enemies; j++){
		(*array_enemies)[j].x = SCREEN_W + 3000*randf();
		(*array_enemies)[j].y = SCREEN_H*randf();
		(*array_enemies)[j].r = 30 + 50*randf();
		(*array_enemies)[j].vel = 2 + 2*randf();
		(*array_enemies)[j].cor = al_map_rgb(255*randf(), 255*randf(), 255*randf());
		if((*array_enemies)[j].y - (*array_enemies)[j].r < 0 || (*array_enemies)[j].y + (*array_enemies)[j].r > SCREEN_H){
			j--;
		}
	}
}

void desenha_tiro(Tiro  tiro){
	al_draw_filled_circle(tiro.x, tiro.y, tiro.r, tiro.cor);
}

void desenha_nave(Nave nave){
	al_draw_filled_triangle(nave.x, nave.y, nave.x - NAVE_W, nave.y - NAVE_H/2, nave.x - NAVE_W, nave.y + NAVE_H/2, nave.cor);
}

void desenha_bloco(Bloco bloco){
	al_draw_filled_rectangle(bloco.x, bloco.y, bloco.x + bloco.w, bloco.y + bloco.h, bloco.cor);
}

void desenha_inimigos(Inimigo *array_enemies, int num_enemies){
	for(int i=0; i<num_enemies; i++){
		al_draw_filled_circle(array_enemies[i].x, array_enemies[i].y,array_enemies[i].r, array_enemies[i].cor);
	}
}

void atualiza_Tiro(Tiro  *tiro, Nave nave, int *atira, int colidiu_tiro_bloco, int *aumenta_tiro){
	
	if(*atira == 1){
		if(tiro->x > SCREEN_W || colidiu_tiro_bloco!=0){
			*atira = 0;
			initTiro(tiro, nave);
		}

		tiro->x += 4;
		return;
	}
	else if(*aumenta_tiro == 1 && tiro->r < 12){
		
		tiro->r *= 1.01;
		
		tiro->x = nave.x + tiro->r/2;
		tiro->y = nave.y;
	}
	else{
		tiro->x = nave.x + tiro->r/2;
		tiro->y = nave.y;
	}
}


void atualiza_nave(Nave *nave){
	nave->y += nave->dir_y * nave->vel;
	if(nave->y > SCREEN_H - NAVE_H/2){
		nave->y = SCREEN_H - NAVE_H/2;
	}
	else if(nave->y < NAVE_H/2){
		nave->y = NAVE_H/2;
	}

	nave->x += nave->dir_x * nave->vel;
	if(nave->x > SCREEN_W ){
		nave->x = SCREEN_W;
	}
	else if(nave->x < NAVE_W){
		nave->x = NAVE_W;
	}
}

void atualiza_bloco(Bloco *bloco){
	bloco->x -= 1;

	if(bloco->x + bloco->w < 0){
		initBloco(bloco);
	}
}

void aloca_inimigos(Inimigo **array_enemies, int num_enemies){
	*array_enemies=(Inimigo*)malloc(num_enemies*sizeof(Inimigo));
}


int colisao_inimigo_bloco(Inimigo *array_enemies, Bloco bloco, int i){
	int colisao = 1;

	
	if(array_enemies[i].y -  array_enemies[i].r > bloco.y + bloco.h){
    	colisao = 0;
	}
	else if(array_enemies[i].y + array_enemies[i].r < bloco.y){
		colisao = 0;
	}
	else if(array_enemies[i].x + array_enemies[i].r < bloco.x){
		colisao = 0;
	}
	else if(array_enemies[i].x - array_enemies[i].r > bloco.x + bloco.w){
		colisao = 0;
	}

	return colisao;

}



int colisao_tiro_bloco(Tiro  tiro, Bloco bloco){
	int colisao = 1;

	if(tiro.y -  tiro.r > bloco.y + bloco.h){
    	colisao = 0;
	}
	else if(tiro.y + tiro.r < bloco.y){
		colisao = 0;
	}
	else if(tiro.x + tiro.r < bloco.x){
		colisao = 0;
	}
	else if(tiro.x - tiro.r > bloco.x + bloco.w)
	{
		colisao = 0;
	}
	return colisao;

}

int colisao_tiro_inimigo(Tiro  tiro, Inimigo *array_enemies, int i, Nave nave, int *pontuacao){
	int colisao = 1;

	if(tiro.y -  tiro.r > array_enemies[i].y + array_enemies[i].r){
    	colisao = 0;
	}
	else if(tiro.y + tiro.r < array_enemies[i].y - array_enemies[i].r){
		colisao = 0;
	}
	else if(tiro.x + tiro.r < array_enemies[i].x - array_enemies[i].r){
		colisao = 0;
	}
	else if(tiro.x - tiro.r > array_enemies[i].x +array_enemies[i].r)
	{
		colisao = 0;
	}
	if(tiro.x == nave.x + tiro.r/2){
		colisao = 0;
	}
	if(colisao == 1){
		*pontuacao+= 80 - (int)array_enemies[i].r;
	}
	return colisao;

}

int colisao_inimigo_inimigo(Inimigo *array_enemies, int j, int i){
	int colisao = 1;

	if(array_enemies[j].y -  array_enemies[j].r > array_enemies[i].y + array_enemies[i].r){
    	colisao = 0;
	}
	else if(array_enemies[j].y +array_enemies[j].r < array_enemies[i].y - array_enemies[i].r){
		colisao = 0;
	}
	else if(array_enemies[j].x + array_enemies[j].r < array_enemies[i].x - array_enemies[i].r){
		colisao = 0;
	}
	else if(array_enemies[j].x - array_enemies[j].r > array_enemies[i].x +array_enemies[i].r)
	{
		colisao = 0;
	}
	else if(i == j){
		colisao = 0;
	}
	return colisao;

}

int colisao_nave_inimigos(Nave nave, Inimigo *array_enemies, Tiro tiro, int i){
	int colisao = 1;

	if(nave.y -  NAVE_H/2 > array_enemies[i].y + array_enemies[i].r){
    	colisao = 0;
	}
	else if(nave.y + NAVE_H/2 <array_enemies[i].y - array_enemies[i].r){
		colisao = 0;
	}
	else if(nave.x + 2*tiro.r < array_enemies[i].x - array_enemies[i].r ){
		colisao = 0;
	}
	else if(nave.x - NAVE_W > array_enemies[i].x + array_enemies[i].r)
	{
		colisao = 0;
	}
	return colisao;
	
}

void atualiza_inimigos(Inimigo **array_enemies, int num_enemies, Bloco bloco, Tiro  *tiro, Nave nave, int *atira, int *playing, int *pontuacao){
	int j=0;
	for(int i=0; i<num_enemies; i++){
		if((*array_enemies)[i].x + (*array_enemies)[i].r<0){
			init_inimigo(array_enemies, i);
		}
		else if(colisao_inimigo_bloco(*array_enemies, bloco, i) == 1){
			init_inimigo(array_enemies, i);
		}
		else if(colisao_tiro_inimigo(*tiro, *array_enemies, i, nave, pontuacao) == 1){
			init_inimigo(array_enemies, i);
			if(tiro->r < 12){
				*atira = 0; 
				initTiro(tiro, nave);
			}
		}
		else if(colisao_nave_inimigos(nave, *array_enemies, *tiro, i) == 1){
			*playing = 0;
		}
		for(j=0; j<num_enemies; j++){
			if(colisao_inimigo_inimigo(*array_enemies, j, i)){
				init_inimigo(array_enemies, i);
				init_inimigo(array_enemies, j);
			}
		}
		(*array_enemies)[i].x -= 1 * (*array_enemies)[i].vel;		
	}
}



int colisao_nave_bloco(Nave nave, Bloco bloco){
	int colisao = 1;

	if(nave.y -  NAVE_H/2 > bloco.y + bloco.h){
    	colisao = 0;
	}
	else if(nave.y + NAVE_H/2 < bloco.y){
		colisao = 0;
	}
	else if(nave.x < bloco.x){
		colisao = 0;
	}
	else if(nave.x - NAVE_W > bloco.x + bloco.w)
	{
		colisao = 0;
	}
	return colisao;
}

int Recorde(int pontuacao, int *recorde) {
	FILE *arq = fopen("recorde.dat", "r");
	*recorde = -1;

	int a = 0;

	if(arq != NULL){
		fscanf(arq, "%d", recorde);
		fclose(arq);
	}

	if(*recorde < pontuacao){
		arq = fopen("recorde.dat", "w");
		fprintf(arq, "%d", pontuacao);
		fclose(arq);

		a = 1;
	}
	
	return a;
		
}

 
int main(int argc, char **argv){
	
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
   
	//----------------------- rotinas de inicializacao ---------------------------------------
    
	//inicializa o Allegro
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	
    //inicializa o módulo de primitivas do Allegro
    if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }	
	
	
	//cria um temporizador que incrementa uma unidade a cada 1.0/FPS segundos
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
 
	//cria uma tela com dimensoes de SCREEN_W, SCREEN_H pixels
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	//instala o teclado
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}


	//inicializa o modulo allegro que carrega as fontes
	al_init_font_addon();

	//inicializa o modulo allegro que entende arquivos tff de fontes
	if(!al_init_ttf_addon()) {
		fprintf(stderr, "failed to load tff font module!\n");
		return -1;
	}
	
	//carrega o arquivo arial.ttf da fonte Arial e define que sera usado o tamanho 32 (segundo parametro)
    ALLEGRO_FONT *size_32 = al_load_font("PilotCommand_.otf", 32, 1);   
	if(size_32 == NULL) {
		fprintf(stderr, "font file does not exist or cannot be accessed!\n");
	}

 	//cria a fila de eventos
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}
   
 


	//registra na fila os eventos de tela (ex: clicar no X na janela)
	al_register_event_source(event_queue, al_get_display_event_source(display));
	//registra na fila os eventos de tempo: quando o tempo altera de t para t+1
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	//registra na fila os eventos de teclado (ex: pressionar uma tecla)
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	Nave nave;
	initNave(&nave);

	Bloco bloco;
	initBloco(&bloco);

	Tiro  tiro;
	initTiro (&tiro, nave);

	int atira = 0, colidiu_tiro_bloco =0;

	Inimigo *array_enemies=NULL;
	int num_enemies = 15;
	aloca_inimigos(&array_enemies, num_enemies);
	init_todos_inimigos(&array_enemies, num_enemies);

	int aumenta_tiro = 0;
	int pontuacao = 0;
	int teclou_i = 0;

	//inicia o temporizador
	al_start_timer(timer);
	
	int playing = 1;
	while(playing) {
		ALLEGRO_EVENT ev;
		//espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);

		//se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
		if(ev.type == ALLEGRO_EVENT_TIMER) {

			//desenha o cenario 
			desenha_cenario();

			atualiza_nave(&nave);

			atualiza_bloco(&bloco);

			colidiu_tiro_bloco = colisao_tiro_bloco(tiro, bloco);
			
			atualiza_inimigos(&array_enemies, num_enemies, bloco, &tiro, nave, &atira, &playing, &pontuacao);

		 	atualiza_Tiro(&tiro, nave, &atira, colidiu_tiro_bloco, &aumenta_tiro);

			desenha_nave(nave);

			desenha_bloco(bloco);

			desenha_tiro(tiro);

			desenha_inimigos(array_enemies, num_enemies);

			if (colisao_nave_bloco(nave, bloco) == 1){
				playing = 0;
			}
			char pontos_de_jogo[20];
			sprintf(pontos_de_jogo, "Pontuação: %d", pontuacao);
        	//imprime o texto armazenado em my_text na posicao x=10,y=10 e com a cor rgb(128,200,30)
        	al_draw_text(size_32, al_map_rgb(0, 200, 30), 10, 20, 0, pontos_de_jogo);


			//atualiza a tela (quando houver algo para mostrar)
			al_flip_display();
			
			
		}
		//se o tipo de evento for o fechamento da tela (clique no x da janela)
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
		}
		
		//se o tipo de evento for um pressionar de uma tecla
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {

			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_SPACE:
					aumenta_tiro = 1;
				break;
			}

			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_I:
					
					if(teclou_i == 0){
						nave.cor = al_map_rgb(250, 190, 40);
						tiro.cor = al_map_rgb(250, 190, 40);
						teclou_i = 1;
					}
					else{
						nave.cor = al_map_rgb(240, 73, 112);
						tiro.cor = al_map_rgb(255, 0, 0);
						teclou_i = 0;
					
					}
					
		
				break;
			}


			switch(ev.keyboard.keycode){

				case ALLEGRO_KEY_W:
					nave.dir_y--;
				break;

				case ALLEGRO_KEY_S:
					nave.dir_y++;
				break;

				case ALLEGRO_KEY_D:
					nave.dir_x++;
				break;

				case ALLEGRO_KEY_A:
					nave.dir_x--;
				break;



			}


		}

		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_SPACE:
					atira = 1;
					aumenta_tiro = 0;
				break;
			}

			switch(ev.keyboard.keycode){

				case ALLEGRO_KEY_W:
					nave.dir_y++;
				break;

				case ALLEGRO_KEY_S:
					nave.dir_y--;
				break;

				case ALLEGRO_KEY_D:
					nave.dir_x--;
				break;

				case ALLEGRO_KEY_A:
					nave.dir_x++;
				break;
			}


		}

	} //fim do while

	while(!playing){
		al_flip_display();
		desenha_cenario();

		char texto_final[30];	

		sprintf(texto_final, "Pontuação: %d", pontuacao);
		al_draw_text(size_32, al_map_rgb(200, 0, 30), SCREEN_W/3, SCREEN_H/2 -25, 0, texto_final);

		int recorde = 0;

		Recorde(pontuacao, &recorde);
		sprintf(texto_final, "Recorde: %d", recorde);
		al_draw_text(size_32, al_map_rgb(0, 200, 30), SCREEN_W/3, SCREEN_H/2+25, 0, texto_final);
		
		
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
	
		
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 1;
		}
	}

	
	//procedimentos de fim de jogo (fecha a tela, limpa a memoria, etc)
	
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
   
 
	return 0;
}